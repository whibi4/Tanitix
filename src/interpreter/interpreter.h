#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "ast.h"
#include "space.h"

class Interpreter {
public:
    Interpreter() = default;
    void run(const std::vector<std::unique_ptr<Statement>>&, SpaceManger*);
};

#endif //INTERPRETER_H