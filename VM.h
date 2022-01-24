#ifndef _VM_
#define _VM_

#include "Object.h"
#include "Heap.h"
#include "Stack.h"
#include "GC.h"
#include "enums.h"

#include <iostream>

//class Stack;
class GC;

class VM{
public:
	void interpretate(char* filename){
		//interpretate bytecode
			// append variable to stack
			// append variable to heap => give it to GC 
		// check if at this point this object is no need no more and give signal to GC - CallMark(obj)
	}

	void AcceptObject(const Object& obj){
		//std::cout << (obj.getType() == StandartTokenVariableType::Int ? "int" : "not int") << "\n";
		if(obj.getMemoryType() == MemoryType::HeapType)
			heap.PushObject(obj);
		
		if(obj.getMemoryType() == MemoryType::StackType)
			stack.PushObject(obj);

		std::cout << "Virtual Machine Accept Object " << "heap size: " << heap.getHeapSize() << " " << "stack size: " << stack.getStackSize() << "\n";
	}

	//optimise this part. HashTable?
	void DeleteObject(const std::string& name){
		heap.DeleteObject(name);
		stack.DeleteObject(name);
		std::cout << "Virtual Machine Delete Object " << "heap size: " << heap.getHeapSize() << " " << "stack size: " << stack.getStackSize() << "\n";
	}

private:
	Heap heap;
	Stack stack;
	//GC gc;
};

#endif
