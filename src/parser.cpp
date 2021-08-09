//
// Created by ds123 on 2021/6/14.
//

#include "parser.h"

/*
 * parse number to const expr
 */
std::unique_ptr<ExprAST> ParseConstExpr() {
  auto result = std::make_unique<ConstAST>(lexer::NumberValue);
  lexer::GetToken(); // consume number
  return std::move(result);
}

/*
 * parse '(' some_expr ')'
 */
std::unique_ptr<ExprAST> ParseParenExpr() {
  lexer::GetToken(); // eat '('
  auto expr = ParsePrimary();
  if (nullptr == expr)
    return nullptr;

  if (lexer::TokenStr != ")")
    return LogError("expexted ')'");

  lexer::GetToken(); // eat ')'
  return expr;
}

/*
 * parse identifier or function name
 */
std::unique_ptr<ExprAST> ParseIdentifierExpr() {
  std::string id_name = lexer::TokenStr;

  lexer::GetToken(); // eat identifier

  if (lexer::TokenStr != "(") // simple variable ref
    return std::make_unique<VarAST>(id_name);

  // function
  auto iter = func_definitons.find(id_name);
  if (iter == func_definitons.end()) {
    char err[] = "No such function: ";
    LogError(strcat(err, id_name.c_str()));
  }
  std::unique_ptr<FuncAST> id_func = std::move(iter->second);
  lexer::GetToken(); // eat '('
  std::vector<std::unique_ptr<ExprAST>> args;
  while (lexer::TokenStr != ")") {
    if (auto arg = ParsePrimary())
      args.emplace_back(std::move(arg));
    else
      return nullptr;

    if (lexer::TokenStr != ", ")
      return LogError("Expected ')' or ',' in argument list");

    lexer::GetToken();
  }

  // eat the ')'
  lexer::GetToken();

  return std::make_unique<CallAST>(std::move(id_func), args);
}

/*
 * parse primary
 * to choose which kind of Expr or Stmt to parse
 */
std::unique_ptr<ExprAST> ParsePrimary() {
  switch (lexer::CurrentToken) {
  case lexer::LiteralNum:
    return ParseConstExpr();
  case lexer::Separator:
    return ParseParenExpr();
  case lexer::Identifier:
    return ParseIdentifierExpr();
  default:
    LogError("No implementation yet.");
  }
}

/*
 * parse expression
 */
std::unique_ptr<ExprAST> ParseStmt() {
  auto lhs = ParsePrimary();
  if (nullptr == lhs) {
    return nullptr;
  }

  return P
}
