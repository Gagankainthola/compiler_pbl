#pragma once
#include "token.h"
#include "ast.h"
#include <vector>
#include <memory>
#include <string>  
using namespace std;

class Parser {
public:
    explicit Parser(const std::vector<Token> &tokens);
    vector<std::unique_ptr<Stmt>> parse();
    unique_ptr<Expr> addition();
    unique_ptr<Expr> multiplication();
    unique_ptr<Stmt> whileStatement();

    unique_ptr<Expr> equality();   
    unique_ptr<Expr> comparison(); 

private:
    vector<Token> tokens;
    size_t pos = 0;

    const Token &peek();
    const Token &advance();
    bool match(TokenType type);

    const Token &consume(TokenType type, const std::string &errorMessage);  // <-- added

    unique_ptr<Stmt> statement();
    unique_ptr<Expr> expression();
    unique_ptr<Expr> primary();
};
