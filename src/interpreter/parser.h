#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "ast.h"

class Parser {
    public:
        explicit Parser(const std::vector<Token>& tokens);
        std::vector<std::unique_ptr<Statement>> parse();
    private:
        const std::vector<Token>& tokens;
        size_t pos;
    
        const Token& peek();
        const Token& advance();
        bool match(TokenType);
        std::unique_ptr<Statement> parseStatement(const std::vector<const Token*>&);
    };

#endif //PARSER_H