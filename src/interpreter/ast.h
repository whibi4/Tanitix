#ifndef AST_H
#define AST_H
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <variant>
#include <stdexcept>
#include <iostream>
#include <limits>
const double MAX_DOUBLE = std::numeric_limits<double>::max();
struct Object
{
    double _initialPositionX= MAX_DOUBLE;
    double _initialPositionY= MAX_DOUBLE;
    double _initialVelocityX= MAX_DOUBLE;
    double _initialVelocityY= MAX_DOUBLE;
    friend std::ostream& operator<<(std::ostream& os, const Object& obj) {
        os <<"OBJ- initPos("<<obj._initialPositionX<<","<<obj._initialPositionY<<") "
        <<"initVeloc("<<obj._initialVelocityX<<","<<obj._initialVelocityY<<")";
        return os;
    }
};
class Context {
    public:
        Context() = default;
        std::pair<bool, std::variant<double, std::string, Object>*> get(const std::string& key) {
            auto it = _variables.find(key);
            if (it == _variables.end())  {
                return std::make_pair(false,nullptr);
            }
            return std::make_pair(true,&it->second);
        }
        void add(const std::string& key, const std::variant<double, std::string, Object>& value) {
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
        std::vector<Object> getAllObjects(){
            std::vector<Object> objects;
            for (auto &[key, value] : _variables) {
                if (std::holds_alternative<Object>(value)) {
                    objects.push_back(std::get<Object>(value));
                }
            }
            return objects;
        }

    private:
        std::unordered_map<std::string, std::variant<double, std::string, Object>> _variables;
};

class Statement {
    public:
        virtual ~Statement() = default;
        virtual void execute(Context&) = 0;
};

class SetVariableStatement : public Statement {
    public:
        enum class VariableType {STRING, NUM};
        explicit SetVariableStatement(std::string variableName, VariableType type, std::string value) : 
                        _variableName(std::move(variableName)), 
                        _type(type), 
                        _value(std::move(value)){};
        void execute(Context &ctx) override;
    private:
        std::string     _variableName;
        VariableType    _type;
        std::string     _value;

};
class AddObjectStatement : public Statement {
    public:
        explicit AddObjectStatement(std::string objectName) : 
                        _objectName(std::move(objectName)){};
        void execute(Context &ctx) override;
    private:
        std::string     _objectName;

};
class SetObjectPropStatement : public Statement {
    private:
        const size_t x_index = 0;
        const size_t y_index = 1;
        const size_t single_value = 0;
    public:
        enum class PropType {POS, VELOC};

        explicit SetObjectPropStatement(std::string objectName, const std::vector<std::string>& values, PropType propType) : 
                                    _objectName(std::move(objectName)),
                                    _values(std::move(values)),
                                    _type(propType){
                                        std::cout<<"SET_PROP"<<_objectName<<" : [";
                                        for (auto v : _values) {
                                            std::cout<<v<<" - ";
                                        }
                                        std::cout<<"]\n";
                                    };
        void execute(Context &ctx) override;
    private:
        std::string               _objectName;
        std::vector<std::string>  _values;
        PropType                  _type;
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