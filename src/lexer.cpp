//
// Created by SENSETIME\mupei on 2021/6/7.
//

#include "lexer.h"
namespace lexer {
TOKEN_TYPE CurrentToken = NotDefine;
std::string TokenStr;
double NumberValue = 0.0;

void GetToken() {
  static char last_char = ' ';
  CurrentToken = NotDefine;

  // skip any white space
  while (isspace(last_char))
    last_char = (char)getchar();

  if (isalpha(last_char)) {
    // including: key word, and identifier
    TokenStr = last_char;
    while (isalnum((last_char = (char)getchar())))
      TokenStr += last_char;

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

  } else if (last_char == '#' || (last_char == '/' && (char)getchar() == '/')) {
    // comment until end of line
    do
      last_char = (char)getchar();
    while (last_char != EOF && last_char != '\n' && last_char != '\r');

    if (last_char != EOF)
      GetToken();

  } else if (last_char == '\"' || last_char == '\'') {
    auto literal_str_symbol = last_char;
    // literal string
    TokenStr = last_char;
    do {
      last_char = (char)getchar();
      TokenStr += last_char;
    } while (last_char != EOF && last_char != literal_str_symbol);
    if (literal_str_symbol == '\'')
      assert(TokenStr.size() <= 3); // the symbol '\'' can only contain a char
    last_char = (char)getchar();
    CurrentToken = LiteralString;

  } else if (ispunct(last_char)) {
    TokenStr = last_char;
    CurrentToken = OperatorSet.find(TokenStr) != OperatorSet.end()
                       ? Operator
                       : CurrentToken;
    CurrentToken = SeparatorSet.find(TokenStr) != SeparatorSet.end()
                       ? Separator
                       : CurrentToken;

    last_char = (char)getchar();
    std::string tmp_token_str = TokenStr + last_char;
    if (ExpandOperatorSet.find(tmp_token_str) != ExpandOperatorSet.end()) {
      TokenStr = tmp_token_str;
      last_char = (char)getchar();
    }

  } else if (last_char == EOF) {
    CurrentToken = TOKEN_EOF;

  } else {
    std::cerr << "\nUnknown char: " << last_char << std::endl;
    assert(CurrentToken != NotDefine);
  }

  if (CurrentToken == NotDefine) {
    std::cerr << "\nDo not support such token: " << TokenStr << std::endl;
  }
}
} // namespace lexer
