#include "CodeWriter.h"

CodeWriter::CodeWriter() { outFileStream = std::ofstream(); stackPointer = 256; }

CodeWriter::~CodeWriter() { outFileStream.close(); }

void CodeWriter::setFileName(std::string fileName) { outFileStream.open(fileName); }

void CodeWriter::writeArithmetic(std::string command) {
	if (command.compare("add") == 0) {
		outFileStream << ("@" + std::to_string(stackPointer - 1)) << std::endl;
		outFileStream << ("D=M") << std::endl;
		outFileStream << ("@" + std::to_string(stackPointer - 2)) << std::endl;
		outFileStream << ("M=M+D");
		--stackPointer;
	}
}

void CodeWriter::writePushPop(VMCommandType command, std::string segment, int index) {
	if (command == VMCommandType::C_PUSH) {
		outFileStream << ("@" + std::to_string(stackPointer));
		outFileStream << ("M=" + segment);
		stackPointer++;
	}
}