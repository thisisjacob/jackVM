#include <iostream>
#include <filesystem>
#include "Parser.h"
#include "CodeWriter.h"
#include "UtilityFunctions.h"
#include "Constants.h"
using namespace std::filesystem;

int main(int argc, char* argv[])
{
    // checks validity of argument, creates a path to manage the given file
    if (argc != 2) { 
        std::cerr << "Invalid number of arguments.";
        return 1; 
    }
    path file(argv[1]);
    if (file.extension() != Constants::INPUT_EXTENSION) {
        std::cerr << "Invalid file extension.";
        return 1;
    }

    Parser par(file.string());
    CodeWriter writer;
    file.replace_extension(Constants::OUTPUT_EXTENSION);
    writer.setFileName(file.string());
    // start at first value in stack
    int address = 256; 
    while (par.hasMoreCommands()) {
        par.advance();
        if (UtilityFunctions::isMemoryOrProgramCommand(par.commandType())) {
            writer.writePushPop(par.commandType(), par.arg2(), address);
            ++address;
        }
        else if (par.commandType() != VMCommandType::NONE) {
            writer.writeArithmetic(par.arg1());
            if (par.arg1() != "neg" && par.arg1() != "not") { 
                --address;
            }
        }
    }

    return 0;
}
