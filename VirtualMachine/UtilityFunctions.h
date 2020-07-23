#pragma once
#include "VMEnums.h"

class UtilityFunctions {
public:
	// Returns true if commandType is a C_POP, C_PUSH, C_FUNC or C_CALL, false otherwise
	static bool isMemoryOrProgramCommand(VMCommandType commandType);
};
