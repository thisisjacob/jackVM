#include "CodeWriter.h"

CodeWriter::CodeWriter() { outFileStream = std::ofstream(); }

CodeWriter::~CodeWriter() { 
	if (outFileStream.is_open()) {
		outFileStream.close(); }
}

void CodeWriter::setFileName(const std::string& fileName) { outFileStream.open(fileName); }

void CodeWriter::writeArithmetic(const std::string& command, const int currentAddress) {
	// currentAddress is the next available empty address - use these to point to items
	int firstAddress = currentAddress - 2;
	int secondAddress = currentAddress - 1;
	if (command == "add") {
		outFileStream << "A=A-1" << "\n";
		outFileStream << "D=M+D" << "\n";
		outFileStream << "M=D" << "\n";
	}
	else if (command == "sub") {
		outFileStream << "A=A-1" << "\n";
		outFileStream << "D=M-D" << "\n";
		outFileStream << "M=D" << "\n";
	}
	else if (command == "neg") {
		outFileStream << "D=-M" << "\n";
		outFileStream << "M=D" << "\n";
	}
	else if (command == "eq") {
		writeLogicCommand("eq", "JEQ", firstAddress, secondAddress);
	}
	else if (command == "gt") {
		// checking if firstAddress is greater than secondAddress
		// TODO: these first for lines for logical operators could be moved into a separate function for code reuse
		// TODO: return values of comparisons could also be moved into a function for code reuse
		outFileStream << "@" << firstAddress << "\n";
		outFileStream << "D=M\n";
		outFileStream << "@" << secondAddress << "\n";
		outFileStream << "D=D-M\n";
		outFileStream << "@ISGREATER" << std::to_string(uniqueSymbolCounter) << "\n";
		outFileStream << "D;JGT\n";
		outFileStream << "@NOTGREATER" << std::to_string(uniqueSymbolCounter) << "\n";
		outFileStream << "0;JMP\n";
		// greater than return value
		outFileStream << "\t(ISGREATER" << std::to_string(uniqueSymbolCounter) << ")\n";
		outFileStream << "@" << firstAddress << "\n";
		outFileStream << "M=-1\n";
		outFileStream << "@END" << std::to_string(uniqueSymbolCounter) << "\n";
		outFileStream << "0;JMP\n";
		// not greater than return value
		outFileStream << "\t(NOTGREATER" << std::to_string(uniqueSymbolCounter) << ")\n";
		outFileStream << "@" << firstAddress << "\n";
		outFileStream << "M=0\n";
		outFileStream << "@END" << std::to_string(uniqueSymbolCounter) << "\n";
		outFileStream << "0;JMP\n";
		// end of equality block
		outFileStream << "\t(END" << std::to_string(uniqueSymbolCounter) << ")\n";
	}
	uniqueSymbolCounter++;
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

void CodeWriter::writeLogicCommand(const std::string& commandName, const std::string& comparisonOperator, const int firstAddress, const int secondAddress) {
	// checking for equality
	outFileStream << "@" << firstAddress << "\n";
	outFileStream << "D=M\n";
	outFileStream << "@" << secondAddress << "\n";
	outFileStream << "D=D-M\n";
	outFileStream << "@IS" << commandName << std::to_string(uniqueSymbolCounter) << "\n";
	outFileStream << "D;" << comparisonOperator << "\n";
	outFileStream << "@NOT" << commandName << std::to_string(uniqueSymbolCounter) << "\n";
	outFileStream << "0;JMP\n";
	// comparison true return value (-1)
	outFileStream << "\t(IS" << commandName << std::to_string(uniqueSymbolCounter) << ")\n";
	outFileStream << "@" << secondAddress << "\n";
	outFileStream << "M=-1\n";
	outFileStream << "@END" << std::to_string(uniqueSymbolCounter) << "\n";
	outFileStream << "0;JMP\n";
	// comparison false return value (0)
	outFileStream << "\t(NOT" << commandName << std::to_string(uniqueSymbolCounter) << ")\n";
	outFileStream << "@" << secondAddress << "\n";
	outFileStream << "M=0\n";
	outFileStream << "@END" << std::to_string(uniqueSymbolCounter) << "\n";
	outFileStream << "0;JMP\n";
	// end of equality block
	outFileStream << "\t(END" << std::to_string(uniqueSymbolCounter) << ")\n";
}