#pragma once

#include "dbd_lexer.hpp"

#include <set>
#include <vector>
#include <optional>

namespace dbd
{
    enum class section_type
    {
        COLUMNS,
        LAYOUT,
        BUILD,
    };

    enum class column_type
    {
        INT,
        LOCSTRING,
        FLOAT,
        STRING
    };

    struct column
    {
        column_type m_type;
        std::string_view m_foreign_table;
        std::string_view m_foreign_column;
        std::string_view m_name;
        bool m_unverified;
    };

    struct build
    {
        int m_major = 0;
        int m_minor = 0;
        int m_patch = 0;
        int m_build = 0;

        bool is_classic_build() const;

        bool operator<(build const& other) const;
        bool operator>(build const& other) const;
        bool operator<=(build const& other) const;
        bool operator>=(build const& other) const;
        bool operator==(build const& other) const;
        bool operator!=(build const& other) const;

        std::string to_string();
    };

    struct build_range
    {
        build m_start;
        std::optional<build> m_end;
        bool includes_build(build const& build) const;
    };

    enum class column_flags : std::uint32_t
    {
        NONE       = 0x0,
        ID         = 0x1,
        RELATION   = 0x2,
        NON_INLINE = 0x4
    };

    enum class column_size
    {
        NONE = 0,
        SIZE_8 = 8,
        SIZE_16 = 16,
        SIZE_32 = 32,
        SIZE_64 = 64,
    };

    struct version_column
    {
        column* m_column = nullptr;
        column_size m_size = column_size::NONE;
        size_t m_array_size = 1;
        bool m_is_unsigned = false;
        std::uint32_t m_flags = static_cast<std::uint32_t>(column_flags::NONE);
    };

    struct version_def
    {
        std::string_view m_comment;
        std::set<std::string_view> m_layout_hashes;
        std::vector<build_range> m_builds;
        std::vector<version_column> m_columns;
        bool includes_build(build const& build) const;
    };

    class parser
    {
    public:
        parser(std::string const& filename);
        parser(std::string const& text, std::string const& filename);
        std::vector<column> m_columns;
        std::vector<version_def> m_versions;
        bool is_finished();
        std::optional<version_def> find_version(build const& build) const;
    private:
        bool read_section(section_type& type);
        column_type read_column_type();

        int read_int();
        lexer_item const& read();
        lexer_item const& peek(std::int64_t offset = 0);
        bool read_if(lexer_item_type type);
        lexer_item const& read_type(lexer_item_type type);

        void read_build(build& res);

        lexer m_lexer;
        bool m_finished = false;
        size_t m_index = 0;
        friend struct parser_exception;
    };

    struct parser_exception : public std::runtime_error
    {
        parser_exception(parser const& parser, lexer_item const& pos, std::string const& message);
    };
}