#include "CodeWriter.h"

CodeWriter::CodeWriter() { outFileStream = std::ofstream(); }

CodeWriter::~CodeWriter() { outFileStream.close(); }

void CodeWriter::setFileName(const std::string& fileName) { outFileStream.open(fileName); }

void CodeWriter::writeArithmetic(const std::string& command) {
	if (command.compare("add") == 0) {
		outFileStream << "D=D+M" << std::endl;
		outFileStream << "M=D" << std::endl;
	}
}

void CodeWriter::writePushPop(const VMCommandType command, const std::string& segment, const int index) {
	if (command == VMCommandType::C_PUSH) {
		outFileStream << ("@" + segment) << std::endl;
		outFileStream << ("D=A") << std::endl;
		outFileStream << ("@" + std::to_string(index)) << std::endl;
		outFileStream << ("M=D") << std::endl;
		outFileStream << ("@" + std::to_string(index - 1)) << std::endl;
	}
}