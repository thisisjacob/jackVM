#include "CodeWriter.h"

CodeWriter::CodeWriter() { outFileStream = std::ofstream(); }

CodeWriter::~CodeWriter() { if (outFileStream.is_open()) { outFileStream.close(); } }

void CodeWriter::setFileName(const std::string& fileName) { outFileStream.open(fileName); }

void CodeWriter::writeArithmetic(const std::string& command, const int index) {
	if (command.compare("add") == 0) {
		outFileStream << "D=M+D" << std::endl;
		outFileStream << "M=D" << std::endl;
	}
	else if (command.compare("sub")) {
		outFileStream << "D=M-D" << std::endl;
		outFileStream << "M=D" << std::endl;
	}
	else if (command.compare("neg")) {
		//outFileStream << 
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

void CodeWriter::close() { if (outFileStream.is_open()) { outFileStream.close(); } }