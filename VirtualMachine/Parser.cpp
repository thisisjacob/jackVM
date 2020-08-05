#include "Parser.h"
#include "Constants.h"

Parser::Parser(const std::string& file) {
	fileStream = std::ifstream(file);
	currentLine = "";
	currentCommand = VMCommandType::NONE;
}

Parser::~Parser() { if (fileStream.is_open()) { fileStream.close(); } }

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

VMCommandType Parser::commandType() { return currentCommand; }

std::string Parser::arg1() {
	if (currentCommand == VMCommandType::C_ARITHMETIC) {
		return currentLine;
	}
	return currentLine.substr(0, currentLine.find(" "));
}

std::string Parser::arg2() {
	return currentLine.substr(currentLine.find(" ") + 1, std::string::npos);
}

VMCommandType Parser::findCommandType(const std::string& command) {
	if (command.compare(Constants::PUSH) == 0) {
		return VMCommandType::C_PUSH;
	}
	else if (command.compare(Constants::POP) == 0) {
		return VMCommandType::C_POP;
	}
	else if (command.compare(Constants::ADD) == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare(Constants::SUBTRACT) == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare(Constants::NEGATE) == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare(Constants::EQUALS) == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare(Constants::GREATER_THAN) == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare(Constants::LESS_THAN) == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare(Constants::AND) == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare(Constants::OR) == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else if (command.compare(Constants::NOT) == 0) {
		return VMCommandType::C_ARITHMETIC;
	}
	else {
		return VMCommandType::NONE;
	}
}
