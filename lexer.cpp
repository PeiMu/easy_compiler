//
// Created by SENSETIME\mupei on 2021/6/7.
//

#include "lexer.h"
namespace lexer {
void GetToken() {
  static char last_char = ' ';
  CurrentToken = NotDefine;

  // skip any white space
  while (isspace(last_char))
    last_char = (char)getchar();

  if (isalpha(last_char)) {
    // including: literal logic, key word, and identifier
    TokenStr = last_char;
    while (isalnum((last_char = (char)getchar())))
      TokenStr += last_char;

    CurrentToken = LiteralLogicSet.find(TokenStr) != LiteralLogicSet.end()
                       ? LiteralLogic
                       : CurrentToken;
    CurrentToken =
        KeyWordSet.find(TokenStr) != KeyWordSet.end() ? KeyWord : CurrentToken;
    CurrentToken = CurrentToken == NotDefine ? Identifier : CurrentToken;

  } else if (isdigit(last_char) || last_char == '.') {
    // literal number
    std::string num_str;
    do {
      num_str += last_char;
      last_char = (char)getchar();
    } while (isdigit(last_char) || last_char == '.');

    NumberValue = strtod(num_str.c_str(), nullptr);
    CurrentToken = LiteralNum;

  } else if (last_char == '#') {
    // comment until end of line
    do
      last_char = (char)getchar();
    while (last_char != EOF && last_char != '\n' && last_char != '\r');

    if (last_char != EOF)
      GetToken();
    CurrentToken = Comment;

  } else if (last_char == '\"' || last_char == '\'') {
    // literal string
    TokenStr = last_char;
    do {
      last_char = (char)getchar();
      TokenStr += last_char;
    } while (last_char != EOF && last_char != '\"' && last_char != '\'');
    CurrentToken = LiteralString;

  } else if (last_char == EOF) {
    CurrentToken = TOKEN_EOF;
  } else if (ispunct(last_char)){
    TokenStr.clear();
    do {
      TokenStr += last_char;
      last_char = (char )getchar();
    } while (ispunct(last_char) && last_char != ';');

    CurrentToken = OperatorSet.find(TokenStr) != OperatorSet.end()
                       ? Operator
                       : CurrentToken;
    CurrentToken = SeparatorSet.find(TokenStr) != SeparatorSet.end()
                       ? Separator
                       : CurrentToken;
  }

	try {
		if (CurrentToken == NotDefine) {
			std::cout << std::endl;
			std::cerr << TokenStr << std::endl;
			throw "Current token hasn't been defined!";
		}
	} catch (const char* msg) {
  	std::cerr << msg << std::endl;
  }
}

void LexerTester() {
	GetToken();
	std::cout << "[";
  while (CurrentToken != TOKEN_EOF) {
    switch (CurrentToken) {
    case KeyWord:
      std::cout << "(KeyWord, " << GREEN << TokenStr << RESET << "), ";
      break;
    case LiteralNum:
      std::cout << "(LiteralNum, " << GREEN << NumberValue << RESET<< "), ";
      break;
    case LiteralLogic:
      std::cout << "(LiteralLogic, " << GREEN << TokenStr << RESET<< "), ";
      break;
    case LiteralString:
      std::cout << "(LiteralString, " << GREEN << TokenStr << RESET<< "), ";
      break;
    case Operator:
      std::cout << "(Operator, " << GREEN << TokenStr << RESET<< "), ";
      break;
    case Separator:
      std::cout << "(Separator, " << GREEN << TokenStr << RESET<< "), ";
      if (TokenStr == ";")
        std::cout << "]" << std::endl;
      break;
    case Comment:
      std::cout << "(Comment, " << GREEN << TokenStr << RESET<< "), ";
      break;
    case Identifier:
      std::cout << "(Identifier, " << GREEN << TokenStr << RESET<< "), ";
      break;
    }
	  GetToken();
  }
}
}
