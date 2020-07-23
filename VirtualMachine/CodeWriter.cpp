#include "CodeWriter.h"

CodeWriter::CodeWriter() { outFileStream = std::ofstream(); }

CodeWriter::~CodeWriter() { outFileStream.close(); }

void CodeWriter::setFileName(const std::string& fileName) { outFileStream.open(fileName); }

void CodeWriter::writeArithmetic(const std::string& command) {
	if (command.compare("add") == 0) {
		outFileStream << ("M=M+D");
	}
}

void CodeWriter::writePushPop(const VMCommandType command, const std::string& segment, const int index) {
	if (command == VMCommandType::C_PUSH) {
		outFileStream << ("D=M");
		outFileStream << ("@" + std::to_string(index)) << std::endl;
		outFileStream << ("M=" + segment) << std::endl;
	}
}