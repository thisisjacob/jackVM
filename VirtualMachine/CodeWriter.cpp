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
	if (command == Constants::ADD) {
		outFileStream << "A=A-1" << "\n";
		outFileStream << "D=M+D" << "\n";
		outFileStream << "M=D" << "\n";
	}
	else if (command == Constants::SUBTRACT) {
		outFileStream << "A=A-1" << "\n";
		outFileStream << "D=M-D" << "\n";
		outFileStream << "M=D" << "\n";
	}
	else if (command == Constants::NEGATE) {
		outFileStream << "D=-M" << "\n";
		outFileStream << "M=D" << "\n";
	}
	else if (command == Constants::EQUALS) {
		writeComparisonLogicCommand("EQUALS", "JEQ", firstAddress, secondAddress);
	}
	else if (command == Constants::GREATER_THAN) {
		// checking if firstAddress is greater than secondAddress
		writeComparisonLogicCommand("GREATERTHAN", "JGT", firstAddress, secondAddress);
	}
	else if (command == Constants::LESS_THAN) {
		writeComparisonLogicCommand("LESSTHAN", "JLT", firstAddress, secondAddress);
	}
	else if (command == Constants::AND) {
		// comparisons
		outFileStream << "@" << firstAddress << "\n";
		outFileStream << "D=M\n";
		outFileStream << "@" << secondAddress << "\n";
		outFileStream << "D=D&M\n";
		outFileStream << "@" << std::to_string(firstAddress) << "\n";
		outFileStream << "M=D\n";
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

void CodeWriter::writeComparisonLogicCommand(const std::string& commandName, const std::string& comparisonOperator, const int firstAddress, const int secondAddress) {
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
	outFileStream << "@" << firstAddress << "\n";
	outFileStream << "M=-1\n";
	outFileStream << "@END" << std::to_string(uniqueSymbolCounter) << "\n";
	outFileStream << "0;JMP\n";
	// comparison false return value (0)
	outFileStream << "\t(NOT" << commandName << std::to_string(uniqueSymbolCounter) << ")\n";
	outFileStream << "@" << firstAddress << "\n";
	outFileStream << "M=0\n";
	// end of equality block
	outFileStream << "\t(END" << std::to_string(uniqueSymbolCounter) << ")\n";
}