//
// Created by ds123 on 2021/6/14.
//

#ifndef EASY_COMPILER_AST_H
#define EASY_COMPILER_AST_H
#include <memory>
#include <string>
#include <utility>
#include <vector>

class NodeAST {
public:
  NodeAST() = default;
  virtual ~NodeAST() = default;
};

class ExprAST : public NodeAST {
public:
  ExprAST() = default;
  ~ExprAST() override = default;
};

class VarAST final : public ExprAST {
public:
  explicit VarAST(std::string variable_value)
      : variable_value_(std::move(variable_value)) {}
  ~VarAST() override = default;

  const std::string variable_value_;
};

class ConstAST final : public ExprAST {
public:
  explicit ConstAST(double constant_value) : constant_value_(constant_value) {}
  ~ConstAST() override = default;

  double constant_value_;
};

class UnaryAST final : public ExprAST {
public:
  enum UnaryOP {
    Not = 1,
  };
  explicit UnaryAST(UnaryOP op, std::unique_ptr<ExprAST> operand)
      : operator_(op), operands_(std::move(operand)) {}
  ~UnaryAST() override = default;

  const UnaryOP operator_;
  const std::unique_ptr<ExprAST> operands_;
};

class BinaryAST final : public ExprAST {
public:
  enum BinaryOP {
    Add = 1,
    Sub,
    Mul,
    Div,
  };
  explicit BinaryAST(BinaryOP op, std::unique_ptr<ExprAST> lhs,
                     std::unique_ptr<ExprAST> rhs)
      : operator_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
  ~BinaryAST() override = default;

  const BinaryOP operator_;
  const std::unique_ptr<const ExprAST> lhs_;
  const std::unique_ptr<const ExprAST> rhs_;
};

class LogicalAST final : public ExprAST {
public:
  enum LogicalOP {
    Equal = 1,
    NotEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,
  };
  explicit LogicalAST(LogicalOP op, std::unique_ptr<ExprAST> lhs,
                      std::unique_ptr<ExprAST> rhs)
      : operator_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
  ~LogicalAST() override = default;

  const LogicalOP operator_;
  const std::unique_ptr<ExprAST> lhs_;
  const std::unique_ptr<ExprAST> rhs_;
};

class StmtAST : public NodeAST {
public:
  StmtAST() = default;
  ~StmtAST() override = default;
};

class LetAST final : public StmtAST {
public:
  explicit LetAST(std::unique_ptr<VarAST> lhs, std::unique_ptr<ExprAST> rhs)
      : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
  ~LetAST() override = default;

  const std::unique_ptr<VarAST> lhs_;
  const std::unique_ptr<ExprAST> rhs_;
};

class IfAST final : public StmtAST {
public:
  explicit IfAST(std::unique_ptr<ExprAST> condition,
                 std::vector<std::unique_ptr<StmtAST>> then_body,
                 std::vector<std::unique_ptr<StmtAST>> else_body)
      : condition_(std::move(condition)), then_body_(std::move(then_body)),
        else_body_(std::move(else_body)) {}
  ~IfAST() override = default;

  const std::unique_ptr<ExprAST> condition_;
  const std::vector<std::unique_ptr<StmtAST>> then_body_;
  const std::vector<std::unique_ptr<StmtAST>> else_body_;
};

class ForAST final : public StmtAST {
public:
  explicit ForAST(std::unique_ptr<ExprAST> condition,
                  std::vector<std::unique_ptr<StmtAST>> for_body)
      : condition_(std::move(condition)), for_body_(std::move(for_body)) {}
  ~ForAST() override = default;

  const std::unique_ptr<ExprAST> condition_;
  const std::vector<std::unique_ptr<StmtAST>> for_body_;
};

class BlockAST final : public StmtAST {
public:
  explicit BlockAST(std::vector<std::unique_ptr<StmtAST>> head_body,
                    std::vector<std::unique_ptr<StmtAST>> tail_body)
      : head_body_(std::move(head_body)), tail_body_(std::move(tail_body)) {}
  ~BlockAST() override = default;

  const std::vector<std::unique_ptr<StmtAST>> head_body_;
  const std::vector<std::unique_ptr<StmtAST>> tail_body_;
};

class AttrAST final : public StmtAST {
public:
  explicit AttrAST(std::string attribute) : attribute_(std::move(attribute)) {}
  ~AttrAST() override = default;

  const std::string attribute_;
};

class FuncAST final : public StmtAST {
public:
  explicit FuncAST(std::string name, std::unique_ptr<ExprAST> result,
                   std::vector<std::unique_ptr<ExprAST>> params,
                   std::vector<std::unique_ptr<StmtAST>> body)
      : name_(std::move(name)), result_(std::move(result)),
        params_(std::move(params)), body_(std::move(body)) {}
  ~FuncAST() override = default;

  const std::string name_;
  const std::unique_ptr<ExprAST> result_;
  const std::vector<std::unique_ptr<ExprAST>> params_;
  const std::vector<std::unique_ptr<StmtAST>> body_;
};

class CallAST final : public ExprAST {
public:
  explicit CallAST(std::unique_ptr<FuncAST> callee,
                   std::vector<std::unique_ptr<ExprAST>> param)
      : callee_(std::move(callee)), params_(std::move(param)) {}
  ~CallAST() override = default;

  const std::unique_ptr<FuncAST> callee_;
  const std::vector<std::unique_ptr<ExprAST>> params_;
};

#endif // EASY_COMPILER_AST_H
