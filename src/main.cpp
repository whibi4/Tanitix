#include "visio.h"
#include "space.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
    const char* file = std::getenv("CODE_PATH");
    std::ifstream inputFile(file);
    if (!inputFile) {
        std::cerr << "Error: Cannot open file " << argv[1] << "\n";
        return 1;
    }
    std::ostringstream buffer;
    buffer << inputFile.rdbuf(); 
    std::string content = buffer.str();

    SpaceManger spaceManger;
    try {
        Lexer lexer(content);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        const auto& program = parser.parse();
        Interpreter interpreter;
        interpreter.run(program, &spaceManger);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    //uncomment this line to get back to ol behivour
    //spaceManger.execute();
    Visio visio(&spaceManger);
    return visio.run(argc, argv);
}