#include "lexer.h"
#include <cctype>
using namespace std;
Lexer::Lexer(const std::string &input) : input(input) {}

char Lexer::peek() {
    return pos < input.size() ? input[pos] : '\0';
}

char Lexer::advance() {
    return pos < input.size() ? input[pos++] : '\0';
}

void Lexer::skipWhitespace() {
    while (isspace(peek())) advance();
}

Token Lexer::identifier() {
    string result;
    while (isalnum(peek())) result += advance();
    if (result == "let") return {TokenType::LET, result};
    if (result == "print") return {TokenType::PRINT, result};
    if (result == "while") return {TokenType::WHILE, result};
    return {TokenType::IDENTIFIER, result};
}

Token Lexer::number() {
    string result;
    while (isdigit(peek())) result += advance();
    return {TokenType::NUMBER, result};
}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    while (peek() != '\0') {
        skipWhitespace();
        char current = peek();
        if (isalpha(current)) tokens.push_back(identifier());
        else if (isdigit(current)) tokens.push_back(number());
        else {
            switch (advance()) {
                case '=': tokens.push_back({TokenType::ASSIGN, "="}); break;
                case '+': tokens.push_back({TokenType::PLUS, "+"}); break;
                case ';': tokens.push_back({TokenType::SEMICOLON, ";"}); break;
                case '-': tokens.push_back({TokenType::MINUS, "-"}); break;
                case '*': tokens.push_back({TokenType::STAR, "*"}); break;
                case '(': tokens.push_back({TokenType::LPAREN, "("}); break;    // Add this
                case ')': tokens.push_back({TokenType::RPAREN, ")"}); break; 
                case '/': tokens.push_back({TokenType::SLASH, "/"}); break;
                 case '<':tokens.push_back({TokenType::LESS, "<"});break;
                   case '>': tokens.push_back({TokenType::GREATER, ">"}); break;
            }
        }
    }
    tokens.push_back({TokenType::END, ""});
    return tokens;
}
