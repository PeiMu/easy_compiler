//
// Created by ds123 on 2021/6/14.
//

#include "parser.h"

/*
 * parse number to const expr
 */
std::unique_ptr<ExprAst> ParseConstExpr() {
  auto result = std::make_unique<ConstExpr>(lexer::NumberValue);
  lexer::GetToken(); // consume number
  return std::move(result);
}

/*
 * parse '(' some_expr ')'
 */
std::unique_ptr<ExprAst> ParseSeparatorExpr() {
  lexer::GetToken(); // eat '('
  auto expr = ParsePrimaryExpr();
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
std::unique_ptr<ExprAst> ParseIdentifierExpr() {
  std::string id_name = lexer::TokenStr;

  lexer::GetToken(); // eat identifier

  if (lexer::TokenStr != "(") // simple variable ref
    return std::make_unique<VarExpr>(id_name);

  // function
  auto iter = func_definitons.find(id_name);
  if (iter == func_definitons.end()) {
    char err[] = "No such function: ";
    LogError(strcat(err, id_name.c_str()));
  }
  std::unique_ptr<FuncStmt> id_func = std::move(iter->second);
  lexer::GetToken(); // eat '('
  std::vector<std::unique_ptr<ExprAst>> args;
  while (lexer::TokenStr != ")") {
    if (auto arg = ParsePrimaryExpr())
      args.emplace_back(std::move(arg));
    else
      return nullptr;

    if (lexer::TokenStr != ", ")
      return LogError("Expected ')' or ',' in argument list");

    lexer::GetToken();
  }

  // eat the ')'
  lexer::GetToken();

  return std::make_unique<CallExpr>(std::move(id_func), std::move(args));
}

std::unique_ptr<ExprAst> ParseLiteralExpr() {
  std::string id_name = lexer::TokenStr;
  lexer::GetToken(); // eat literal string

  return std::make_unique<VarExpr>(id_name);
}

std::unique_ptr<ExprAst> ParseOperatorExpr() {
  return std::unique_ptr<ExprAst>();
}

std::unique_ptr<StmtAst> ParseKeyWordExpr() {
  std::string id_name = lexer::TokenStr;
  assert(lexer::KeyWordSet.count(id_name) > 0);
  return std::unique_ptr<StmtAst>();
}

/*
 * parse primary
 * to choose which kind of Expr or Stmt to parse
 */
std::unique_ptr<ExprAst> ParsePrimaryExpr(std::unique_ptr<ExprAst> lhs) {
  switch (lexer::CurrentToken) {
  case lexer::LiteralString:
    return ParseLiteralExpr();
  case lexer::LiteralNum:
    return ParseConstExpr();
  case lexer::Operator:
    return ParseOperatorExpr();
  case lexer::Separator:
    return ParseSeparatorExpr();
  case lexer::Identifier:
    return ParseIdentifierExpr();
  default:
    LogError("No implementation yet.");
  }
}

static constexpr unsigned int str2int(const char *str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

static std::unique_ptr<StmtAst> ParseIfStmt() {
  return std::unique_ptr<StmtAst>();
}

static std::unique_ptr<StmtAst> ParseForStmt() {
  return std::unique_ptr<StmtAst>();
}

static std::unique_ptr<StmtAst> ParseWhileStmt() {
  return std::unique_ptr<StmtAst>();
}

static std::unique_ptr<StmtAst> ParseLetStmt() {
  return std::unique_ptr<StmtAst>();
}

static std::unique_ptr<StmtAst> ParseDefStmt() {
  return std::unique_ptr<StmtAst>();
}

std::unique_ptr<ExprAst> ParseFuncBody() {
  std::vector<std::unique_ptr<StmtAst>> func_body;
  while (lexer::CurrentToken != lexer::TOKEN_EOF) {
    lexer::GetToken();
    switch (str2int(lexer::TokenStr.c_str())) {
    case str2int("if"):
      func_body.emplace_back(ParseIfStmt());
      break;
    case str2int("for"):
      func_body.emplace_back(ParseForStmt());
      break;
    case str2int("while"):
      func_body.emplace_back(ParseWhileStmt());
      break;
    case str2int("let"):
      func_body.emplace_back(ParseLetStmt());
      break;
    case str2int("def"):
      func_body.emplace_back(ParseDefStmt());
      break;
    case str2int("return"):
      break;
    }
  }
  auto lhs = ParsePrimaryExpr();
  if (nullptr == lhs) {
    return nullptr;
  }

  return nullptr;
}
