#ifndef AST_H
#define AST_H
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <variant>
#include <stdexcept>
#include <iostream>
class Context {
    public:
        Context() = default;
        std::variant<double, std::string> get(const std::string& key) const {
            auto it = _variables.find(key);
            if (it == _variables.end()) throw std::out_of_range("Key not found in Context: " + key);
            return it->second;
        }
        void add(const std::string& key, const std::variant<double, std::string>& value) {
            _variables[key] = value;
        }
        void print() const {
            for (const auto& [key, value] : _variables) {
                std::cout << key << ": ";
                std::visit([](auto&& arg) {
                    std::cout << arg;
                }, value);
                std::cout << std::endl;
            }
        }
    private:
        std::unordered_map<std::string, std::variant<double, std::string>> _variables;

};

class Statement {
    public:
        virtual ~Statement() = default;
        virtual void execute(Context&) = 0;
};

class SetVariableStatement : public Statement {
    public:
        enum class VariableType {STRING, NUM};
        explicit SetVariableStatement(std::string variableName, VariableType type, std::string value, bool copyFromAnotherVariable) : 
                        _variableName(std::move(variableName)), 
                        _type(type), 
                        _value(std::move(value)),
                        _copyFromAnotherVariable(copyFromAnotherVariable){};
        void execute(Context &ctx) override;
    private:
        std::string     _variableName;
        VariableType    _type;
        std::string     _value;
        bool            _copyFromAnotherVariable;

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