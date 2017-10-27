#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "calculator.hpp"
#include <sstream>

TEST_CASE("Lexeme types be calculated correctly") {
	Token token;

	std::stringstream s;
	s << "11";
	get_token(s, token);
	REQUIRE(token.type == Number);

	std::stringstream s2;
	s2 << "1.3";
	token.c = Empty;
	get_token(s2, token);
	REQUIRE(token.type == Number);

	std::stringstream s3;
	s3 << "1,5";
	token.c = Empty;
	get_token(s3, token);
	REQUIRE(token.type == Number);

	std::stringstream s4;
	s4 << "+";
	token.c = Empty;
	get_token(s4, token);
	REQUIRE(token.type == Plus);

	std::stringstream s5;
	s5 << "-";
	token.c = Empty;
	get_token(s5, token);
	REQUIRE(token.type == Minus);

	std::stringstream s6;
	s6 << "*";
	token.c = Empty;
	get_token(s6, token);
	REQUIRE(token.type == Mult);

	std::stringstream s7;
	s7 << "/";
	token.c = Empty;
	get_token(s7, token);
	REQUIRE(token.type == Div);

	std::stringstream s8;
	s8 << "(";
	token.c = Empty;
	get_token(s8, token);
	REQUIRE(token.type == Lbracket);

	std::stringstream s9;
	s9 << ")";
	token.c = Empty;
	get_token(s9, token);
	REQUIRE(token.type == Rbracket);

	std::stringstream s10;
	s10 << "";
	token.c = Empty;
	get_token(s, token);
	REQUIRE(token.type == Eof);

	std::stringstream s11;
	s11 << "12 +";
	token.c = Empty;
	get_token(s11, token);
	REQUIRE(token.type == Number);
	get_token(s11, token);
	REQUIRE(token.type == Plus);
}

TEST_CASE("Incorrect lexeme must be detected") {
	Token token;
	std::stringstream s;
	s << "1..1";
	REQUIRE_THROWS(get_token(s, token));
	
	std::stringstream s1;
	s1 << "e";
	token.c = Empty;
	REQUIRE_THROWS(get_token(s1, token));

	std::stringstream s2;
	s2 << "{";
	token.c = Empty;
	REQUIRE_THROWS(get_token(s2, token));

}

TEST_CASE("Test of basic() function") {
	Token token;
	std::stringstream s;
	s << "123";
	REQUIRE(basic(s, token, true) == 123);

	std::stringstream s1;
	s1 << "-123";
	token.c = Empty;
	REQUIRE(basic(s1, token, true) == -123);

	std::stringstream s2;
	s2 << "-(123)";
	token.c = Empty;
	REQUIRE(basic(s2, token, true) == -123);

	std::stringstream s3;
	s3 << "(123)";
	token.c = Empty;
	REQUIRE(basic(s3, token, true) == 123);

	std::stringstream s4;
	s4 << "(1+3)";
	token.c = Empty;
	REQUIRE(basic(s4, token, true) == 4);

	std::stringstream s5;
	s5 << "--5";
	token.c = Empty;
	REQUIRE(basic(s5, token, true) == 5);

	std::stringstream s6;
	s6 << "6.0003";
	token.c = Empty;
	REQUIRE(basic(s6, token, true) == 6.0);
}

TEST_CASE("Test of multdiv() function") {
	Token token;
	std::stringstream s;
	s << "5/2";
	REQUIRE(multdiv(s, token, true) == 2.5);

	std::stringstream s1;
	s1 << "2.2 * 3";
	token.c = Empty;
	REQUIRE(multdiv(s1, token, true) == 6.6);

	std::stringstream s2;
	s2 << "10 / 2 / 5";
	token.c = Empty;
	REQUIRE(multdiv(s2, token, true) == 1.0);

	std::stringstream s3;
	s3 << "10 / (5 / 2.5)";
	token.c = Empty;
	REQUIRE(multdiv(s3, token, true) == 5.0);

	std::stringstream s4;
	s4 << "-1";
	token.c = Empty;
	REQUIRE(multdiv(s4, token, true) == -1);

	std::stringstream s5;
	s5 << "(3 +4)";
	token.c = Empty;
	REQUIRE(multdiv(s5, token, true) == 7);
}

TEST_CASE("Test of plusminus() function") {
	Token token;
	std::stringstream s;
	s << "1 + 5";
	REQUIRE(plusminus(s, token, true) == 6);

	std::stringstream s1;
	s1 << "0- 8";
	token.c = Empty;
	REQUIRE(plusminus(s1, token, true) == -8);

	std::stringstream s2;
	s2 << "-1 + 5 - 3";
	token.c = Empty;
	REQUIRE(plusminus(s2, token, true) == 1.0);

	std::stringstream s3;
	s3 << "-10 + (8 * 2.5) - (3 / 1,5)";
	token.c = Empty;
	REQUIRE(plusminus(s3, token, true) == 8);

	std::stringstream s4;
	s4 << "1.1 + 2.1 + abc";
	token.c = Empty;
	REQUIRE_THROWS(plusminus(s4, token, true));

	std::stringstream s5;
	s5 << "(3 +4)";
	token.c = Empty;
	REQUIRE(plusminus(s5, token, true) == 7);

	std::stringstream s6;
	s6 << "10000000 - 0.01";
	token.c = Empty;
	REQUIRE(plusminus(s6, token, true) == 9999999.99);

	std::stringstream s7;
	s7 << "1 + (-4)";
	token.c = Empty;
	REQUIRE(plusminus(s7, token, true) == -3);
}
