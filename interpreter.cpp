#include "interpreter.h"
#include <iostream>

int Interpreter::evaluate(Expr *expr) {
    if (auto num = dynamic_cast<NumberExpr *>(expr)) {
        return num->value;
    } else if (auto var = dynamic_cast<VarExpr *>(expr)) {
        return variables[var->name];
    } else if (auto bin = dynamic_cast<BinaryExpr *>(expr)) {
        return evaluate(bin->left.get()) + evaluate(bin->right.get());
    }
    return 0;
}

void Interpreter::execute(const std::vector<std::unique_ptr<Stmt>> &program) {
    for (const auto &stmt : program) {
        if (auto letStmt = dynamic_cast<LetStmt *>(stmt.get())) {
            int val = evaluate(letStmt->expr.get());
            variables[letStmt->name] = val;
        } else if (auto printStmt = dynamic_cast<PrintStmt *>(stmt.get())) {
            std::cout << evaluate(printStmt->expr.get()) << "\n";
        }
    }
}
