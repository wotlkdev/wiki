#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <cstdint>
#include <stdexcept>

namespace dbd
{
    enum class lexer_item_type
    {
        COMMENT,
        IDENTIFIER,
        DOUBLE_COLON,
        NEW_SECTION,
        COMMA,
        DASH,
        DOT,
        NEW_LINE,
        OPEN_ANGLE_BRACKET,
        CLOSE_ANGLE_BRACKET,
        OPEN_SQUARE_BRACKET,
        CLOSE_SQUARE_BRACKET,
        EQUALS_SIGN,
        DOLLAR_SIGN,
        QUESTION_MARK,
    };

    std::string lexer_item_type_to_string(lexer_item_type type);

    struct lexer_item
    {
        lexer_item_type m_type;
        size_t m_row;
        size_t m_column;
        std::basic_string_view<char> m_text;
    };

    class lexer
    {
    public:
        lexer(std::string const& text, std::string const& filename = "");
        lexer_item const& get_item(size_t index);
        size_t size();
        const std::string m_text;
        const std::string m_filename;
    private:
        void add_item(lexer_item_type item, size_t start);
        bool is_identifier_char(char c);
        char read();
        char peek(std::int64_t offset = 0);
        std::vector<lexer_item> m_items;
        size_t m_index = 0;
        size_t m_column = 1;
        size_t m_row = 1;
        friend struct lexer_exception;
    };

    struct lexer_exception : public std::runtime_error
    {
        lexer_exception(lexer const& lexer, std::string const& message);
    };
}
