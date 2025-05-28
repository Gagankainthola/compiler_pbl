#include "parser.h"
#include <stdexcept>
#include <cstdlib>
#include<iostream>
using namespace std;
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
const Token& Parser::consume(TokenType type, const string& errorMessage) {
    if (peek().type == type) {
        return advance();
    }
    throw runtime_error(errorMessage);
}

std::unique_ptr<Stmt> Parser::statement() {
     if (match(TokenType::WHILE)) {
        return whileStatement();
    }
    if (match(TokenType::LET)) {
        std::string name = advance().value;
        match(TokenType::ASSIGN);
        auto expr = expression();
        match(TokenType::SEMICOLON);
        return make_unique<LetStmt>(name, move(expr));
    }
    if (match(TokenType::PRINT)) {
        auto expr = expression();
        match(TokenType::SEMICOLON);
        return make_unique<PrintStmt>(move(expr));
    }
    throw std::runtime_error("Unknown statement");
}



unique_ptr<Expr> Parser::addition() {
    auto expr = multiplication();
    while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        Token op = tokens[pos - 1];
        auto right = multiplication();
        expr = std::make_unique<BinaryExpr>(move(expr),move(right), op.type);
    }
    return expr;
}

unique_ptr<Expr> Parser::multiplication() {
    auto expr = primary();
    while (match(TokenType::STAR) || match(TokenType::SLASH)) {
        Token op = tokens[pos - 1];
        auto right = primary();
        expr = std::make_unique<BinaryExpr>(move(expr), move(right), op.type);
    }
    return expr;
}
unique_ptr<Stmt> Parser::whileStatement() {
    consume(TokenType::LPAREN, "Expect '(' after 'while'.");
    auto condition = expression();
    consume(TokenType::RPAREN, "Expect ')' after while condition.");
    auto body = statement();
    return std::make_unique<WhileStmt>(move(condition), move(body));
}

unique_ptr<Expr> Parser::primary() {
    if (match(TokenType::NUMBER))
        return std::make_unique<NumberExpr>(std::stoi(tokens[pos - 1].value));
    if (match(TokenType::IDENTIFIER))
        return std::make_unique<VarExpr>(tokens[pos - 1].value);
    throw std::runtime_error("Invalid expression");
}

vector<std::unique_ptr<Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<Stmt>> program;
    while (peek().type != TokenType::END)
        program.push_back(statement());
    return program;
}
unique_ptr<Expr> Parser::expression() {
    return equality();
}

unique_ptr<Expr> Parser::equality() {
    auto expr = comparison();

    while (match(TokenType::EQUAL_EQUAL) /*|| match other equality tokens*/) {
        Token op = tokens[pos - 1];
        auto right = comparison();
        expr = std::make_unique<BinaryExpr>(std::move(expr), move(right), op.type);
    }
    return expr;
}

unique_ptr<Expr> Parser::comparison() {
    auto expr = addition();

    while (match(TokenType::LESS) || match(TokenType::GREATER)) {
        Token op = tokens[pos - 1];
        auto right = addition();
        expr = make_unique<BinaryExpr>(std::move(expr), move(right), op.type);
    }
    return expr;
}

