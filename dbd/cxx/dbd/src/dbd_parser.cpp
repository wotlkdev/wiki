#include "dbd_parser.hpp"

#include <charconv>
#include <fstream>
#include <sstream>

namespace
{
    std::string read_file(std::string const& path)
    {
        std::ifstream ifs(path);
        std::stringstream str;
        str << ifs.rdbuf();
        return str.str();
    }
}

namespace dbd
{
    parser::parser(std::string const& filename)
        : parser(read_file(filename) ,filename)
    {
    }

    parser::parser(std::string const& text, std::string const& filename)
        : m_lexer(text, filename)
    {
        section_type initial_section;
        if (!read_section(initial_section) || initial_section != section_type::COLUMNS)
        {
            throw parser_exception(*this, peek(-1), "expected COLUMNS section type, but got " + std::string(peek(-1).m_text));
        }

        while (read_if(lexer_item_type::NEW_LINE))
        {
            column_type type = read_column_type();
            std::string_view table, column;
            if (read_if(lexer_item_type::OPEN_ANGLE_BRACKET))
            {
                table = read_type(lexer_item_type::IDENTIFIER).m_text;
                read_type(lexer_item_type::DOUBLE_COLON);
                column = read_type(lexer_item_type::IDENTIFIER).m_text;
                read_type(lexer_item_type::CLOSE_ANGLE_BRACKET);
            }
            std::string_view name = read_type(lexer_item_type::IDENTIFIER).m_text;
            m_columns.push_back({ type,table,column,name, read_if(lexer_item_type::QUESTION_MARK )});
        }

        // no contents
        if (m_columns.size() == 0)
        {
            m_finished = true;
            return;
        }

        do
        {
            read_type(lexer_item_type::NEW_SECTION);
            version_def& def = m_versions.emplace_back();
            section_type type;
            while (read_section(type))
            {
                switch (type)
                {
                case section_type::BUILD:
                {
                    do
                    {
                        build_range& range = def.m_builds.emplace_back();
                        read_build(range.m_start);
                        if (read_if(lexer_item_type::DASH))
                        {
                            range.m_end.emplace();
                            read_build(range.m_end.value());
                        }
                    } while (read_if(lexer_item_type::COMMA));
                    read_type(lexer_item_type::NEW_LINE);
                    break;
                }
                case section_type::LAYOUT:
                {
                    if (def.m_layout_hashes.size() > 0)
                    {
                        throw parser_exception(*this, peek(-1), "duplicate layout section, only one is allowed per version block");
                    }
                    do
                    {
                        std::string_view hash = read_type(lexer_item_type::IDENTIFIER).m_text;
                        if (def.m_layout_hashes.find(hash) != def.m_layout_hashes.end())
                        {
                            throw parser_exception(*this, peek(-1), "duplicate layout hash " + std::string(hash));
                        }
                        def.m_layout_hashes.insert(hash);
                    } while (read_if(lexer_item_type::COMMA));
                    read_type(lexer_item_type::NEW_LINE);
                    break;
                }
                case section_type::COLUMNS:
                    throw parser_exception(*this, peek(-1), "COLUMNS section declared after initial section");
                }
            }

            if (def.m_builds.size() == 0)
            {
                throw parser_exception(*this, peek(-1), "no builds specified for version block");
            }

            do
            {
                version_column& col = def.m_columns.emplace_back();

                if (read_if(lexer_item_type::DOLLAR_SIGN))
                {
                    do
                    {
                        lexer_item const& item = read_type(lexer_item_type::IDENTIFIER);
                        if (item.m_text == "id")
                        {
                            col.m_flags |= static_cast<std::uint32_t>(column_flags::ID);
                        }
                        else if (item.m_text == "relation")
                        {
                            col.m_flags |= static_cast<std::uint32_t>(column_flags::RELATION);
                        }
                        else if (item.m_text == "noninline")
                        {
                            col.m_flags |= static_cast<std::uint32_t>(column_flags::NON_INLINE);
                        }
                        else
                        {
                            throw parser_exception(*this, item, "expected identifier 'id' or 'relation', got " + std::string(item.m_text));
                        }
                    } while (read_if(lexer_item_type::COMMA));
                    read_if(lexer_item_type::DOLLAR_SIGN);
                }

                lexer_item const& name = read_type(lexer_item_type::IDENTIFIER);
                auto itr = std::find_if(m_columns.begin(), m_columns.end(),
                    [&](column const& c) { return c.m_name == name.m_text; });
                if (itr == m_columns.end())
                {
                    throw parser_exception(*this, name, "unknown column in version block: \"" + std::string(name.m_text) + "\"");
                }
                col.m_column = &(*itr);
                if (read_if(lexer_item_type::OPEN_ANGLE_BRACKET))
                {
                    lexer_item const& size = read_type(lexer_item_type::IDENTIFIER);
                    std::string_view size_str(size.m_text);
                    if (size_str.starts_with("u"))
                    {
                        col.m_is_unsigned = true;
                        size_str = std::string_view(size_str.begin() + 1, size_str.end());
                    }

                    if (size_str == "8")
                    {
                        col.m_size = column_size::SIZE_8;
                    }
                    else if (size_str == "16")
                    {
                        col.m_size = column_size::SIZE_16;
                    }
                    else if (size_str == "32")
                    {
                        col.m_size = column_size::SIZE_32;
                    }
                    else if (size_str == "64")
                    {
                        col.m_size = column_size::SIZE_64;
                    }
                    else
                    {
                        throw parser_exception(*this, size, "invalid array size: " + std::string(size.m_text));
                    }
                    read_type(lexer_item_type::CLOSE_ANGLE_BRACKET);
                }

                if (read_if(lexer_item_type::OPEN_SQUARE_BRACKET))
                {
                    col.m_array_size = read_int();
                    read_type(lexer_item_type::CLOSE_SQUARE_BRACKET);
                }
            } while (read_if(lexer_item_type::NEW_LINE) && m_index < m_lexer.size());
        } while (m_index < m_lexer.size());

        m_finished = true;
    }

