#include "CodeWriter.h"

CodeWriter::CodeWriter() { outFileStream = std::ofstream(); }

CodeWriter::~CodeWriter() { 
	if (outFileStream.is_open()) {
		outFileStream.close(); }
}

void CodeWriter::setFileName(const std::string& fileName) { outFileStream.open(fileName); }

void CodeWriter::writeArithmetic(const std::string& command, const int currentAddress) {
	int address = currentAddress - 1;
	if (command.compare("add") == 0) {
		outFileStream << "A=A-1" << "\n";
		outFileStream << "D=M+D" << "\n";
		outFileStream << "M=D" << "\n";
	}
	else if (command.compare("sub") == 0) {
		outFileStream << "A=A-1" << "\n";
		outFileStream << "D=M-D" << "\n";
		outFileStream << "M=D" << "\n";
	}
	else if (command.compare("neg") == 0) {
		outFileStream << "D=-M" << "\n";
		outFileStream << "M=D" << "\n";
	}
	else if (command.compare("eq") == 0) {
		outFileStream << "D=D-M" << "\n";
		outFileStream << "M=D" << "\n";
	}
}

void CodeWriter::writePushPop(const VMCommandType command, const std::string& segment, const int index) {
	if (command == VMCommandType::C_PUSH) {
		outFileStream << ("@" + segment) << "\n";
		outFileStream << ("D=A") << "\n";
		outFileStream << ("@" + std::to_string(index)) << "\n";
		outFileStream << ("M=D") << "\n";
		// segment put into m
		outFileStream << "D=M" << "\n";
		// ends with D pointing at item in index, A pointing at index, M pointing at item in index
	}
}

void CodeWriter::close() { if (outFileStream.is_open()) { outFileStream.close(); } }