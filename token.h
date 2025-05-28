#pragma once
#include <string>
using namespace std;
enum class TokenType {
    PLUS, MINUS, STAR, SLASH, NUMBER, IDENTIFIER, LPAREN, RPAREN, END   ,LET,
    PRINT,
    ASSIGN,
    SEMICOLON,
    WHILE,
     LESS,       // '<'
    GREATER,    // '>'
    EQUAL_EQUAL, 
};
struct Token {
    TokenType type;
    string value;
     Token(TokenType t, const string& v) : type(t), value(v) {}
};
