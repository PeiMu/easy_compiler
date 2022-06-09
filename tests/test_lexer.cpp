//
// Created by ds123 on 2021/8/7.
//
#include "lexer.h"

namespace lexer {
void LexerTester() {
  while (CurrentToken != TOKEN_EOF) {
    GetToken();
    std::cout << "tokenize to: ";
    switch (CurrentToken) {
    case KeyWord:
      std::cout << "(KeyWord, " << TokenStr << "), ";
      break;
    case LiteralNum:
      std::cout << "(LiteralNum, " << NumberValue << "), ";
      break;
    case LiteralString:
      std::cout << "(LiteralString, " << TokenStr << "), ";
      break;
    case Operator:
      std::cout << "(Operator, " << TokenStr << "), ";
      break;
    case Separator:
      std::cout << "(Separator, " << TokenStr << "), ";
      break;
    case Identifier:
      std::cout << "(Identifier, " << TokenStr << "), ";
      break;
    case NotDefine:
      std::cout << "(No Defined Token)";
      break;
    case TOKEN_EOF:
      return;
    }
  }
}
} // namespace lexer

void test_func() {
	std::cout << "test_func" << std::endl;
}

int main() {
  std::cout << "in test_lexer" << std::endl;
	test_func();
//  lexer::LexerTester();
  return 0;
}
