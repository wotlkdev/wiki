
#include <dbd_parser.hpp>

#include <fmt/core.h>

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unordered_map>

// todo: temporary hardcoded paths

#define OUTPUT_PATH "D:\\dev\\wow\\tswow-maintenance\\wow-intro-tutorials-drafts\\dbd\\dbc"
#define INPUT_PATH "D:\\dev\\wow\\tswow-maintenance\\wow-intro-tutorials-drafts\\dbd\\WoWDBDefs\\definitions"
#define COMMENTS_PATH "D:\\dev\\wow\\tswow-maintenance\\wow-intro-tutorials-drafts\\dbd\\comments"

namespace fs = std::filesystem;

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

int main()
{
    codegen menu(fs::path(OUTPUT_PATH) / "README.md");
    menu.line("# DBC File Documentation");
    menu.line("");
    menu.line("This is an automatically generated documentation for the 3.3.5 DBC files.");
    menu.line("## Tables");

    for (auto const& itr : fs::directory_iterator{ INPUT_PATH })
    {
        dbd::parser parser(itr.path().string());
        auto version = parser.find_version({ 3,3,5,12340 });
        if (!version.has_value())
        {
            continue;
        }

        std::string filename = itr.path().filename().string();
        filename = filename.substr(0, filename.find_last_of('.'));

        std::string file_comment = "";
        std::string menu_comment = "";

        std::unordered_map<std::string,std::string> comments;
        fs::path comments_path = fs::path(COMMENTS_PATH) / (filename + ".md");
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
                    throw std::runtime_error(fmt::format("malformed comments file {} on line {}: could not find any colon", filename, line_no));
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

        menu.line(    "* [{0}]({0}.md)", filename);
        if (menu_comment.size() > 0)
        {
            menu.line("    * {}", menu_comment);
        }

        codegen file(fs::path(OUTPUT_PATH) / (filename + ".md"));
        file.line(        "# {}", filename);
        file.line(        "{}",file_comment);
        file.line(        "| Column | Type | Reference | Comment |", filename);
        file.line(        "|--------|------|-----------|---------|");
        for (auto const& col : version->m_columns)
        {
            std::string foreign_table = "";
            if (col.m_column->m_foreign_table.size() > 0)
            {
                foreign_table = fmt::format("[{0}#{1}]({0}.md)", col.m_column->m_foreign_table, col.m_column->m_foreign_column);
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
                foreign_table,
                comment
            );
        }
    }
}