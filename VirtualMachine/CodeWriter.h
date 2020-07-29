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
	void setFileName(const std::string& fileName);
	// Writes an arithmetic command to file in assembly code
	void writeArithmetic(const std::string& command, const int currentAddress);
	// Writes push/pop to file in assembly code
	void writePushPop(const VMCommandType command, const std::string& segment, const int index);
	// Closes the file stream
	void close();
private:
	std::ofstream outFileStream;
};
