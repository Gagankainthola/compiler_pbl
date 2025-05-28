#pragma once
#include "token.h"
#include <vector>
#include <string>
using namespace std;
class Lexer {
public:
    explicit Lexer(const std::string &input);
    vector<Token> tokenize();

private:
    string input;
    size_t pos = 0;

    char peek();
    char advance();
    void skipWhitespace();
    Token identifier();
    Token number();
};
