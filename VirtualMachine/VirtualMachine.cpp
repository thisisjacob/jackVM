#include <iostream>
#include "Parser.h"

int main()
{
    Parser par = Parser("StackTest.vm");
    while (par.hasMoreCommands()) {
        par.advance();
        par.commandType();
        par.arg1();
        if (par.commandType() == VMCommandType::C_PUSH || par.commandType() == VMCommandType::C_POP
            || par.commandType() == VMCommandType::C_FUNCTION || par.commandType() == VMCommandType::C_CALL) {
            par.arg2();
        }
    }
}
