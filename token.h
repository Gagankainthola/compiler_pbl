#pragma once
#include <string>

enum class TokenType {
    LET, IDENTIFIER, NUMBER, ASSIGN, PLUS, SEMICOLON, PRINT, END
};

struct Token {
    TokenType type;
    std::string value;
};
