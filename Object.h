#ifndef _OBJECT_
#define _OBJECT_

#include "enums.h"
#include <string>

class Object{
public:
	template<typename T>
	Object(const T& type_in, MemoryType mtype, std::string name_in) : type(StandartTokenVariableType::NotStandartType), memoryType(mtype), data(&type_in), name(name_in) {}

	Object(int& val, MemoryType mtype, std::string name_in) : type(StandartTokenVariableType::Int), memoryType(mtype), data(&val), name(name_in) {}
	Object(float& val, MemoryType mtype, std::string name_in) : type(StandartTokenVariableType::Float), memoryType(mtype), data(&val), name(name_in) {}
	Object(double& val, MemoryType mtype, std::string name_in) : type(StandartTokenVariableType::Double), memoryType(mtype), data(&val), name(name_in) {}
	Object(char* val, MemoryType mtype, std::string name_in) : type(StandartTokenVariableType::String), memoryType(mtype), data(val), name(name_in) {}

	StandartTokenVariableType getType() const noexcept {
		return type;
	}

	MemoryType getMemoryType() const noexcept {
		return memoryType;
	}

	std::string getName() const noexcept{
		return name;
	}

private:
	StandartTokenVariableType type;
	MemoryType memoryType;
	void* data;
	std::string name;
	std::function<void()> destroyer;
};

#endif