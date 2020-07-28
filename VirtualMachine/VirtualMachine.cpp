#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"
#include "UtilityFunctions.h"

int main()
{
    Parser par("SimpleAdd.vm");
    CodeWriter writer;
    writer.setFileName("SimpleAdd.asm");
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
