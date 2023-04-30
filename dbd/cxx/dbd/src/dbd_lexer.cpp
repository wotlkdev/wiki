#include "dbd_lexer.hpp"

#include <cctype>
#include <regex>
#include <vector>
#include <iostream>

constexpr float ITEM_RESERVE_RATIO = 0.65; // guess value, worked the best while testing

namespace dbd
{
    lexer::lexer(std::string const& text, std::string const& filename)
        : m_text(text)
        , m_filename(filename)
    {
        m_items.reserve(text.size() * ITEM_RESERVE_RATIO);
        while (m_index < m_text.size())
        {
            size_t start = m_index;
            char c = read();
            switch (c)
            {
            case ' ':
                break;
            case '$':
                add_item(lexer_item_type::DOLLAR_SIGN, start);
                break;
            case '-':
                add_item(lexer_item_type::DASH, start);
                break;
            case '<':
                add_item(lexer_item_type::OPEN_ANGLE_BRACKET, start);
                break;
            case '>':
                add_item(lexer_item_type::CLOSE_ANGLE_BRACKET, start);
                break;
            case '[':
                add_item(lexer_item_type::OPEN_SQUARE_BRACKET, start);
                break;
            case ']':
                add_item(lexer_item_type::CLOSE_SQUARE_BRACKET, start);
                break;
            case '=':
                add_item(lexer_item_type::EQUALS_SIGN, start);
                break;
            case '?':
                add_item(lexer_item_type::QUESTION_MARK, start);
                break;
            case ',':
                add_item(lexer_item_type::COMMA, start);
                break;
            case '.':
                add_item(lexer_item_type::DOT, start);
                break;
            case ':':
                if (read() != ':')
                {
                    throw lexer_exception(*this, "expected another :");
                }
                add_item(lexer_item_type::DOUBLE_COLON, start);
                break;
            case '/':
                if (read() != '/')
                {
                    throw lexer_exception(*this, "expected another /");
                }
                while (peek() != '\n')
                {
                    m_index++;
                }
                break;
            case '\n':
                if (m_index < m_text.size() && peek() == '\n')
                {
                    add_item(lexer_item_type::NEW_SECTION, start);
                    m_index++;
                }
                else
                {
                    add_item(lexer_item_type::NEW_LINE, start);
                }
                break;
            default:
            {
                if (!is_identifier_char(c))
                {
                    throw lexer_exception(*this, std::string("unknonwn symbol: ") + c);
                }
                while (m_index < m_text.size() && is_identifier_char(peek()))
                {
                    m_index++;
                }
                add_item(lexer_item_type::IDENTIFIER, start);
                if (m_items[m_items.size() - 1].m_text == "COMMENT")
                {
                    m_items.pop_back();
                    while (m_index < m_text.size() && read() != '\n')
                    {}
                }
            }
            }
        }
    }

    bool lexer::is_identifier_char(char c)
    {
        return isalnum(c) || c == '_';
    }

    void lexer::add_item(lexer_item_type item, size_t start)
    {
        m_items.push_back({ item,m_row,m_column,std::string_view(m_text.begin() + start, m_text.begin() + m_index) });
    }

    lexer_item const& lexer::get_item(size_t index)
    {
        if (index >= m_items.size())
        {
            throw std::runtime_error("tried to access item out of bounds");
        }
        return m_items[index];
    }

    size_t lexer::size()
    {
        return m_items.size();
    }

    char lexer::read()
    {
        if (m_index >= m_text.size())
        {
            throw lexer_exception(*this, "attempted to read character out of bounds");
        }
        return m_text[m_index++];
    }

    char lexer::peek(std::int64_t offset)
    {
        if (m_index + offset >= m_text.size())
        {
            throw lexer_exception(*this, "attempted to read character out of bounds");
        }
        return m_text[m_index + offset];
    }

    lexer_exception::lexer_exception(lexer const& lexer, std::string const& message)
        : std::runtime_error(
            "lexer error in " +
            (lexer.m_filename.size() > 0 ? lexer.m_filename + ":" : "") +
            std::to_string(lexer.m_row) +
                ":" +
            std::to_string(lexer.m_column) +
            ": " +
            message
        )
    {}

    std::string lexer_item_type_to_string(lexer_item_type type)
    {
        switch (type)
        {
        case lexer_item_type::COMMENT: return "COMMENT";
        case lexer_item_type::IDENTIFIER: return "IDENTIFIER";
        case lexer_item_type::DOUBLE_COLON: return "DOUBLE_COLON";
        case lexer_item_type::NEW_SECTION: return "NEW_SECTION";
        case lexer_item_type::COMMA: return "COMMA";
        case lexer_item_type::DASH: return "DASH";
        case lexer_item_type::NEW_LINE: return "NEW_LINE";
        case lexer_item_type::OPEN_ANGLE_BRACKET: return "OPEN_ANGLE_BRACKET";
        case lexer_item_type::CLOSE_ANGLE_BRACKET: return "CLOSE_ANGLE_BRACKET";
        case lexer_item_type::OPEN_SQUARE_BRACKET: return "OPEN_SQUARE_BACKET";
        case lexer_item_type::CLOSE_SQUARE_BRACKET: return "CLOSE_SQUARE_BRACKET";
        case lexer_item_type::EQUALS_SIGN: return "EQUALS_SIGN";
        case lexer_item_type::DOLLAR_SIGN: return "DOLLAR_SIGN";
        case lexer_item_type::QUESTION_MARK: return "QUESTION_MARK";
        default:
            throw std::runtime_error("unknown lexer type " + std::to_string(static_cast<size_t>(type)));
        }
    }
}
