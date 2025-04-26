#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>

enum class TokenType
{
    add_field,
    identifier,
    semicolon,
    add_object,
    set_object_prop,
    initial_position,
    left_parenthesis,
    comma,
    right_parenthesis,
    initial_velocity,
    set_variable,
    type,
    string_as_type,
    number_as_type,
    value,
    string_as_value,
    number_as_value,
    double_plus,
    double_minus,
    loop,
    left_brace,
    right_brace,
    comment,
    EndOfFile,
    unknown
};
struct Token {
    TokenType type;
    std::string value;
};

class Lexer
{
public:
    explicit Lexer(const std::string &source);
    std::vector<Token> tokenize();

private:
    std::string _source;
    size_t _pos;
    char peek();
    char advance();
    void skipWhitespace();
    void skipComments();
    Token identifier(bool startWithUnderscore = false);
};
/*
        code example:
        #comments
        add_field _<fieldName: string>; // to be set later
        add_object _<objectName: string>;
        set_object_prop <objectName: string> initial_position (<objectX: double>, <objectY: double>) ;
        set_object_prop <objectName: string> initial_velocity (<objectX: double>, <objectY: double>);
        set_variable <VariableName: string> type <type: string/number> value <value: string/number> ;
        <VariableName: string>++ <value: string/number>;
        <VariableName: string>-- <value: number>;
        loop <nmbrOfLoop: number> {

        };
 */
#endif //LEXER_H