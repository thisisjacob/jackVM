#include "Parser.h"

Parser::Parser(std::ifstream&& file) : fileStream{ file }, currentLine{ "" }, currentCommand{ Parser::VMCommandType::NONE } {}

bool Parser::hasMoreCommands() { return fileStream.peek() != EOF; }

// not yet implemented
void Parser::advance() {

}

Parser::VMCommandType Parser::commandType() { return currentCommand; }

std::string Parser::arg1() {
	return "";
}

std::string Parser::arg2() {
	return "";
}
