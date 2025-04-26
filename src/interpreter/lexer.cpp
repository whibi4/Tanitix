#include "lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& src) : _source(src), _pos(0) {}

char Lexer::peek() {
    return _pos < _source.size() ? _source[_pos] : '\0';
}

char Lexer::advance() {
    return _pos < _source.size() ? _source[_pos++] : '\0';
}

void Lexer::skipWhitespace() {
    while (isspace(peek())) advance();
}
void Lexer::skipComments() {
    while (peek()!='\n') advance();
}

Token Lexer::identifier(bool startWithUnderscore) {
    if (startWithUnderscore) advance();
    std::string value;
    while (isalnum(peek())) value += advance();
    if (value.empty())                     return {TokenType::unknown, value};
    if (startWithUnderscore)               return {TokenType::identifier, value};
    if (!value.compare("addField"))        return {TokenType::add_field, value};
    if (!value.compare("addObject"))       return {TokenType::add_object, value};
    if (!value.compare("setObjectProp"))   return {TokenType::set_object_prop, value};
    if (!value.compare("initialPosition")) return {TokenType::initial_position, value};
    if (!value.compare("initialVelocity")) return {TokenType::initial_velocity, value};
    if (!value.compare("setVariable"))     return {TokenType::set_variable, value};
    if (!value.compare("type"))            return {TokenType::type, value};
    if (!value.compare("value"))           return {TokenType::value, value};
    if (!value.compare("string"))          return {TokenType::string_as_type, value};
    if (!value.compare("number"))          return {TokenType::number_as_type, value};
    if (!value.compare("loop"))            return {TokenType::loop, value};
    try {
        size_t pos;
        std::stod(value, &pos);
        if (pos == value.length())     return {TokenType::number_as_value, value};
    } catch(...) {}
    return {TokenType::string_as_value, value};
} 

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (_pos < _source.size()) {
        skipWhitespace();
        char c = peek();
        if (c == '_' || isalpha(c) || isdigit(c)) tokens.push_back(identifier(c == '_'));
        else if (c == '#') { skipComments() ;}
        else if (c == ';') { advance(); tokens.push_back({TokenType::semicolon, ";"}); }
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