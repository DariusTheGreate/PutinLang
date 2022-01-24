## Some simple cringe compiler with garbage collection and multithreading 

Planned to initialize fixed amount of system threads and switch execution contexts inside Virtual Machine
Virtual Machine is also responsible for collecting memory using Mark And Swap Garbage collection algorithm

The main invariant of this language for now is ";" symbol. This is used for defining a logical block of code.
For example:

```sh
int aboba;
```

will create int on a stack of virtual machine
When

```sh
int abobus = malloc(1000);
```

will allocate 1000 byte on heap of VM

Comment section of this language is implemented using "|" symbol, like this:

```
| THIS IS COMMENT |
```

Like this, for now, for input similar to this:
```
  int   mister_putin    = 10;
 
   int    russian   = malloc(1000);
  int   best    = 10;
 
   int    president   = malloc(1000);
  int   of    = 10;
 
   int    the   = malloc(1000);
  int   world    = 10;
 
   int    u_kno   = malloc(1000);

| clear heap |

free(president);

```
u will get output like this:

![output example](/assets/output1.png "output example")

### What needs to be done:
- Compiler parser needs to be optimised and tested. For now this is really bad
- Using vectors for storing stack and heap vaues is kinda stupid way to act
- Create own string class
- structs defenition. Storing types table inside VM? 
- Write bytecode, like in Java?
- Threading and thread contexts switching, simmilar to my coroutines project.
- Scheduling?
