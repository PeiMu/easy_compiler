//
// Created by ds123 on 2021/6/14.
//

#include "parser.h"

namespace parser {
std::unordered_map<std::string, std::unique_ptr<FuncStmt>> func_definitons;

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

static inline std::unique_ptr<ExprAst> ParsePrimaryExpr();

/*
 * parse number to const expr
 */
static inline std::unique_ptr<ExprAst> ParseConstExpr() {
  auto result = std::make_unique<ConstExpr>(lexer::NumberValue);
  lexer::GetToken(); // consume number
  return std::move(result);
}

/*
 * parse '(' some_expr ')'
 */
static inline std::unique_ptr<ExprAst> ParseSeparatorExpr() {
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
static inline std::unique_ptr<ExprAst> ParseIdentifierExpr() {
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

static inline std::unique_ptr<ExprAst> ParseLiteralExpr() {
  std::string id_name = lexer::TokenStr;
  lexer::GetToken(); // eat literal string

  return std::make_unique<VarExpr>(id_name);
}

static inline std::unique_ptr<ExprAst> ParseOperatorExpr() {
  return std::unique_ptr<ExprAst>();
}

/*
 * parse primary
 * to choose which kind of Expr or Stmt to parse
 */
static inline std::unique_ptr<ExprAst> ParsePrimaryExpr() {
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
    LogError("Token Error!");
  }
}

static inline constexpr unsigned int str2int(const char *str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

static inline std::unique_ptr<StmtAst> ParseIfStmt() {
  return std::unique_ptr<StmtAst>();
}

static inline std::unique_ptr<StmtAst> ParseForStmt() {
  return std::unique_ptr<StmtAst>();
}

static inline std::unique_ptr<StmtAst> ParseWhileStmt() {
  return std::unique_ptr<StmtAst>();
}

static inline std::unique_ptr<StmtAst> ParseLetStmt() {
  return std::unique_ptr<StmtAst>();
}

static inline std::unique_ptr<StmtAst> ParseDefStmt() {
  return std::unique_ptr<StmtAst>();
}

static inline std::tuple<std::unique_ptr<StmtAst>, std::unique_ptr<ExprAst>>
ParseFuncBody() {
  std::vector<std::unique_ptr<StmtAst>> func_body_vec;
  std::unique_ptr<ExprAst> return_val = nullptr;
  while (lexer::CurrentToken != lexer::TOKEN_EOF) {
    // we must meet keyword or function call at first
    if (lexer::CurrentToken != lexer::KeyWord) {
      assert(lexer::CurrentToken == lexer::Identifier);
      auto func_call = ParseIdentifierExpr();
      assert(typeid(func_call).name() ==
             typeid(std::unique_ptr<CallExpr>).name());
      // construct an anonymous let stmt to include CallExpr.
      auto anonymous_let =
          std::make_unique<LetStmt>(nullptr, std::move(func_call));
      func_body_vec.emplace_back(std::move(anonymous_let));
    }
    lexer::GetToken();
    switch (str2int(lexer::TokenStr.c_str())) {
    case str2int("if"):
      func_body_vec.emplace_back(ParseIfStmt());
      break;
    case str2int("for"):
      func_body_vec.emplace_back(ParseForStmt());
      break;
    case str2int("while"):
      func_body_vec.emplace_back(ParseWhileStmt());
      break;
    case str2int("let"):
      func_body_vec.emplace_back(ParseLetStmt());
      break;
    case str2int("def"):
      func_body_vec.emplace_back(ParseDefStmt());
      break;
    case str2int("return"):
      lexer::GetToken();
      return_val = ParsePrimaryExpr();
      break;
    }
  }

  auto func_body =
      std::make_unique<BlockStmt>(std::move(func_body_vec.back()), nullptr);
  for (auto it = func_body_vec.rbegin() + 1; it != func_body_vec.rend(); it++) {
    auto tmp_link_node =
        std::make_unique<BlockStmt>(std::move(*it), std::move(func_body));
    func_body = std::move(tmp_link_node);
  }

  return std::make_tuple(std::move(func_body), std::move(return_val));
}

void ParserDriver() {
  // sometimes, we might regard the source code as a big function body
  std::unique_ptr<StmtAst> stmt_block;
  std::unique_ptr<ExprAst> null_ret;
  std::tie(stmt_block, null_ret) = ParseFuncBody();
  assert(null_ret == nullptr);
}
}