    bool parser::read_section(section_type& type)
    {
        lexer_item const& item = peek();
        if (item.m_type != lexer_item_type::IDENTIFIER)
        {
            return false;
        }

        if (item.m_text == "COLUMNS")
        {
            type = section_type::COLUMNS;
        }
        else if (item.m_text == "LAYOUT")
        {
            type = section_type::LAYOUT;
        }
        else if (item.m_text == "BUILD")
        {
            type = section_type::BUILD;
        }
        else
        {
            return false;
        }

        read();
        return true;
    }

    column_type parser::read_column_type()
    {
        lexer_item const& item = read_type(lexer_item_type::IDENTIFIER);

        if (item.m_text == "int")
        {
            return column_type::INT;
        }
        if (item.m_text == "locstring")
        {
            return column_type::LOCSTRING;
        }
        if (item.m_text == "float")
        {
            return column_type::FLOAT;
        }
        if (item.m_text == "string")
        {
            return column_type::STRING;
        }

        throw parser_exception(*this, item, "expected column type, but got " + std::string(item.m_text));
    }

    lexer_item const& parser::read_type(lexer_item_type type)
    {
        lexer_item const& item = read();
        if (item.m_type != type)
        {
            throw parser_exception(*this, item, "expected " + lexer_item_type_to_string(type) + ", but got " + lexer_item_type_to_string(item.m_type));
        }
        return item;
    }

    bool parser::read_if(lexer_item_type type)
    {
        if (m_index >= m_lexer.size())
        {
            return false;
        }
        if (m_lexer.get_item(m_index).m_type == type)
        {
            ++m_index;
            return true;
        }
        return false;
    }

    lexer_item const& parser::read()
    {
        return m_lexer.get_item(m_index++);
    }

    int parser::read_int()
    {
        lexer_item const& item = read();
        if (item.m_type != lexer_item_type::IDENTIFIER)
        {
            throw parser_exception(*this, item, "expected integer, but got " + std::string(item.m_text));
        }
        int i;
        std::from_chars_result res = std::from_chars(item.m_text.data(), item.m_text.data() + item.m_text.size(), i);

        if (res.ec == std::errc::invalid_argument)
        {
            throw parser_exception(*this, item, "invalid argument during int conversion for " + std::string(item.m_text));
        }
        else if (res.ec == std::errc::result_out_of_range)
        {
            throw parser_exception(*this, item, "result out of range during int conversion for " + std::string(item.m_text));
        }
        return i;
    }

    void parser::read_build(build& res)
    {
        res.m_major = read_int();
        read_type(lexer_item_type::DOT);
        res.m_minor = read_int();
        read_type(lexer_item_type::DOT);
        res.m_patch = read_int();
        read_type(lexer_item_type::DOT);
        res.m_build = read_int();
    }

    bool parser::is_finished()
    {
        return m_finished;
    }

    lexer_item const& parser::peek(std::int64_t offset)
    {
        return m_lexer.get_item(m_index + offset);
    }

    bool build::is_classic_build() const
    {
        return (m_major == 1 && m_minor > 12)
            || (m_major == 2 && m_minor > 4)
            || (m_major == 3 && m_minor > 3)
            ;
    }

    bool build::operator<(build const& other) const
    {
        if (m_major < other.m_major) return true;
        if (m_major > other.m_major) return false;

        // classic fuckery
        if (m_major == 1 && m_minor <= 12 && other.m_minor >= 13)
        {
            return true;
        }

        if (m_minor < other.m_minor) return true;
        if (m_minor > other.m_minor) return false;

        if (m_patch < other.m_patch) return true;
        if (m_patch > other.m_patch) return false;

        return m_build < other.m_build;
    }

    bool build::operator==(build const& other) const
    {
        return m_major == other.m_major && m_minor == other.m_minor && m_patch == other.m_patch && m_build == other.m_build;
    }

    bool build::operator>(build const& other) const { return !(*this >= other); }
    bool build::operator<=(build const& other) const { return (*this < other) || (*this == other); }
    bool build::operator>=(build const& other) const { return (*this == other) || !(*this < other); };
    bool build::operator!=(build const& other) const { return !(*this == other); };

    bool build_range::includes_build(build const& build) const
    {
        if (!m_end.has_value())
        {
            return m_start == build;
        }

        if (m_start.is_classic_build() != build.is_classic_build())
        {
            return false;
        }
        return build >= m_start && (build <= *m_end);
    }

    bool version_def::includes_build(build const& build) const
    {
        for (build_range const& range : m_builds)
        {
            if (range.includes_build(build))
            {
                return true;
            }
        }
        return false;
    }

    std::optional<version_def> parser::find_version(build const& build) const
    {
        for (version_def const& def : m_versions)
        {
            if (def.includes_build(build))
            {
                return def;
            }
        }
        return {};
    }

    std::string build::to_string()
    {
        return std::to_string(m_major) + "." + std::to_string(m_minor) + "." + std::to_string(m_patch) + "." + std::to_string(m_build);
    }

    parser_exception::parser_exception(parser const& parser, lexer_item const& pos, std::string const& message)
        : std::runtime_error(
            "parser error in " +
            (parser.m_lexer.m_filename.size() > 0 ? parser.m_lexer.m_filename + ":" : "") +
            std::to_string(pos.m_row) +
            ":" +
            std::to_string(pos.m_column) +
            ": " +
            message
        )
    {}

}