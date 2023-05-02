
#include <dbd_parser.hpp>

#include <fmt/core.h>

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unordered_map>

static constexpr std::size_t WOTLK_DBC_COUNT = 246;

// ============================================================================
//
// - Overrides -
//
//   This is necessary because WoWDBDefs do not handle foreign keys changing
//   between versions, so we need to tell the exporter what columns to use.
//
//   See https://github.com/wowdev/WoWDBDefs/issues/51
// 
// ============================================================================

struct fk_override
{
    std::string m_table;
    std::string m_column;
};

std::unordered_map<std::string, fk_override> fk_override_by_dest =
{
    {"WorldState:ID",{"WorldStateUI", "ID"}}
};

// these take precedence over fk_override_by_dest
std::unordered_map<std::string, fk_override> fk_override_by_source
{
    // just a dummy, doesn't do anything
    {"CreatureSoundData:SoundExertionID",{"SoundEntries", "ID"}}
};

namespace fs = std::filesystem;

// ============================================================================
//
// - codegen -
//
//   Just a simple class to write code to a file line-by-line
// 
// ============================================================================

class codegen
{
public:
    codegen(fs::path const& path)
        : m_path(path)
    {}

    template <typename ... Args>
    void line(fmt::format_string<Args...> str, Args... args)
    {
        m_ofs << fmt::format(str, std::forward<Args>(args)...) << "\n";
    }

    template <typename ... Args>
    void text(fmt::format_string<Args...> str, Args... args)
    {
        m_ofs << fmt::format(str, std::forward<Args>(args)...);
    }

    ~codegen()
    {
        // only write if the file has changed
        if (fs::exists(m_path))
        {
            std::string str;
            {
                std::ifstream ifs(m_path);
                std::stringstream buf;
                buf << ifs.rdbuf();
                str = buf.str();
            }
            std::string cur = m_ofs.str();
            if (str != cur)
            {
                std::ofstream ofs(m_path);
                ofs << cur;
            }
        }
        else
        {
            std::ofstream ofs(m_path);
            ofs << m_ofs.str();
        }
    }
private:
    std::stringstream m_ofs;
    fs::path m_path;
};

// ============================================================================
//
// - main -
// 
// ============================================================================
int main()
{
    if (!fs::exists(OUTPUT_PATH))
    {
        fs::create_directories(OUTPUT_PATH);
    }

    if (!fs::exists(INPUT_PATH))
    {
        std::cout << "The input path \"" << INPUT_PATH << "\" doesn't exist!\n";
        return 1;
    }

    codegen menu(fs::path(OUTPUT_PATH) / "index.md");
    menu.line("---");
    menu.line("layout: default");
    menu.line("title: DBC");
    menu.line("nav_exclude: true");
    menu.line("---");
    menu.line("# DBC");
    menu.line("");
    menu.line("This is an automatically generated documentation for the 3.3.5 DBC files.");

    std::cout << "Building DBC files...\n";

    int nav_order = 2;
    int files = 0;
    for (auto const& itr : fs::directory_iterator{ INPUT_PATH })
    {
        dbd::parser parser(itr.path().string());
        auto version = parser.find_version({ 3,3,5,12340 });
        if (!version.has_value())
        {
            continue;
        }
        files++;
        std::string table = itr.path().filename().string();
        table = table.substr(0, table.find_last_of('.'));

        std::cout << "  " << table << ".dbc\n";

        std::string file_comment = "";
        std::string menu_comment = "";

        std::unordered_map<std::string,std::string> comments;
        fs::path comments_path = fs::path(COMMENTS_PATH) / (table + ".md");
        if (fs::exists(comments_path))
        {
            std::ifstream ifs(comments_path);
            std::string line;
            int line_no = 1;

            bool reading_columns = false;

            for(int line_no = 1; std::getline(ifs,line); line_no++)
            {
                if (line == "----COLUMNS----")
                {
                    reading_columns = true;
                    continue;
                }

                if (!reading_columns)
                {
                    file_comment += line + "\n";
                    continue;
                }

                size_t index = line.find_first_of(':');
                if (index == std::string::npos)
                {
                    throw std::runtime_error(fmt::format("malformed comments file {} on line {}: could not find any colon", table, line_no));
                }

                std::string key = line.substr(0, index);
                std::string value = line.substr(index+1);
                if (key == "_md_menu")
                {
                    menu_comment = value;
                }
                else
                {
                    comments[key] = value;
                }
            }
        }

        menu.line(    "* [{0}]({0})", table);
        if (menu_comment.size() > 0)
        {
            menu.line("    * {}", menu_comment);
        }

        codegen file(fs::path(OUTPUT_PATH) / (table + ".md"));
        file.line("---");
        file.line("layout: default");
        file.line("title: {}", table);
        file.line("nav_exclude: true",nav_order++);
        file.line("---");

        file.line(        "# {}", table);
        file.line(        "{}",file_comment);
        file.line(        "| Column | Type | Reference | Comment |", table);
        file.line(        "|--------|------|-----------|---------|");
        for (auto const& col : version->m_columns)
        {
            std::string column = std::string(col.m_column->m_name);

            std::string fk_link = "";
            if (col.m_column->m_foreign_table.size() > 0)
            {
                std::string fk_table = std::string(col.m_column->m_foreign_table);
                std::string fk_column = std::string(col.m_column->m_foreign_column);
                
                auto specific_itr = fk_override_by_source.find(fmt::format("{}:{}", table, column));
                if (specific_itr != fk_override_by_source.end())
                {
                    fk_table = specific_itr->second.m_table;
                    fk_column = specific_itr->second.m_column;
                }
                else
                {
                    auto generic_itr = fk_override_by_dest.find(fmt::format("{}:{}", fk_table, fk_column));
                    if (generic_itr != fk_override_by_dest.end())
                    {
                        fk_table = generic_itr->second.m_table;
                        fk_column = generic_itr->second.m_column;
                    }
                }

                fk_link = fmt::format("[{0}#{1}]({0})", fk_table, fk_column);
            }

            std::string array_suffix = "";
            if (col.m_array_size > 1)
            {
                array_suffix = fmt::format("[{}]", col.m_array_size);
            }

            std::string type;
            switch (col.m_column->m_type)
            {
                case dbd::column_type::INT: type = fmt::format("int{}", static_cast<std::size_t>(col.m_size)); break;
                case dbd::column_type::LOCSTRING: type = "locstring"; break;
                case dbd::column_type::FLOAT: type = fmt::format("float"); break;
                case dbd::column_type::STRING: type = "string"; break;
                default:
                {
                    throw std::runtime_error(fmt::format("invalid column type {}", type));
                }
            }

            std::string comment;
            auto itr = comments.find(std::string(col.m_column->m_name));
            if (itr != comments.end())
            {
                comment = itr->second;
            }
            
            file.line(    "|{}|{}{}|{}|{}|",
                col.m_column->m_name,
                type, array_suffix,
                fk_link,
                comment
            );
        }
    }

    if (files != WOTLK_DBC_COUNT)
    {
        std::cout << "Error: Only wrote md for " << files << "/" << WOTLK_DBC_COUNT << ", check your WoWDBDefs.\n";
    }
    else
    {
        std::cout << "Successfully wrote markdown for all " << files << " DBC files.\n";
    }
}