#ifndef AST_H
#define AST_H
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <variant>
class Context {
    public:
        std::unordered_map<std::string, std::variant<double, std::string>> _variables;
};
enum class VariableType {STRING, NUM};
class Statement {
    public:
        virtual ~Statement() = default;
        virtual void execute(Context&) = 0;
};

template <typename T>
class SetVariableStatement : public Statement {
    public:
        explicit SetVariableStatement(std::string variableName, VariableType type, T value) : 
                        _variableName(std::move(variableName)), 
                        _type(type), 
                        _value(value) {};
        void execute(Context &ctx) override;
    private:
        std::string     _variableName;
        VariableType    _type;
        T               _value;

};


class LoopStatement : public Statement {
    public:
        explicit LoopStatement(int count) : _count(count) {}
        void execute(Context &ctx) override;
    private:
        double _count;
        std::vector<std::unique_ptr<Statement>> _body;
};

#endif //AST_H