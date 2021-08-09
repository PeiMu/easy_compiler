//
// Created by ds123 on 2021/7/3.
//

#ifndef EASY_COMPILER_TOOLS_H
#define EASY_COMPILER_TOOLS_H

#include "ast.h"
#include <iostream>
#include <memory>
#include <tuple>

std::unique_ptr<ExprAST> LogError(const char *message);

#endif // EASY_COMPILER_TOOLS_H
