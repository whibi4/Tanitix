#include "parser.h"
namespace
{
    std::string tokenTypeToString(TokenType type)
    {
        switch (type)
        {
        case TokenType::number_as_value:
            return "number_as_value";
        case TokenType::add_field:
            return "add_field";
        case TokenType::identifier:
            return "identifier";
        case TokenType::semicolon:
            return "semicolon";
        case TokenType::add_object:
            return "add_object";
        case TokenType::set_object_prop:
            return "set_object_prop";
        case TokenType::initial_position:
            return "initial_position";
        case TokenType::left_parenthesis:
            return "left_parenthesis";
        case TokenType::comma:
            return "comma";
        case TokenType::right_parenthesis:
            return "right_parenthesis";
        case TokenType::initial_velocity:
            return "initial_velocity";
        case TokenType::set_variable:
            return "set_variable";
        case TokenType::string_as_type:
            return "string_as_type";
        case TokenType::number_as_type:
            return "number_as_type";
        case TokenType::string_as_value:
            return "string_as_value";
        case TokenType::plus:
            return "plus";
        case TokenType::minus:
            return "minus";
        case TokenType::loop:
            return "loop";
        case TokenType::left_brace:
            return "left_brace";
        case TokenType::right_brace:
            return "right_brace";
        case TokenType::comment:
            return "comment";
        case TokenType::EndOfFile:
            return "EndOfFile";
        case TokenType::unknown:
            return "unknown";
        default:
            return "invalid_token";
        }
    }
}

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

const Token& Parser::peek() { return tokens[pos]; }
const Token& Parser::advance() { return tokens[pos++]; }
bool Parser::match(TokenType type) {
    if (peek().type == type) { advance(); return true; }
    return false;
}
std::unique_ptr<Statement> Parser::parseStatement(const std::vector<const Token*>& instrection) {
    if (instrection.size() == 0) return nullptr;
    switch (instrection[0]->type)
    {
    case TokenType::set_variable: {
        std::string variableName = instrection[1]->value;
        TokenType variableTypeTkn = instrection[2]->type;
        SetVariableStatement::VariableType variableType;
        if (variableTypeTkn == TokenType::string_as_type) variableType = SetVariableStatement::VariableType::STRING;
        if (variableTypeTkn == TokenType::number_as_type) variableType = SetVariableStatement::VariableType::NUM;
        std::string value = instrection[3]->value;
        double sign = 1;
        if (instrection[3]->type == TokenType::minus || instrection[3]->type == TokenType::plus) {
            sign = (instrection[3]->type == TokenType::minus)?-1:1;
            value= instrection[4]->value;
        }
        return std::make_unique<SetVariableStatement>(variableName, variableType, value, sign);
        break;
    }
    case TokenType::add_object: {
        std::string objectName = instrection[1]->value;
        return std::make_unique<AddObjectStatement>(objectName);
        break;
    }
    case TokenType::set_object_prop: {
        std::string objectName = instrection[1]->value;
        TokenType propTypeTkn = instrection[2]->type;
        SetObjectPropStatement::PropType propType;
        if (propTypeTkn == TokenType::initial_position) propType = SetObjectPropStatement::PropType::POS;
        if (propTypeTkn == TokenType::initial_velocity) propType = SetObjectPropStatement::PropType::VELOC;
        std::vector<std::pair<double, std::string>> props;
        if (propType == SetObjectPropStatement::PropType::POS || propType ==SetObjectPropStatement::PropType::VELOC) {
            size_t index_instruction = 3 + 1; // assuming 3rd index is '('
            std::string value ="";
            double sign = 1;
            while (instrection[index_instruction]->type!=TokenType::right_parenthesis) {
                if(instrection[index_instruction]->type == TokenType::comma) {
                    props.push_back(std::make_pair(sign,value));
                    value = "";
                } else if (instrection[index_instruction]->type == TokenType::minus || instrection[index_instruction]->type == TokenType::plus) {
                    sign = (instrection[index_instruction]->type == TokenType::minus)?-1:1;
                } else {
                    value+=instrection[index_instruction]->value;
                }
                index_instruction++;
            }
            props.push_back(std::make_pair(sign,value));
        }
        return std::make_unique<SetObjectPropStatement>(objectName, props, propType);
        break;
    }
    default:
        break;
    }
    return nullptr;
}
std::vector<std::unique_ptr<Statement>> Parser::parse() {
    std::vector<std::unique_ptr<Statement>> program;
    while (peek().type != TokenType::EndOfFile) {
        if (peek().type == TokenType::unknown) {advance(); continue;}
        std::vector<const Token*> instrection;
        while (peek().type != TokenType::semicolon) {
            instrection.push_back(&advance());
        }
        advance();
        auto stmt = parseStatement(instrection);
        if (stmt) program.push_back(std::move(stmt));
    }
    return program;
}