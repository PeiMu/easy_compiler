//
// Created by ds123 on 2021/7/3.
//

#include "tools.h"

std::unique_ptr<ExprAst> LogError(const char *message) {
  fprintf(stderr, "LogError: %s", message);
  return nullptr;
}
