//
// Created by SENSETIME\mupei on 2021/6/7.
//

#ifndef EASY_COMPILER_LEXER_H
#define EASY_COMPILER_LEXER_H

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#define RESET "\033[0m"
#define BLUE "\033[34m"
#define BOLDWHITE "\033[1m\033[31m"

namespace lexer {
enum TOKEN_TYPE {
  KeyWord = 1,
  LiteralNum,
  LiteralString,
  Operator,
  Separator,
  Identifier,
  NotDefine,
  TOKEN_EOF,
};

static const std::unordered_set<std::string> KeyWordSet(
    {"if", "else", "for", "while", "return", "let", "def", "true", "false"});

static const std::unordered_set<std::string> OperatorSet({"*", "/", "+", "-",
                                                          "!", ">", "<", "="});

static const std::unordered_set<std::string> ExpandOperatorSet({">=", "<=",
                                                                "==", "!="});

static const std::unordered_set<std::string> SeparatorSet({"{", "}", "(", ")",
                                                           "[", "]", ";"});

extern TOKEN_TYPE CurrentToken;
extern std::string TokenStr;
extern double NumberValue;

void GetToken();
} // namespace lexer

#endif // EASY_COMPILER_LEXER_H
