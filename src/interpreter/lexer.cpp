#include "lexer.h"
#include <cctype>
#include <iostream>

Lexer::Lexer(const std::string& src) : _source(src), _pos(0) {}

char Lexer::peek() {
    return _pos < _source.size() ? _source[_pos] : '\0';
}

char Lexer::advance() {
    return _pos < _source.size() ? _source[_pos++] : '\0';
}

void Lexer::skipWhitespaceAndBl() {
    while (isspace(peek()) || peek() == '\n') advance();
}
void Lexer::skipComments() {
    while (peek()!='\n') advance();
}
Token Lexer::treatString() {
    std::string value;
    while (peek()!='"') value += advance(); 
    advance();
    return {TokenType::string_as_value, value};
}

Token Lexer::identifier() {
    std::string value;
    while (isalnum(peek())) value += advance();
    if (value.empty())                     return {TokenType::unknown, value};
    if (!value.compare("addField"))        return {TokenType::add_field, value};
    if (!value.compare("addObject"))       return {TokenType::add_object, value};
    if (!value.compare("setObjectProp"))   return {TokenType::set_object_prop, value};
    if (!value.compare("initialPosition")) return {TokenType::initial_position, value};
    if (!value.compare("initialVelocity")) return {TokenType::initial_velocity, value};
    if (!value.compare("setVariable"))     return {TokenType::set_variable, value};
    if (!value.compare("string"))          return {TokenType::string_as_type, value};
    if (!value.compare("number"))          return {TokenType::number_as_type, value};
    if (!value.compare("loop"))            return {TokenType::loop, value};
    try {
        size_t pos;
        std::stod(value, &pos);
        if (pos == value.length())     return {TokenType::number_as_value, value};
    } catch(...) {};
    return {TokenType::identifier, value};
};

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (_pos < _source.size()) {
        skipWhitespaceAndBl();
        char c = peek();
        if (c == '#') { skipComments() ;}
        else if (c == '"') { advance(); tokens.push_back(treatString());}
        else if (isalpha(c) || isdigit(c)) tokens.push_back(identifier());
        else if (c == ';') { advance(); tokens.push_back({TokenType::semicolon, ";"}); }
        else if (c == '+') { advance(); tokens.push_back({TokenType::plus, "+"}); }
        else if (c == '-') { advance(); tokens.push_back({TokenType::minus, "-"}); }
        else if (c == ',') { advance(); tokens.push_back({TokenType::comma, ","}); }
        else if (c == '(') { advance(); tokens.push_back({TokenType::left_parenthesis, "("});}
        else if (c == ')') { advance(); tokens.push_back({TokenType::right_parenthesis, ")"});}
        else if (c == '{') { advance(); tokens.push_back({TokenType::left_brace, "{"}); }
        else if (c == '}') { advance(); tokens.push_back({TokenType::right_brace, "}"}); }
        else { advance(); tokens.push_back({TokenType::unknown, std::string(1, c)}); }
    }
    tokens.push_back({TokenType::EndOfFile, ""});
    return tokens;
}