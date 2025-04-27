#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "ast.h"

class Interpreter {
public:
    Interpreter() = default;
    void run(const std::vector<std::unique_ptr<Statement>>&);
};

#endif //INTERPRETER_H