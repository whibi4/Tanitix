#include "interpreter.h"
#include <iostream>
void Interpreter::run(const std::vector<std::unique_ptr<Statement>>& program) {
    Context ctx;
    for (const auto& stmt : program) stmt->execute(ctx);
    ctx.print();
}
void SetVariableStatement::execute(Context& ctx) {
    if (_type == VariableType::NUM) {
        double value;
        if (_copyFromAnotherVariable) {
            value = std::get<double>(ctx.get(_value));
        } else {
            std::cout<<"\nreached this ponit "<<_value<<"\n";
            value = std::stod(_value);
        }
        ctx.add(_variableName, value);
    } else if (_type == VariableType::STRING) {
        std::string value;
        if (_copyFromAnotherVariable) {
            value = std::get<std::string>(ctx.get(_value));
        } else {
            value = std::string(_value);
        }
        ctx.add(_variableName, value);
    }
};