#include <catch2/catch_test_macros.hpp>

#include "dbd_parser.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <chrono>

TEST_CASE("reads a minimal definition", "[parser]") {
    dbd::parser parse(
        "COLUMNS\n"
        "int ID\n"
        "\n"
        "BUILD 1.2.3.4\n"
        "ID"
    );

    REQUIRE(parse.m_columns.size() == 1);
    REQUIRE(std::string(parse.m_columns[0].m_name) == "ID");
    REQUIRE(parse.m_columns[0].m_type == dbd::column_type::INT);
    REQUIRE(parse.m_columns[0].m_foreign_column.size() == 0);
    REQUIRE(parse.m_columns[0].m_foreign_table.size() == 0);

    REQUIRE(parse.m_versions.size() == 1);
    REQUIRE(parse.m_versions[0].m_builds.size() == 1);
    REQUIRE(parse.m_versions[0].m_builds[0].m_end.has_value() == false);
    REQUIRE(parse.m_versions[0].m_builds[0].m_start.to_string() == "1.2.3.4");
    REQUIRE(parse.m_versions[0].m_layout_hashes.size() == 0);
}

TEST_CASE("reads multiple build entries", "[parser]") {
    dbd::parser parse(
        "COLUMNS\n"
        "int ID\n"
        "\n"
        "BUILD 1.2.3.4, 5.6.7.8\n"
        "ID"
    );

    REQUIRE(parse.m_versions[0].m_builds.size() == 2);
    REQUIRE(parse.m_versions[0].m_builds[0].m_start.to_string() == "1.2.3.4");
    REQUIRE(parse.m_versions[0].m_builds[1].m_start.to_string() == "5.6.7.8");
}

TEST_CASE("reads multiple build lines", "[parser]") {
    dbd::parser parse(
        "COLUMNS\n"
        "int ID\n"
        "\n"
        "BUILD 1.2.3.4\n"
        "BUILD 5.6.7.8\n"
        "ID"
    );

    REQUIRE(parse.m_versions[0].m_builds.size() == 2);
    REQUIRE(parse.m_versions[0].m_builds[0].m_start.to_string() == "1.2.3.4");
    REQUIRE(parse.m_versions[0].m_builds[1].m_start.to_string() == "5.6.7.8");
}

TEST_CASE("reads build range", "[parser]") {
    dbd::parser parse(
        "COLUMNS\n"
        "int ID\n"
        "\n"
        "BUILD 1.2.3.4-5.6.7.8\n"
        "ID"
    );

    REQUIRE(parse.m_versions[0].m_builds[0].m_start.to_string() == "1.2.3.4");
    REQUIRE(parse.m_versions[0].m_builds[0].m_end.has_value() == true);
    REQUIRE(parse.m_versions[0].m_builds[0].m_end->to_string() == "5.6.7.8");
}

TEST_CASE("reads foreign key in column definition", "[parser]") {
    dbd::parser parse(
        "COLUMNS\n"
        "int<A::B> ID\n"
        "\n"
        "BUILD 1.2.3.4\n"
        "ID"
    );

    REQUIRE(std::string(parse.m_columns[0].m_foreign_table)  == "A");
    REQUIRE(std::string(parse.m_columns[0].m_foreign_column) == "B");
    REQUIRE(std::string(parse.m_columns[0].m_name) == "ID");
}

TEST_CASE("reads single layout", "[parser]") {
    dbd::parser parse(
        "COLUMNS\n"
        "int ID\n"
        "\n"
        "LAYOUT 1234\n"
        "BUILD 1.2.3.4\n"
        "ID"
    );

    REQUIRE(parse.m_versions[0].m_layout_hashes.contains("1234") == true);
    REQUIRE(parse.m_versions[0].m_builds.size() == 1);
}

TEST_CASE("reads multiple layouts", "[parser]")
{
    dbd::parser parse(
        "COLUMNS\n"
        "int ID\n"
        "\n"
        "LAYOUT 1234, 5678\n"
        "BUILD 1.2.3.4\n"
        "ID"
    );

    REQUIRE(parse.m_versions[0].m_layout_hashes.contains("1234") == true);
    REQUIRE(parse.m_versions[0].m_layout_hashes.contains("5678") == true);
}

TEST_CASE("reads $id$ prefix in version column", "[parser]")
{
    dbd::parser parse(
        "COLUMNS\n"
        "int ID\n"
        "\n"
        "BUILD 1.2.3.4\n"
        "$id$ID"
    );

    REQUIRE(parse.m_versions[0].m_columns[0].m_flags == static_cast<std::uint32_t>(dbd::column_flags::ID));
}

