#ifndef _STACK_
#define _STACK_

#include <vector>
#include <iostream>

#include "Object.h"

class Stack{
public:
	void PushObject(const Object& obj){
		stackObjects.push_back(obj);
	}

	int getStackSize() const noexcept {
		return stackObjects.size();
	}

	void DeleteObject(const std::string& name){
		for(int i = 0; i < stackObjects.size(); ++i){
			if(stackObjects[i].getName() == name)
				stackObjects.erase(stackObjects.begin() + i);
		}
	}

private:
	std::vector<Object> stackObjects;
};

#endif
