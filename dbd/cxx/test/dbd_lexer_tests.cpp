#include <catch2/catch_test_macros.hpp>

#include <dbd_lexer.hpp>

TEST_CASE("simple tokens are read", "[lexer]") {
    REQUIRE(dbd::lexer("$").get_item(0).m_type == dbd::lexer_item_type::DOLLAR_SIGN);
    REQUIRE(dbd::lexer("<").get_item(0).m_type == dbd::lexer_item_type::OPEN_ANGLE_BRACKET);
    REQUIRE(dbd::lexer(">").get_item(0).m_type == dbd::lexer_item_type::CLOSE_ANGLE_BRACKET);
    REQUIRE(dbd::lexer("[").get_item(0).m_type == dbd::lexer_item_type::OPEN_SQUARE_BRACKET);
    REQUIRE(dbd::lexer("]").get_item(0).m_type == dbd::lexer_item_type::CLOSE_SQUARE_BRACKET);
    REQUIRE(dbd::lexer("=").get_item(0).m_type == dbd::lexer_item_type::EQUALS_SIGN);
    REQUIRE(dbd::lexer("-").get_item(0).m_type == dbd::lexer_item_type::DASH);
    REQUIRE(dbd::lexer("\n").get_item(0).m_type == dbd::lexer_item_type::NEW_LINE);
    REQUIRE(dbd::lexer("?").get_item(0).m_type == dbd::lexer_item_type::QUESTION_MARK);
}

TEST_CASE("lexer stores row/column data correctly", "[lexer]") {
    dbd::lexer lex("$");

    REQUIRE(lex.get_item(0).m_row == 1);
    REQUIRE(lex.get_item(0).m_column == 1);
}

TEST_CASE("double colon tokens are read", "[lexer]") {
    REQUIRE(dbd::lexer("::").get_item(0).m_type == dbd::lexer_item_type::DOUBLE_COLON);
}

TEST_CASE("new section tokens are read", "[lexer]") {
    REQUIRE(dbd::lexer("\n\n").get_item(0).m_type == dbd::lexer_item_type::NEW_SECTION);
}

TEST_CASE("consequetive simple tokens are read", "[lexer]") {
    dbd::lexer lex(",-");
    REQUIRE(lex.get_item(0).m_type == dbd::lexer_item_type::COMMA);
    REQUIRE(lex.get_item(1).m_type == dbd::lexer_item_type::DASH);
}

TEST_CASE("consequetive complex tokens are read", "[lexer]") {
    dbd::lexer lex("-::::-");
    REQUIRE(lex.get_item(0).m_type == dbd::lexer_item_type::DASH);
    REQUIRE(lex.get_item(1).m_type == dbd::lexer_item_type::DOUBLE_COLON);
    REQUIRE(lex.get_item(2).m_type == dbd::lexer_item_type::DOUBLE_COLON);
    REQUIRE(lex.get_item(3).m_type == dbd::lexer_item_type::DASH);
}

TEST_CASE("identifiers are read", "[lexer]") {
    dbd::lexer lex("hello");
    REQUIRE(lex.get_item(0).m_type == dbd::lexer_item_type::IDENTIFIER);
    REQUIRE(std::string(lex.get_item(0).m_text) == "hello");
}

TEST_CASE("identifiers are read inline", "[lexer]") {
    dbd::lexer lex("$hello-");
    REQUIRE(lex.get_item(1).m_type == dbd::lexer_item_type::IDENTIFIER);
    REQUIRE(std::string(lex.get_item(1).m_text) == "hello");
}
