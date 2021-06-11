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
  LiteralLogic,
  LiteralString,
  Operator,
  Separator,
  Identifier,
  NotDefine,
  TOKEN_EOF,
};

static const std::unordered_set<std::string>
    KeyWordSet({"if", "else", "for", "while", "return", "let", "def"});

static const std::unordered_set<std::string> LiteralLogicSet({"true", "false"});

static const std::unordered_set<std::string> OperatorSet({"*", "/", "+", "-",
                                                          "!", ">", "<", "="});

static const std::unordered_set<std::string> ExpandOperatorSet({">=", "<=",
                                                                "==", "!="});

static const std::unordered_set<std::string> SeparatorSet({"{", "}", "(", ")",
                                                           ";"});

static TOKEN_TYPE CurrentToken = NotDefine;
static std::string TokenStr;
static double NumberValue = 0.0;

//// from C operator precedence: the lower the number, the higher the priority
// static const std::unordered_map<std::string, int> BinaryOpPrecedence({{"*",
// 3},
//                                                         {"/", 3},
//                                                         {"+", 4},
//                                                         {"-", 4},
//                                                         {">", 6},
//                                                         {"<", 6},
//                                                         {"==", 7},
//                                                         {"=", 14}});

void GetToken();
void LexerTester();
}

#endif // EASY_COMPILER_LEXER_H
