#include <iostream>
#include "Parser.h"

int main()
{
    Parser par = Parser("StackTest.vm");
    while (par.hasMoreCommands()) {
        par.advance();
        par.commandType();
    }
}
