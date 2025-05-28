#pragma once
#include <string>
#include <memory>
#include <vector>
#include "token.h"
using namespace std;
struct Expr {
    virtual ~Expr() = default;
};

struct NumberExpr : Expr {
    int value;
    explicit NumberExpr(int v) : value(v) {}
};

struct VarExpr : Expr {
    std::string name;
    explicit VarExpr(const std::string &n) : name(n) {}
};

struct BinaryExpr : Expr {
    std::unique_ptr<Expr> left, right;
    TokenType op;
    BinaryExpr(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r, TokenType o)
        : left(std::move(l)), right(std::move(r)), op(o) {}
};


struct Stmt {
    virtual ~Stmt() = default;
};

struct LetStmt : Stmt {
    string name;
    unique_ptr<Expr> expr;
    LetStmt(const std::string &n, std::unique_ptr<Expr> e)
        : name(n), expr(std::move(e)) {}
};

struct PrintStmt : Stmt {
    unique_ptr<Expr> expr;
    explicit PrintStmt(std::unique_ptr<Expr> e) : expr(std::move(e)) {}
};

class WhileStmt : public Stmt {
public:
    unique_ptr<Expr> condition;
    unique_ptr<Stmt> body;

    WhileStmt(std::unique_ptr<Expr> cond, std::unique_ptr<Stmt> bodyStmt)
        : condition(std::move(cond)), body(std::move(bodyStmt)) {}
};