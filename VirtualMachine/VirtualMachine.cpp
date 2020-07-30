#include <iostream>
#include <filesystem>
#include "Parser.h"
#include "CodeWriter.h"
#include "UtilityFunctions.h"
#include "Constants.h"
using namespace std::filesystem;

// This program converts a .vm file to the Hack assembly language specified in The Elements of Computing Systems
// This program should be called from the command line, with one argument for a VM file with the extension .vm
// The assembly version is written to a file having the same name as the given argument, but with a .asm extension
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

    // Prepares to read and write file
    Parser par(file.string());
    CodeWriter writer;
    file.replace_extension(Constants::OUTPUT_EXTENSION);
    writer.setFileName(file.string());
    // start at first value in stack, pointing to the next available empty address
    int address = 256; 
    // Advances through each line and writes the assembly version of each command to file
    while (par.hasMoreCommands()) {
        par.advance();
        if (UtilityFunctions::isMemoryOrProgramCommand(par.commandType())) {
            writer.writePushPop(par.commandType(), par.arg2(), address);
            ++address;
        }
        else if (par.commandType() != VMCommandType::NONE) {
            writer.writeArithmetic(par.arg1(), address);
            if (par.arg1() != "neg" && par.arg1() != "not") { 
                --address;
            }
        }
    }

    return 0;
}
