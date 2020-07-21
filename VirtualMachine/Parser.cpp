#include "Parser.h"

Parser::Parser(std::ifstream&& file) : fileStream{ file }, currentLine{ "" }, currentCommand{ Parser::VMCommandType::NONE } {}

bool Parser::hasMoreCommands() { return fileStream.peek() != EOF; }

// not yet implemented
void Parser::advance() {
	std::getline(fileStream, currentLine);
	currentLine += currentLine.substr(currentLine.find("//"), std::string::npos);
	auto testString = currentLine.substr(0, currentLine.find(" "));
	currentCommand = findCommandType(testString);
	currentLine = currentLine.substr(currentLine.find(" "), std::string::npos);
}

Parser::VMCommandType Parser::commandType() { return currentCommand; }

std::string Parser::arg1() {
	return "";
}

std::string Parser::arg2() {
	return "";
}

Parser::VMCommandType Parser::findCommandType(std::string command) {
	if (command.compare("push") == 0) {
		return VMCommandType::C_PUSH;
	}
	else if (command.compare("pop") == 0) {
		return VMCommandType::C_POP;
	}
	else if (command.compare("add") == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare("sub") == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare("neg") == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare("eq") == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare("gt") == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare("lt") == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare("and") == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare("or") == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare("not") == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else {
		return VMCommandType::NONE;
	}
}
