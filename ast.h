#pragma once
#include <string>
#include <memory>
#include <vector>

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
    explicit BinaryExpr(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : left(std::move(l)), right(std::move(r)) {}
};

struct Stmt {
    virtual ~Stmt() = default;
};

struct LetStmt : Stmt {
    std::string name;
    std::unique_ptr<Expr> expr;
    LetStmt(const std::string &n, std::unique_ptr<Expr> e)
        : name(n), expr(std::move(e)) {}
};

struct PrintStmt : Stmt {
    std::unique_ptr<Expr> expr;
    explicit PrintStmt(std::unique_ptr<Expr> e) : expr(std::move(e)) {}
};
