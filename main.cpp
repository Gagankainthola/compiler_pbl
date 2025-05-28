#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream file("program.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();

    Lexer lexer(buffer.str());
    auto tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        std::cout << "Token: " << static_cast<int>(token.type) << ", value: " << token.value << "\n";
    }

    Parser parser(tokens);
    auto program = parser.parse();

    Interpreter interpreter;
    interpreter.execute(program);

    return 0;
}
