#pragma once
#include "ast.h"
#include <unordered_map>

class Interpreter {
public:
    void execute(const std::vector<std::unique_ptr<Stmt>> &program);

private:
    std::unordered_map<std::string, int> variables;
    int evaluate(Expr *expr);
};
