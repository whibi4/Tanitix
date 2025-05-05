#include "interpreter.h"
#include <iostream>
void Interpreter::run(const std::vector<std::unique_ptr<Statement>>& program, SpaceManger* spaceManger) {
    Context ctx;
    for (const auto& stmt : program) stmt->execute(ctx);
    for (auto obj : ctx.getAllObjects()) {
        spaceManger->configureObject(obj._initialPositionX,obj._initialPositionY,obj._initialVelocityX,obj._initialVelocityY);
    }
    ctx.print();
}
void SetVariableStatement::execute(Context& ctx) {
    auto it = ctx.get(_value);
    if (it.first) {
        if (_type == VariableType::NUM) {
            double value = std::get<double>(*it.second);
            ctx.add(_variableName, _sign*value);
        } else if (_type == VariableType::STRING) {
            std::string value = std::get<std::string>(*it.second);
            ctx.add(_variableName, value);
        }
    } else {
        if (_type == VariableType::NUM) {
            double value = std::stod(_value);
            ctx.add(_variableName, _sign*value);
        } else if (_type == VariableType::STRING) {
            ctx.add(_variableName, _value);
        }
    }
};
void AddObjectStatement::execute(Context& ctx) {
    Object obj;
    ctx.add(_objectName, obj);
};
void SetObjectPropStatement::execute(Context& ctx) {
    auto it = ctx.get(_objectName);
    if (it.first) {
        double xVal, yVal;
        try {
            size_t pos;
            xVal = std::stod(_values[x_index].second, &pos);
            if (pos != _values[x_index].second.length())
                xVal = std::get<double>(*ctx.get(_values[x_index].second).second);
        } catch (...) {
            xVal = std::get<double>(*ctx.get(_values[x_index].second).second);
        }
        try {
            size_t pos;
            yVal = std::stod(_values[y_index].second, &pos);
            if (pos != _values[y_index].second.length()) 
                yVal = std::get<double>(*ctx.get(_values[y_index].second).second);
        } catch (...) {
            yVal = std::get<double>(*ctx.get(_values[y_index].second).second);
        };
        if (_type == SetObjectPropStatement::PropType::POS) {
            std::get<Object>(*it.second)._initialPositionX = _values[x_index].first*xVal;
            std::get<Object>(*it.second)._initialPositionY = _values[y_index].first*yVal;
        } else if (_type == SetObjectPropStatement::PropType::VELOC) {
            std::get<Object>(*it.second)._initialVelocityX = _values[x_index].first*xVal;
            std::get<Object>(*it.second)._initialVelocityY = _values[y_index].first*yVal;
        }
    }
};