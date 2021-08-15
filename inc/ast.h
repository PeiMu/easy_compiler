//
// Created by ds123 on 2021/6/14.
//

#ifndef EASY_COMPILER_AST_H
#define EASY_COMPILER_AST_H
#include <memory>
#include <string>
#include <utility>
#include <vector>

class NodeAst {
public:
  NodeAst() = default;
  virtual ~NodeAst() = default;
};

class ExprAst : public NodeAst {
public:
  ExprAst() = default;
  ~ExprAst() override = default;
};

class VarExpr final : public ExprAst {
public:
  explicit VarExpr(std::string variable_value)
      : variable_value_(std::move(variable_value)) {}
  ~VarExpr() override = default;

  const std::string variable_value_;
};

class ConstExpr final : public ExprAst {
public:
  explicit ConstExpr(double constant_value) : constant_value_(constant_value) {}
  ~ConstExpr() override = default;

  double constant_value_;
};

class UnaryExpr final : public ExprAst {
public:
  enum UnaryOP {
    Not = 1,
  };
  explicit UnaryExpr(UnaryOP op, std::unique_ptr<ExprAst> operand)
      : operator_(op), operands_(std::move(operand)) {}
  ~UnaryExpr() override = default;

  const UnaryOP operator_;
  const std::unique_ptr<ExprAst> operands_;
};

class BinaryExpr final : public ExprAst {
public:
  enum BinaryOP {
    Add = 1,
    Sub,
    Mul,
    Div,
  };
  explicit BinaryExpr(BinaryOP op, std::unique_ptr<ExprAst> lhs,
                      std::unique_ptr<ExprAst> rhs)
      : operator_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
  ~BinaryExpr() override = default;

  const BinaryOP operator_;
  const std::unique_ptr<const ExprAst> lhs_;
  const std::unique_ptr<const ExprAst> rhs_;
};

class LogicalExpr final : public ExprAst {
public:
  enum LogicalOP {
    Equal = 1,
    NotEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,
  };
  explicit LogicalExpr(LogicalOP op, std::unique_ptr<ExprAst> lhs,
                       std::unique_ptr<ExprAst> rhs)
      : operator_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
  ~LogicalExpr() override = default;

  const LogicalOP operator_;
  const std::unique_ptr<ExprAst> lhs_;
  const std::unique_ptr<ExprAst> rhs_;
};

class StmtAst : public NodeAst {
public:
  StmtAst() = default;
  ~StmtAst() override = default;
};

class LetStmt final : public StmtAst {
public:
  explicit LetStmt(std::unique_ptr<VarExpr> lhs, std::unique_ptr<ExprAst> rhs)
      : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
  ~LetStmt() override = default;

  std::unique_ptr<VarExpr> lhs_;
  std::unique_ptr<ExprAst> rhs_;
};

class BlockStmt final : public StmtAst {
public:
  explicit BlockStmt(std::unique_ptr<StmtAst> head_body,
                     std::unique_ptr<StmtAst> tail_body)
      : head_body_(std::move(head_body)), tail_body_(std::move(tail_body)) {}
  ~BlockStmt() override = default;

  const std::unique_ptr<StmtAst> head_body_;
  const std::unique_ptr<StmtAst> tail_body_;
};

class IfStmt final : public StmtAst {
public:
  explicit IfStmt(std::unique_ptr<ExprAst> condition,
                  std::vector<std::unique_ptr<StmtAst>> then_body,
                  std::vector<std::unique_ptr<StmtAst>> else_body)
      : condition_(std::move(condition)), then_body_(std::move(then_body)),
        else_body_(std::move(else_body)) {}
  ~IfStmt() override = default;

  const std::unique_ptr<ExprAst> condition_;
  const std::vector<std::unique_ptr<StmtAst>> then_body_;
  const std::vector<std::unique_ptr<StmtAst>> else_body_;
};

class ForStmt final : public StmtAst {
public:
  explicit ForStmt(std::unique_ptr<VarExpr> iter_var,
                   std::unique_ptr<VarExpr> init,
                   std::unique_ptr<VarExpr> extent,
                   std::unique_ptr<VarExpr> stride,
                   std::unique_ptr<BlockStmt> for_body)
      : iter_var_(std::move(iter_var)), init_(std::move(init)),
        extent_(std::move(extent)), stride_(std::move(stride)),
        for_body_(std::move(for_body)) {}

  explicit ForStmt(std::unique_ptr<VarExpr> iter_var,
                   std::unique_ptr<VarExpr> init,
                   std::unique_ptr<VarExpr> extent,
                   std::unique_ptr<BlockStmt> for_body)
      : iter_var_(std::move(iter_var)), init_(std::move(init)),
        extent_(std::move(extent)), for_body_(std::move(for_body)),
        stride_(std::make_unique<VarExpr>("1")) {}

  ~ForStmt() override = default;

  const std::unique_ptr<VarExpr> iter_var_;
  const std::unique_ptr<VarExpr> init_;
  const std::unique_ptr<VarExpr> extent_;
  const std::unique_ptr<VarExpr> stride_;
  const std::unique_ptr<BlockStmt> for_body_;
};

class AttrStmt final : public StmtAst {
public:
  explicit AttrStmt(std::string attribute) : attribute_(std::move(attribute)) {}
  ~AttrStmt() override = default;

  const std::string attribute_;
};

class FuncStmt final : public StmtAst {
public:
  explicit FuncStmt(std::string name, std::unique_ptr<ExprAst> result,
                    std::vector<std::unique_ptr<ExprAst>> params,
                    std::unique_ptr<BlockStmt> body)
      : name_(std::move(name)), result_(std::move(result)),
        params_(std::move(params)), body_(std::move(body)) {}
  ~FuncStmt() override = default;

  const std::string name_;
  const std::unique_ptr<ExprAst> result_;
  const std::vector<std::unique_ptr<ExprAst>> params_;
  const std::unique_ptr<BlockStmt> body_;
};

class CallExpr final : public ExprAst {
public:
  explicit CallExpr(std::unique_ptr<FuncStmt> callee,
                    std::vector<std::unique_ptr<ExprAst>> param)
      : callee_(std::move(callee)), params_(std::move(param)) {}
  ~CallExpr() override = default;

  const std::unique_ptr<FuncStmt> callee_;
  const std::vector<std::unique_ptr<ExprAst>> params_;
};

#endif // EASY_COMPILER_AST_H
