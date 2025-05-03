#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>
enum class TokenType
{
    number_as_value,
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
    string_as_type,
    number_as_type,
    string_as_value,
    plus,
    minus,
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
    void skipWhitespaceAndBl();
    void skipComments();
    Token treatString();
    Token identifier();
};
/*
        code example:
        #comments
        addField <fieldName: string>; // to be set later
        addObject <objectName: string>;
        setObjectProp <objectName: string> initialPosition (<objectX: double>, <objectY: double>) ;
        setObjectProp <objectName: string> initialVelocity (<objectX: double>, <objectY: double>);
        setVariable <VariableName: string> type <type: string/number> value <value: string/number> ;
        <VariableName: string>+ <value: string/number>;
        <VariableName: string>- <value: number>;
        loop <nmbrOfLoop: number> {

        };
 */
#endif //LEXER_H