TEST_CASE("reads $relation$ prefix in version column", "[parser]")
{
    dbd::parser parse(
        "COLUMNS\n"
        "int ID\n"
        "\n"
        "BUILD 1.2.3.4\n"
        "$relation$ID"
    );

    REQUIRE(parse.m_versions[0].m_columns[0].m_flags == static_cast<std::uint32_t>(dbd::column_flags::RELATION));
}

TEST_CASE("reads sizes in version column", "[parser]")
{
    dbd::parser parse(
        "COLUMNS\n"
        "int ID\n"
        "\n"
        "BUILD 1.2.3.4\n"
        "ID<8>"
    );

    REQUIRE(parse.m_versions[0].m_columns[0].m_size == dbd::column_size::SIZE_8);
}

TEST_CASE("reads array sizes in version column", "[parser]")
{
    dbd::parser parse(
        "COLUMNS\n"
        "int ID\n"
        "\n"
        "BUILD 1.2.3.4\n"
        "ID[5]"
    );

    REQUIRE(parse.m_versions[0].m_columns[0].m_array_size == 5);
}

TEST_CASE("reads size + array sizes in version column", "[parser]")
{
    dbd::parser parse(
        "COLUMNS\n"
        "int ID\n"
        "\n"
        "BUILD 1.2.3.4\n"
        "ID<8>[5]"
    );

    REQUIRE(parse.m_versions[0].m_columns[0].m_size == dbd::column_size::SIZE_8);
    REQUIRE(parse.m_versions[0].m_columns[0].m_array_size == 5);
}

TEST_CASE("reads all possible types", "[parser]")
{
    dbd::parser parse(
        "COLUMNS\n"
        "int v1\n"
        "float v2\n"
        "string v3\n"
        "locstring v4\n"
        "\n"
        "BUILD 1.2.3.4\n"
        "v1"
    );

    REQUIRE(parse.m_columns[0].m_type == dbd::column_type::INT);
    REQUIRE(parse.m_columns[1].m_type == dbd::column_type::FLOAT);
    REQUIRE(parse.m_columns[2].m_type == dbd::column_type::STRING);
    REQUIRE(parse.m_columns[3].m_type == dbd::column_type::LOCSTRING);
}

TEST_CASE("reads multiple versions", "[parser]")
{
    dbd::parser parse(
        "COLUMNS\n"
        "int id\n"
        "\n"
        "BUILD 1.2.3.4\n"
        "id\n"
        "\n"
        "BUILD 5.6.7.8\n"
        "id"
    );

    REQUIRE(parse.m_versions.size() == 2);
}

TEST_CASE("handles trailing whitespace", "[parser]")
{
    dbd::parser parse(
        "COLUMNS\n"
        "int id\n"
        "\n"
        "BUILD 1.2.3.4\n"
        "id\n"
    );
}

