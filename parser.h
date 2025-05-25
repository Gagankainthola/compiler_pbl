#pragma once
#include "token.h"
#include "ast.h"
#include <vector>
#include <memory>

class Parser {
public:
    explicit Parser(const std::vector<Token> &tokens);
    std::vector<std::unique_ptr<Stmt>> parse();

private:
    std::vector<Token> tokens;
    size_t pos = 0;

    const Token &peek();
    const Token &advance();
    bool match(TokenType type);

    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> primary();
};
