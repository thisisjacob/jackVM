#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "VMEnums.h"
#include "Constants.h"

class CodeWriter {
public:
	CodeWriter();
	~CodeWriter();
	// Opens a new file to start writing to
	void setFileName(const std::string& fileName);
	// Writes an arithmetic command to file in assembly code
	// currentAddress should be the next available address
	void writeArithmetic(const std::string& command, const int currentAddress);
	// Writes push/pop to file in assembly code
	void writePushPop(const VMCommandType command, const std::string& segment, const int index);
	// Closes the file stream
	void close();
private:
	std::ofstream outFileStream;
	unsigned int uniqueSymbolCounter = 0;
	// Writes to outFileStream the result of a logical operator
	// commandName should be the name of the command
	// comparisonOperator is the comparisonOperator in Assembly language to use
	// item in firstAddress is compared to item in secondAddress
	// Result is written into the location of secondAddress (-1 for success, 0 for failure)
	void writeLogicCommand(const std::string& commandName, const std::string& comparisonOperator, const int firstAddress, const int secondAddress);
};
