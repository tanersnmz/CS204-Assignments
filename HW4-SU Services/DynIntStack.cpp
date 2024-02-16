#include <iostream>
#include "dynintstack.h"
using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynIntStack::DynIntStack()
{
	top = NULL; 
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynIntStack::push(string num)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->value = num;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynIntStack::pop(string &num)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		num = top->value;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynIntStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

void DynIntStack::printStack(void){
	int counter=0;
	StackNode *topCopy = top;
	cout <<"PRINTING THE STACK TRACE:"<<endl;
	if (isEmpty())
	{
		cout << "The stack is empty"<<endl;
	}
	else
	{
		while (topCopy->next!=NULL)
		{
			counter++;
			topCopy=topCopy->next;
		}
		
		while (counter!=0)
		{
			cout << topCopy->value<<endl;
			topCopy=top;
			for (int i = 0; i < counter-1; i++)
			{
				
				topCopy=topCopy->next;
			}
			counter--;
		}
		cout << topCopy->value<<endl;
	}
}

void DynIntStack::clear()
{
	string value;   // Dummy variable for dequeue
	while(!isEmpty())
		pop(value); //delete all elements
	top =NULL;
}