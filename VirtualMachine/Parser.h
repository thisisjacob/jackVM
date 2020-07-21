#pragma once
#include <iostream>
#include <string>

class Parser {
public:
	enum class VMCommandType {
		C_ARITHMETIC, 
		C_PUSH, 
		C_POP, 
		C_LABEL,
		C_GOTO,
		C_IF,
		C_FUNCTION,
		C_RETURN,
		C_CALL
	};
	Parser(std::istream& file);
	bool hasMoreCommands();
	void advance();
	VMCommandType commandType();
	std::string arg1();
	std::string arg2();
};