//
// Created by ds123 on 2021/6/14.
//

#ifndef EASY_COMPILER_PARSER_H
#define EASY_COMPILER_PARSER_H

#include "ast.h"
#include "lexer.h"
#include "tools.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <unordered_map>

std::unordered_map<std::string, std::unique_ptr<FuncAST>> func_definitons;

// from C operator precedence: the lower the number, the higher the priority
static const std::unordered_map<std::string, int>
    BinaryOpPrecedence({{"*", 3},
                        {"/", 3},
                        {"+", 4},
                        {"-", 4},
                        {">", 6},
                        {"<", 6},
                        {"==", 7},
                        {"=", 14}});

#endif // EASY_COMPILER_PARSER_H
