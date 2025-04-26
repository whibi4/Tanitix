#ifndef AST_H
#define AST_H
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Context {
    public:
        std::unordered_map<std::string, std::string> _stringVariables;
        std::unordered_map<std::string, double>      _numericVariables;
};

class Statement {
    public:
        virtual ~Statement() = default;
        virtual void execute(Context&) = 0;
};

class AddObjectStatement : public Statement {
    
};


class LoopStatement : public Statement {
    public:
        explicit LoopStatement(std::string countStr) : _countStr(std::move(countStr)) {}
        void execute(Context &ctx) override;

    private:
        std::string _countStr;
        std::vector<std::unique_ptr<Statement>> _body;
};

#endif //AST_H