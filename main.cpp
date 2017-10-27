#include <iostream>
#include <string>
#include <stdexcept>
#include "calculator.hpp"

int main() {

	Token token;
	
	try {
		std::cout << "Welcome to calculator!\nPlease enter your expression: " << std::endl;
		get_token(std::cin, token);
		std::cout << plusminus(std::cin, token, false) << std::endl;
	}
	catch (std::runtime_error r) {
		std::cerr << "Error: " << r.what();
		return 1;
	}
	return 0;
}