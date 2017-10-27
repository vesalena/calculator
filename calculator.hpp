#pragma once
#include <iostream>
#include <string>

// Grammar of expression language.
// 
// calculator :=
//    plusminus
// 
// plusminus :=
//    plusminus + multdiv
//    plusminus - multdiv
//    multdiv
// 
// multdiv :=
//    multdiv / basic
//    multdiv * basic
//    basic
// 
// basic :=
//    NUMBER
//    -basic
//    (plusminus)

const char Empty = 0;

enum LexemeType {
	Number,
	Plus,
	Minus,
	Mult,
	Div,
	Lbracket,
	Rbracket,
	Eof,
};

struct Token {
	LexemeType type;
	double value;
	char c = Empty;
};

std::string type2str(LexemeType token);
void get_token(std::istream& input, Token &token);
double basic(std::istream& input, Token &token, bool need_token);
double multdiv(std::istream& input, Token &token, bool need_token);
double plusminus(std::istream& input, Token &token, bool need_token);
