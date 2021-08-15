//
// Created by ds123 on 2021/7/3.
//

#ifndef EASY_COMPILER_TOOLS_H
#define EASY_COMPILER_TOOLS_H

#include "ast.h"
#include <iostream>
#include <memory>
#include <tuple>

std::unique_ptr<ExprAst> LogError(const char *message);

template <typename out_type, typename in_type>
std::unique_ptr<out_type> ptr_cast(in_type in) {
  auto *ptr = dynamic_cast<out_type *>(in.get());
  std::unique_ptr<out_type> new_value;
  if (ptr != nullptr) {
    in.release();
    new_value.reset(ptr);
  }
  return new_value;
}

#endif // EASY_COMPILER_TOOLS_H
