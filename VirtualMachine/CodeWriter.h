#pragma once
#include <iostream>
#include <string>
#include "Parser.h"

class CodeWriter {
public:
	CodeWriter(std::ofstream& outFile);
	void setFileName(std::string fileName);
	void writeArithmetic(std::string command);
	void writePushPop(Parser::VMCommandType command, std::string segment, int index);
	void close();
private:
	std::ostream& outFileStream;
};
