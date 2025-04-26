#include "parser.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

const Token& Parser::peek() { return tokens[pos]; }
const Token& Parser::advance() { return tokens[pos++]; }
bool Parser::match(TokenType type) {
    if (peek().type == type) { advance(); return true; }
    return false;
}
std::unique_ptr<Statement> Parser::parseStatement() {
    if (match(TokenType::set_variable)) {
        std::string nameTkn = advance().value;
        std::string typeTkn = advance().value;
        VariableType variableType;
        if (!typeTkn.compare("string")) variableType = VariableType::STRING;
        if (!typeTkn.compare("number")) variableType = VariableType::NUM;
        if (variableType == VariableType::STRING) {
            std::string valueTkn = advance().value;
            return std::make_unique<SetVariableStatement<std::string>>(nameTkn, variableType, valueTkn);
        } else if (variableType == VariableType::NUM) {
            double val = std::stoi(advance().value);
            return std::make_unique<SetVariableStatement<double>>(nameTkn, variableType, val);
        }
    }
    return nullptr;
}