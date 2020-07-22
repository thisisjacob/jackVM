#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "VMEnums.h"

class CodeWriter {
public:
	CodeWriter();
	~CodeWriter();
	// Opens a new file to start writing to
	void setFileName(std::string fileName);
	// Writes an arithmetic command to file in assembly code
	void writeArithmetic(std::string command);
	// Writes push/pop to file in assembly code
	void writePushPop(VMCommandType command, std::string segment, int index);
	// Closes the file stream
	void close();
private:
	std::ofstream outFileStream;
};
