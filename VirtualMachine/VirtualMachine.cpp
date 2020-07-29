#include <iostream>
#include <filesystem>
#include "Parser.h"
#include "CodeWriter.h"
#include "UtilityFunctions.h"

using namespace std::filesystem;

int main(int argc, char* argv[])
{
    if (argc != 2) { return 1; }
    path file(argv[1]);

    Parser par(file.string());
    CodeWriter writer;
    file.replace_extension(".asm");
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
