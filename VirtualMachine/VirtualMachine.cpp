#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"
#include "UtilityFunctions.h"

int main()
{
    Parser par = Parser("SimpleAdd.vm");
    CodeWriter writer;
    writer.setFileName("SimpleAdd.asm");
    // start at first value in stack
    int address = 256; 
    while (par.hasMoreCommands()) {
        par.advance();
        par.commandType();
        par.arg1();
        if (UtilityFunctions::isMemoryOrProgramCommand(par.commandType())) {
            writer.writePushPop(par.commandType(), par.arg1(), 256);
            ++address;
        }
        else {
            writer.writeArithmetic(par.arg1());
            --address;
        }
    }
}
