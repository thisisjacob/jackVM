#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Parser {
public:
	// The different types of commands, including NONE for an unrecognized or nonexistent command
	enum class VMCommandType {
		C_ARITHMETIC, 
		C_PUSH, 
		C_POP, 
		C_LABEL,
		C_GOTO,
		C_IF,
		C_FUNCTION,
		C_RETURN,
		C_CALL,
		NONE
	};
	Parser(std::string file);
	// Returns true if there are more lines in the file
	bool hasMoreCommands();
	// Goes down a command, does any needed filtering, sets currentLine and currentCommand
	void advance();
	// Returns the VMCommandType of the current line
	VMCommandType commandType();
	// Returns the first argument passed to a command, or the command if the type of the command is an arithmetic type
	std::string arg1();
	// Returns the second arugment passed to a command, should only be called of findCommandType is C_PUSH, C_POP, C_FUNCTION or C_CALL
	std::string arg2();
private:
	std::ifstream fileStream;
	std::string currentLine;
	VMCommandType currentCommand;
	VMCommandType findCommandType(std::string command);
};