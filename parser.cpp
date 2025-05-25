#include "parser.h"
#include <stdexcept>
#include <cstdlib>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

const Token &Parser::peek() {
    return tokens[pos];
}

const Token &Parser::advance() {
    return tokens[pos++];
}

bool Parser::match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

std::unique_ptr<Stmt> Parser::statement() {
    if (match(TokenType::LET)) {
        std::string name = advance().value;
        match(TokenType::ASSIGN);
        auto expr = expression();
        match(TokenType::SEMICOLON);
        return std::make_unique<LetStmt>(name, std::move(expr));
    }
    if (match(TokenType::PRINT)) {
        auto expr = expression();
        match(TokenType::SEMICOLON);
        return std::make_unique<PrintStmt>(std::move(expr));
    }
    throw std::runtime_error("Unknown statement");
}

std::unique_ptr<Expr> Parser::expression() {
    auto left = primary();
    if (match(TokenType::PLUS)) {
        auto right = primary();
        return std::make_unique<BinaryExpr>(std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<Expr> Parser::primary() {
    if (match(TokenType::NUMBER))
        return std::make_unique<NumberExpr>(std::stoi(tokens[pos - 1].value));
    if (match(TokenType::IDENTIFIER))
        return std::make_unique<VarExpr>(tokens[pos - 1].value);
    throw std::runtime_error("Invalid expression");
}

std::vector<std::unique_ptr<Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<Stmt>> program;
    while (peek().type != TokenType::END)
        program.push_back(statement());
    return program;
}
