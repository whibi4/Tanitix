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
        TokenType typeTkn = advance().type;
        SetVariableStatement::VariableType variableType;
        if (typeTkn == TokenType::string_as_type) variableType = SetVariableStatement::VariableType::STRING;
        if (typeTkn == TokenType::number_as_type) variableType = SetVariableStatement::VariableType::NUM;
        advance();
        return std::make_unique<SetVariableStatement>(nameTkn, variableType, peek().value, (peek().type == TokenType::identifier));
    }
    advance();
    return nullptr;
}
std::vector<std::unique_ptr<Statement>> Parser::parse() {
    std::vector<std::unique_ptr<Statement>> program;
    while (peek().type != TokenType::EndOfFile) {
        std::cout<<"DBGgg1\n";
        auto stmt = parseStatement();
        if (stmt) program.push_back(std::move(stmt));
    }
    return program;
}