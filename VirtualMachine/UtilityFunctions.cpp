#include "UtilityFunctions.h"

bool UtilityFunctions::isMemoryOrProgramCommand(VMCommandType commandType) {
	return (commandType == VMCommandType::C_PUSH || commandType == VMCommandType::C_POP || commandType == VMCommandType::C_FUNCTION || commandType == VMCommandType::C_CALL);
}