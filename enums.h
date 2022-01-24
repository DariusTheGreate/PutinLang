#ifndef _ENUMS_
#define _ENUMS_

enum class StandartTokenVariableType {
	Int,
	String,
	Double,
	Float,
	NotStandartType
};

enum class MemoryType{
	StackType,
	HeapType
};

enum class TokenType{
	VariableDeclaration,
	VariableDeletion,
	StructDeclaration,
	FunctionDeclaration,
	ForLoop,
	Undefined
};

#endif
