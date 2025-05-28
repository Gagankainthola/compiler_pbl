#pragma once
#include "ast.h"
#include <unordered_map>
using namespace std;
class Interpreter {
public:
    void execute(const std::vector<std::unique_ptr<Stmt>> &program);

private:
    unordered_map<std::string, int> variables;
    int evaluate(Expr *expr);
};
