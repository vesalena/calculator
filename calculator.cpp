#include <stdexcept>
#include <cmath>
#include "calculator.hpp"

std::string type2str(LexemeType token) {
	switch (token) {
	case Number:   return "number";
	case Plus:     return "plus";
	case Minus:    return "minus";
	case Mult:     return "multiplication";
	case Div:      return "division";
	case Lbracket: return "left bracket";
	case Rbracket: return "right bracket";
	case Eof:      return "end of file";
	default:
		return "";
	}
}

void get_token(std::istream& input, Token &token) {

	// skip whitespace
	if (token.c == Empty)
		input.get(token.c);
	while (input.good() && token.c == ' ') {
		input.get(token.c);
	}
	if (input.eof() || token.c == '\n') {
		token.type = Eof;
		return;
	}
	if (!input.good()) {
		throw std::runtime_error("bad input stream\n");
	}

	std::string digit = "";
	switch (token.c) {
		case '+': token.type = Plus;     input.get(token.c); return;
		case '-': token.type = Minus;    input.get(token.c); return;
		case '*': token.type = Mult;     input.get(token.c); return;
		case '/': token.type = Div;      input.get(token.c); return;
		case '(': token.type = Lbracket; input.get(token.c); return;
		case ')': token.type = Rbracket; input.get(token.c); return;
		case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': {

			// read number
			while (input.good() && (isdigit(token.c) || token.c == '.' || token.c == ',')) {
				digit += token.c;
				input.get(token.c);
			}
			// check
			int comma = 0;
			for (size_t i = 0; i < digit.length(); i++) {
				if (digit[i] == ',')
					digit[i] = '.';
				if (digit[i] == '.')
					comma++;
			}
			if (comma > 1) {
				std::string msg = "incorrect number \'" + digit + "\'\n";
				throw std::runtime_error(msg);
			}
			token.type = Number;
			token.value = stod(digit);
			token.value = (token.value * 100) / 100.;
			break;
		}
		default: {
			std::string msg = "unexpected symbol \'"; 
			msg += token.c;
			msg += "\'\n";
			throw std::runtime_error(msg);
		}
	}
}

double basic(std::istream& input, Token &token, bool need_token) {
	if (need_token)
		get_token(input, token);

	double x;
	switch (token.type) {
		case Number:
			x = token.value;
			get_token(input, token);
			return round(x * 100) / 100.;
		case Minus:
			return -basic(input, token, true);
		case Lbracket:
			x = plusminus(input, token, true);
			if (token.type != Rbracket) {
				throw std::runtime_error("\')\' not found\n");
			}
			get_token(input, token);
			return round(x * 100) / 100.;
		default:
			std::string msg = "unexpected token \'" + type2str(token.type) + "\'\n";
			throw std::runtime_error(msg);
	}
}

double multdiv(std::istream& input, Token &token, bool need_token) {
	double left = basic(input, token, need_token);
	while (true) {
		switch (token.type) {
			case Div:
				left /= basic(input, token, true); break;
			case Mult:
				left *= basic(input, token, true); break;
			default:
				return round(left * 100) / 100.;
		}
	}
}

double plusminus(std::istream& input, Token &token, bool need_token) {
	double left = multdiv(input, token, need_token);
	while (true) {
		switch (token.type) {
			case Plus:
				left += multdiv(input, token, true); break;
			case Minus:
				left -= multdiv(input, token, true); break;
			default:
				return round(left * 100) / 100.;
		}
	}
}
