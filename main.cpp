#include <iostream>
#include "lexer.h"

int main() {
	std::cout << BOLDWHITE << "enjoy it! :)" << RESET << std::endl;
	std::cout << "input >" << std::endl;
	lexer::LexerTester();
	std::cout << BOLDWHITE << "bye~" << RESET << std::endl;
	return 0;
}
