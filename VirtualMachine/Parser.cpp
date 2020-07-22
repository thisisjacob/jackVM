#include "Parser.h"

Parser::Parser(std::string file) {
	fileStream = std::ifstream(file);
	currentLine = "";
	currentCommand = VMCommandType::NONE;
}

bool Parser::hasMoreCommands() { return fileStream.peek() != EOF; }

void Parser::advance() {
	std::getline(fileStream, currentLine);
	currentLine = currentLine.substr(0, currentLine.find("//"));
	auto testString = currentLine.substr(0, currentLine.find(" "));
	currentCommand = findCommandType(testString);
	if (currentLine.find(" ") != std::string::npos) {
		currentLine = currentLine.substr(currentLine.find(" ") + 1, std::string::npos);
	}
}

Parser::VMCommandType Parser::commandType() { return currentCommand; }

std::string Parser::arg1() {
	if (currentCommand == VMCommandType::C_ARITHMETIC) {
		return currentLine;
	}
	return currentLine.substr(0, currentLine.find(" "));
}

std::string Parser::arg2() {
	return currentLine.substr(currentLine.find(" ") + 1, std::string::npos);
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
