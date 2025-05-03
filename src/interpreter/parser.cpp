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
std::unique_ptr<Statement> Parser::parseStatement() {
    if (match(TokenType::set_variable)) {
        std::string nameTkn = advance().value;
        TokenType typeTkn = advance().type;
        SetVariableStatement::VariableType variableType;
        if (typeTkn == TokenType::string_as_type) variableType = SetVariableStatement::VariableType::STRING;
        if (typeTkn == TokenType::number_as_type) variableType = SetVariableStatement::VariableType::NUM;
        return std::make_unique<SetVariableStatement>(nameTkn, variableType, advance().value);
    } else if (match(TokenType::add_object)) {
        std::string objectName = advance().value;
        return std::make_unique<AddObjectStatement>(objectName);
    } else if (match(TokenType::set_object_prop)) {
        std::string objectName = advance().value;
        TokenType typeTkn = advance().type;
        SetObjectPropStatement::PropType propType;
        if (typeTkn == TokenType::initial_position) propType = SetObjectPropStatement::PropType::POS;
        if (typeTkn == TokenType::initial_velocity) propType = SetObjectPropStatement::PropType::VELOC;
        std::vector<std::string> props;
        if (propType == SetObjectPropStatement::PropType::POS || propType ==SetObjectPropStatement::PropType::VELOC) {
            while (advance().type!=TokenType::right_parenthesis) {
                if(peek().type == TokenType::comma) advance();
                props.push_back(peek().value);
            }
        }
        return std::make_unique<SetObjectPropStatement>(objectName, props, propType);

    }
    return nullptr;
}
std::vector<std::unique_ptr<Statement>> Parser::parse() {
    std::vector<std::unique_ptr<Statement>> program;
    while (peek().type != TokenType::EndOfFile) {
        match(TokenType::semicolon);
        if(peek().type == TokenType::unknown) {
            std::cout<<"DBG_crtcl : "<<peek().value<<" : "<<tokenTypeToString(peek().type)<<std::endl;
            advance();
        }
        auto stmt = parseStatement();
        if (stmt) program.push_back(std::move(stmt));
    }
    return program;
}