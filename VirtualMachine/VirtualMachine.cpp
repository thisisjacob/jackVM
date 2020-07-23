#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"

int main()
{
    Parser par = Parser("SimpleAdd.vm");
    CodeWriter writer;
    writer.setFileName("SimpleAdd.asm");
    while (par.hasMoreCommands()) {
        par.advance();
        par.commandType();
        par.arg1();
        if (par.commandType() == VMCommandType::C_PUSH || par.commandType() == VMCommandType::C_POP
            || par.commandType() == VMCommandType::C_FUNCTION || par.commandType() == VMCommandType::C_CALL) {
            writer.writePushPop(par.commandType(), par.arg1(), 0);
        }
        else {
            writer.writeArithmetic(par.arg1());
        }
    }
}
