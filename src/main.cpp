#include "visio.h"
#include "space.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char** argv) {

#if 0
    std::string script = R"(
        setVariable _x number 10;
    )";
    try {
        std::cout<<"DBG1\n";
        Lexer lexer(script);
        std::cout<<"DBG2\n";
        auto tokens = lexer.tokenize();
        std::cout<<"DBG3\n";
        Parser parser(tokens);
        std::cout<<"DBG4\n";
        const auto& program = parser.parse();
        std::cout<<"DBG5\n";
        Interpreter interpreter;
        std::cout<<"DBG6\n";
        interpreter.run(program);
        std::cout<<"DBG7\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
#endif
    SpaceManger spaceManger;
    spaceManger.execute();
    Visio visio(&spaceManger);
    return visio.run(argc, argv);
}