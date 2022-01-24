#ifndef _HEAP_
#define _HEAP_
#include <vector>
#include <iostream>

#include "Object.h"

class Heap{
public:
	void PushObject(const Object& obj){
		heapObjects.push_back(obj);
	}

	void DeleteObject(const std::string& name){
		for(int i = 0; i < heapObjects.size(); ++i){
			if(heapObjects[i].getName() == name)
				heapObjects.erase(heapObjects.begin() + i);
		}
	}

	int getHeapSize() const noexcept {
		return heapObjects.size();
	}
private:
	std::vector<Object> heapObjects;
};

#endif
