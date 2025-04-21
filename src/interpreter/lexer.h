#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>

enum class TokenType {
    Add, Loop, InitialX, InitialY, Motion, String, Identifier, Set, Number, Increase, LBrace, RBrace, EndOfFile, Unknown
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
};
/*
    it's dummy for now but i will make it better i promise 
    Example :
        add 50 300 circulare 300 400 0.005
        set x 0
        loop 20 {
            x += 10
            add x x circulare x x 0.005
        }
 */

#endif //LEXER_H