#include "semantic.h"
#include <iostream>
#include "ast.h"
using namespace std;
int Interpreter::evaluate(Expr *expr) {
    if (auto num = dynamic_cast<NumberExpr *>(expr)) {
        return num->value;
    } else if (auto var = dynamic_cast<VarExpr *>(expr)) {
        return variables[var->name];
    } else if (auto bin = dynamic_cast<BinaryExpr *>(expr)) {
        int l = evaluate(bin->left.get());
        int r = evaluate(bin->right.get());
        switch (bin->op) {
            case TokenType::PLUS: return l + r;
            case TokenType::MINUS: return l - r;
            case TokenType::STAR: return l * r;
            case TokenType::SLASH: return l / r; 
            default: return 0;
        }
    }
    return 0;
}

void Interpreter::execute(const std::vector<std::unique_ptr<Stmt>> &program) {
    for (const auto &stmt : program) {
        if (auto letStmt = dynamic_cast<LetStmt *>(stmt.get())) {
            int val = evaluate(letStmt->expr.get());
            variables[letStmt->name] = val;
        } else if (auto printStmt = dynamic_cast<PrintStmt *>(stmt.get())) {
            cout << evaluate(printStmt->expr.get()) << "\n";
        }
    }
}
