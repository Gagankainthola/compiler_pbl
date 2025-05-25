#pragma once
#include "token.h"
#include <vector>
#include <string>

class Lexer {
public:
    explicit Lexer(const std::string &input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t pos = 0;

    char peek();
    char advance();
    void skipWhitespace();
    Token identifier();
    Token number();
};
