#include "CodeWriter.h"

CodeWriter::CodeWriter() { outFileStream = std::ofstream(); }

CodeWriter::~CodeWriter() { outFileStream.close(); }

void CodeWriter::setFileName(std::string fileName) {
	outFileStream.open(fileName);
}