#pragma once
// The different types of commands for the virtual machine, including NONE for an unrecognized or nonexistent command
enum class VMCommandType {
	C_ARITHMETIC,
	C_PUSH,
	C_POP,
	C_LABEL,
	C_GOTO,
	C_IF,
	C_FUNCTION,
	C_RETURN,
	C_CALL,
	NONE
};
