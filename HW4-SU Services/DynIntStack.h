#pragma once
#include <string>

using namespace std;
struct StackNode
{
	string value;
	StackNode *next;
};

class DynIntStack
{
private:
	

public:
	DynIntStack(void);
	void push(string);
	void pop(string &);
	bool isEmpty(void);
	void printStack(void);
	void clear(void);
	StackNode *top;
	
};
