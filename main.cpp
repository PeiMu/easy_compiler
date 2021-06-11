#include "lexer.h"
#include <iostream>

int main() {
  std::cout << BOLDWHITE << "enjoy it! :)" << RESET << std::endl;
  std::cout << "input >" << std::endl;
  lexer::LexerTester();
  std::cout << BOLDWHITE << "\nbye~" << RESET << std::endl;
  return 0;
}