TEST_CASE("reads complex combination of settings", "[parser]")
{
    dbd::parser parse(
        "COLUMNS\n"
        "int v1\n"
        "float v2\n"
        "string v3\n"
        "locstring v4\n"
        "int<A::B> ref\n"
        "\n"
        "LAYOUT 1234, 6789\n"
        "BUILD 1.2.3.4, 5.6.7.8\n"
        "BUILD 1.1.2.2-1.1.2.3, 5.5.6.6\n"
        "$id$v1<8>\n"
        "$relation$v2<16>[5]\n"
        "$id,noninline$v3\n"
        "v4\n"
        "ref\n"
        "\n"
        "BUILD 9.9.9.9\n"
        "v1\n"
    );

    REQUIRE(parse.m_columns.size() == 5);
    REQUIRE(parse.m_columns[0].m_type == dbd::column_type::INT);
    REQUIRE(parse.m_columns[1].m_type == dbd::column_type::FLOAT);
    REQUIRE(parse.m_columns[2].m_type == dbd::column_type::STRING);
    REQUIRE(parse.m_columns[3].m_type == dbd::column_type::LOCSTRING);
    REQUIRE(parse.m_columns[4].m_type == dbd::column_type::INT);

    REQUIRE(std::string(parse.m_columns[0].m_name) == "v1");
    REQUIRE(std::string(parse.m_columns[1].m_name) == "v2");
    REQUIRE(std::string(parse.m_columns[2].m_name) == "v3");
    REQUIRE(std::string(parse.m_columns[3].m_name) == "v4");
    REQUIRE(std::string(parse.m_columns[4].m_name) == "ref");

    REQUIRE(std::string(parse.m_columns[4].m_foreign_table) == "A");
    REQUIRE(std::string(parse.m_columns[4].m_foreign_column) == "B");

    REQUIRE(parse.m_versions[0].m_layout_hashes.size() == 2);
    REQUIRE(parse.m_versions[0].m_layout_hashes.contains("1234") == true);
    REQUIRE(parse.m_versions[0].m_layout_hashes.contains("6789") == true);

    REQUIRE(parse.m_versions[0].m_builds[0].m_start.to_string() == "1.2.3.4");
    REQUIRE(parse.m_versions[0].m_builds[0].m_end.has_value() == false);
    REQUIRE(parse.m_versions[0].m_builds[1].m_start.to_string() == "5.6.7.8");
    REQUIRE(parse.m_versions[0].m_builds[1].m_end.has_value() == false);
    REQUIRE(parse.m_versions[0].m_builds[2].m_start.to_string() == "1.1.2.2");
    REQUIRE(parse.m_versions[0].m_builds[2].m_end.has_value() == true);
    REQUIRE(parse.m_versions[0].m_builds[2].m_end->to_string() == "1.1.2.3");
    REQUIRE(parse.m_versions[0].m_builds[3].m_start.to_string() == "5.5.6.6");
    REQUIRE(parse.m_versions[0].m_builds[3].m_end.has_value() == false);
    REQUIRE(parse.m_versions[1].m_builds[0].m_start.to_string() == "9.9.9.9");
    REQUIRE(parse.m_versions[1].m_builds[0].m_end.has_value() == false);

    REQUIRE(parse.m_versions[0].m_columns[0].m_flags == static_cast<std::uint32_t>(dbd::column_flags::ID));
    REQUIRE(parse.m_versions[0].m_columns[0].m_column == &parse.m_columns[0]);
    REQUIRE(parse.m_versions[0].m_columns[0].m_size == dbd::column_size::SIZE_8);
    REQUIRE(parse.m_versions[0].m_columns[0].m_array_size == 1);

    REQUIRE(parse.m_versions[0].m_columns[1].m_flags == static_cast<std::uint32_t>(dbd::column_flags::RELATION));
    REQUIRE(parse.m_versions[0].m_columns[1].m_column == &parse.m_columns[1]);
    REQUIRE(parse.m_versions[0].m_columns[1].m_size == dbd::column_size::SIZE_16);
    REQUIRE(parse.m_versions[0].m_columns[1].m_array_size == 5);

    REQUIRE(parse.m_versions[0].m_columns[2].m_flags ==
        (
            static_cast<std::uint32_t>(dbd::column_flags::ID) |
            static_cast<std::uint32_t>(dbd::column_flags::NON_INLINE)
        )
    );
    REQUIRE(parse.m_versions[0].m_columns[2].m_column == &parse.m_columns[2]);
    REQUIRE(parse.m_versions[0].m_columns[2].m_size == dbd::column_size::NONE);
    REQUIRE(parse.m_versions[0].m_columns[2].m_array_size == 1);

    REQUIRE(parse.m_versions[0].m_columns[3].m_flags == static_cast<std::uint32_t>(dbd::column_flags::NONE));
    REQUIRE(parse.m_versions[0].m_columns[3].m_column == &parse.m_columns[3]);
    REQUIRE(parse.m_versions[0].m_columns[3].m_size == dbd::column_size::NONE);
    REQUIRE(parse.m_versions[0].m_columns[3].m_array_size == 1);

    REQUIRE(parse.m_versions[0].m_columns[4].m_flags == static_cast<std::uint32_t>(dbd::column_flags::NONE));
    REQUIRE(parse.m_versions[0].m_columns[4].m_column == &parse.m_columns[4]);
    REQUIRE(parse.m_versions[0].m_columns[4].m_size == dbd::column_size::NONE);
    REQUIRE(parse.m_versions[0].m_columns[4].m_array_size == 1);

    REQUIRE(parse.m_versions[1].m_columns[0].m_flags == static_cast<std::uint32_t>(dbd::column_flags::NONE));
    REQUIRE(parse.m_versions[1].m_columns[0].m_column == &parse.m_columns[0]);
    REQUIRE(parse.m_versions[1].m_columns[0].m_size == dbd::column_size::NONE);
    REQUIRE(parse.m_versions[1].m_columns[0].m_array_size == 1);
}

uint64_t now()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

TEST_CASE("parses every existing definition without errors", "[parser]")
{
    uint64_t total_parse = 0;
    for (auto const& dir_entry : std::filesystem::directory_iterator{ DBD_DEFINITIONS_PATH })
    {
        std::ifstream ifs(dir_entry.path());
        std::string str((std::istreambuf_iterator<char>(ifs)),std::istreambuf_iterator<char>());
        uint64_t parse_start = now();
        REQUIRE(dbd::parser(str).is_finished() == true);
        total_parse += now()  - parse_start;
    }
    std::cout << "\n";
#ifdef DBD_DEBUG
    std::cout << "Warning: Running tests in debug mode (this is very slow, expect high time below)\n";
#endif
    std::cout << "Time to parse all definitions (excluding io): " << total_parse << "ms\n";
    std::cout << "\n";
}
