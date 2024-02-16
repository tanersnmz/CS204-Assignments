/*******************************************************************************************************************
Purpose: 
This program places students and academic staff who want to use Sabanci university services into two separate "Queue" data structures
(in a First In First Out (FIFO) manner), after that it performs the requested services in the correct order
by keeping them in the "Stack" data structure(in First In Last Out (FILO) manner).

Author: Taner Giray Sonmez

Date: 24/11/2021

Any known bugs: No known bugs
******************************************************************************************************************/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "DynIntQueue.h" // This is implemented for the student's queue.
#include "DynIntStack.h" // This is implemented for the shared stack.
#include "IntQueue.h" // This is implemented for the instructor's queue.



using namespace std;

/*************************************************************************************************
This struct coded for linked list structure that holds commands (instructions) in the input files.
**************************************************************************************************/
struct commands
{
	string commandName;
	commands *down;

	commands::commands(const string & command="", commands *d=NULL){
		commandName=command;
		down =d;
	}

};

/**********************************************************************************************
This struct coded for linked list structure that holds functions (services) in the input files.
************************************************************************************************/
struct functions
{
	string functionName;
	functions *next;
	commands *firstCommand;

	functions::functions(const string & service="", functions *n=NULL,commands * fc=NULL){
		functionName=service;
		next =n;
		firstCommand=fc;
	}
};

/************************************************************************************************************************************
This struct coded for keeping a person's information(student or academic staff) such as name, id and corresponding function(service). 
*************************************************************************************************************************************/
struct PersonInfo
{
	int id;
	string function;
	string name;

	PersonInfo::PersonInfo(const int &i,const string &f,const string &n ){
		id=i;
		function=f;
		name=n;
	}
};

/********************
GLOBAL VARIABLES
*********************/
functions *head=NULL; // Services head of my linked list.
IntQueue InstructorQueue(5); // Static Instructor Queue.
DynIntQueue	StudentQueue; // Dynamic Student Queue.
DynIntStack sharedStack; // Dynamic shared Stack.
vector<PersonInfo> students; // Vector of PersonInfo that holds students informations.
vector<PersonInfo> instructors;// Vector of PersonInfo that holds instructors informations.

/******************************************************
This variable is counting the times of dequeuing,
by doing this it prevents unnecessary dequeuing
operations (This is kind of coded for safety purposes).
*******************************************************/
int globalDequeueTimes=0; 


/************************************************************************************************************
This function takes name of the input file and while reading input file it creates linked list structure that 
was said in homework. Moreover, if input files opened correctly, it returns true. Otherwise, it returns false.
************************************************************************************************************/
bool LinkedListCreator(const string & inputFileName){
	static functions *headIterator;

	/*****************************************************************************************
	It counts the times for creating linked list properly(For example, if times is 1 it says
	that we are in the first input file, if it is 2 we are in the second input file and so on)
	(I.e it is for adding new function to the linked list)
	*******************************************************************************************/
	int static times=0;

	times++;
	bool status=true;
	ifstream input;
	input.open(inputFileName.c_str());
	if (input.fail())
	{
		cout << "Wrong file name!"<<endl;
		status=false;
	}
	else
	{
		commands *commandIterator;
		string line;

		/*****************************************************************************************
		It counts the times for creating linked list properly(For example, if counter is 1 it says
		that we are in the first command in the input file, if it is 2 we are in the second 
		command in the input file and so on)
		(I.e it is for adding new command to the linked list)
		********************************************************************************************/
		int counter=0;

		if (times==1)
		{
			while (getline(input,line))
			{
				counter++;
				if (counter==1 && head==NULL)
				{
					head = new functions(line.substr(0,line.length()-1));
					headIterator=head;
				}
				else if (counter>2 && head!=NULL)
				{
					commandIterator->down = new commands(line.substr(0,line.length()-1));
					commandIterator= commandIterator->down;
				}
				else if (counter==2 && head!=NULL)
				{
					head->firstCommand = new commands(line.substr(0,line.length()-1));
					commandIterator=head->firstCommand;
				}
			}
		}
		else if (times>1)
		{
			while (getline(input,line))
			{
				counter++;
				if (counter==1)
				{
					headIterator->next =new functions(line.substr(0,line.length()-1));
					headIterator=headIterator->next;
				}
				else if (counter>2)
				{
					commandIterator->down = new commands(line.substr(0,line.length()-1));
					commandIterator= commandIterator->down;
				}
				else if (counter==2)
				{
					headIterator->firstCommand= new commands(line.substr(0,line.length()-1));
					commandIterator=headIterator->firstCommand;
				}
			}
		}
		input.close();
	}
	return status;
}

/*****************************************************
This function prints the linked list as desired format.
******************************************************/
void LinkedListPrinter(){
	cout << "--------------------------------------------------------------------"<<endl;
	cout << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS"<<endl;
	cout << "--------------------------------------------------------------------"<<endl;
	functions *headTemp =head;
	while (headTemp)
	{
		commands *commandTemp = headTemp->firstCommand;
		cout<<headTemp->functionName << ":"<<endl;
		while (commandTemp->down !=NULL)
		{
			cout << commandTemp->commandName<<", ";
			commandTemp=commandTemp->down;
		}
		cout << commandTemp->commandName<<"."<<endl;
		cout<<endl<<endl;
		headTemp=headTemp->next;
	}
}

/***************************************************************************************
This function takes service name(function name) as an input. If given service exist in 
the linked list, it returns true. Otherwise, it returns false.
***************************************************************************************/
bool FunctionExistenceChecker(const string & functionName){
	functions *headTemp = head;
	while (headTemp)
	{
		if (headTemp->functionName == functionName)
		{
			return true;
		}
		headTemp=headTemp->next;
	}
	return false;
}

/****************************************************************************************************************************
This function adds instructor to the instructor queue and instructor vector(keeping person's information such as name and id).
******************************************************************************************************************************/
void addInstructorRequest(){
	cout << "Add a service (function) that the instructor wants to use: "<<endl;
	string functionName;
	cin >> functionName;
	if (FunctionExistenceChecker(functionName))
	{
		cout << "Give instructor's name: ";
		string instructorName;
		cin>> instructorName;
		cout << "Give instructor's ID (an int): ";
		int instructorId;
		cin>>instructorId;
		InstructorQueue.enqueue(instructorId);
		PersonInfo teacher(instructorId,functionName,instructorName);
		instructors.push_back(teacher);
		cout << "Prof. " << instructorName<<"'s service request of " << functionName<< " has been put in the instructor's queue."<<endl;
		cout << "Waiting to be served..." << endl;
	}
	else
	{
		cout << "The requested service (function) does not exist."<<endl;
		cout << "GOING BACK TO MAIN MENU"<<endl;
	}

}

/*********************************************************************************************************************
This function adds student to the student queue and student vector(keeping person's information such as name and id).
**********************************************************************************************************************/
void addStudentRequest(){
	cout << "Ad a service (function) that the student wants to use: "<<endl;
	string functionName;
	cin >> functionName;
	if (FunctionExistenceChecker(functionName))
	{
		cout << "Give student's name: ";
		string studentName;
		cin>> studentName;
		cout << "Give student's ID (an int): ";
		int studentId;
		cin>>studentId;
		StudentQueue.enqueue(studentId);
		PersonInfo student(studentId,functionName,studentName);
		students.push_back(student);
		cout <<  studentName<<"'s service request of " << functionName<< " has been put in the student's queue."<<endl;
		cout << "Waiting to be served..." << endl;
	}
	else
	{
		cout << "The requested service (function) does not exist."<<endl;
		cout << "GOING BACK TO MAIN MENU"<<endl;
	}
}


/*************************************************************************************
This function implies necessary types of commands such as define, print stack and call.
By doing this, it uses shared stacks, instructor queue,vector and student queue,vector.
Furthermore, it takes int studentOrInstructor(i.e students or instructors) as a parameter
which is helping to decide whether function should use students queue or instructor queue.
If studentOrInstructor is 1, function uses student queue. If it is 0, function uses
instructor queue.
**************************************************************************************/
void processARequest(string functionName,const int studentOrInstructor)
{
	functions *headTemp=head;
	while (headTemp->functionName!=functionName)
	{
		headTemp=headTemp->next;
	}
	commands *commandTemp=headTemp->firstCommand;
	while (commandTemp)
	{
		string result="";
		if(commandTemp->commandName.find("define")!=string::npos)
		{
			result+= functionName+": "+commandTemp->commandName;
			sharedStack.push(result);
		}
		else if (commandTemp->commandName.find("call")!=string::npos)
		{
			int idx = commandTemp->commandName.find(" ");
			result = commandTemp->commandName.substr(5);
			cout << "Calling " << result << " from " << functionName<<endl;
			processARequest(result,studentOrInstructor);
		}
		else
		{
			sharedStack.printStack();
		}
		commandTemp=commandTemp->down;
	}	
	cout<<functionName<<" is finished. Clearing the stack from it's data... "<<endl;
	system("pause");
	string temp;// for pop().
	while (!sharedStack.isEmpty() && sharedStack.top->value.find(functionName)!=string::npos)
	{
		sharedStack.pop(temp);
	}	
	int dummy;// for dequeue().
	if(!StudentQueue.isEmpty() && studentOrInstructor==1 && globalDequeueTimes==0)
	{ 
		StudentQueue.dequeue(dummy);
		students.erase(students.begin());
	}
	else if(!InstructorQueue.isEmpty()&& studentOrInstructor==0 && globalDequeueTimes==0)
	{ 
		InstructorQueue.dequeue(dummy);
		instructors.erase(instructors.begin());
	}
	if (sharedStack.isEmpty())
	{
		cout << "The stack is empty"<<endl;
	}
	globalDequeueTimes++;
	
}

/***************************************************************************************************
This function decides whether to continue the program with the student queue or academic staff queue
and sends the necessary arguments to itself by using recursion.
****************************************************************************************************/
void processARequest()
{
	if (!InstructorQueue.isEmpty())
	{
		cout << "Processing instructors queue..."<<endl;
		cout <<"Processing prof." << instructors[0].name<<"'s request (with ID "<<  instructors[0].id<<") of service (function):"<<endl;
		cout <<instructors[0].function<<endl;
		globalDequeueTimes=0;
		processARequest(instructors[0].function,0);
		cout<<"GOING BACK TO MAIN MENU"<<endl;
		
	}
	else if (!StudentQueue.isEmpty())
	{
		cout << "Instructors queue is empty. Proceeding with students queue..."<<endl;
		cout <<"Processing " <<students[0].name<<"'s request (with ID "<<  students[0].id<<") of service (function):"<<endl;
		cout <<students[0].function<<endl;
		globalDequeueTimes	=0;
		processARequest(students[0].function,1);
		cout<<"GOING BACK TO MAIN MENU"<<endl;
		
	}
	else
	{
		cout<<"Both instructor's and student's queue is empty.\nNo request is processed."<<endl<<"GOING BACK TO MAIN MENU"<<endl;
	}
}

int main(){
	bool CorrectlyOpened;// This is for checking whether input file opened correctly or not.
	string UserResponse;
	string inputFileName;

	/****************************************************************************
	This is for understanding which step we are for taking file inputs that is,
	it allows us to decide which input we should receive.
	*****************************************************************************/
	int inputTimes=-1;

	while (true)
	{
		inputTimes++;
		if (inputTimes==0)
		{
			cout <<"If you want to open a service <function> defining file, then press (Y/y) for 'yes', otherwise press any single key"<<endl;
			cin >>UserResponse;
			if (UserResponse != "y" && UserResponse != "Y")
			{
				cout << "You do not want to open a service"<<endl;
				cout << "Exiting..."<<endl;
				break;
			}
		}
		else if (inputTimes>0)
		{
			cout <<"Do you want to open another service defining file?"<<endl;
			cout << "Press (Y/y) for 'yes', otherwise press anykey"<<endl;
			cin >>UserResponse;
		}
		if (UserResponse=="y" || UserResponse=="Y")
		{
			cout <<"Enter the input file name: ";
			cin >>inputFileName;
			CorrectlyOpened=LinkedListCreator(inputFileName);
			if (!CorrectlyOpened) break;		
		}
		else
		{
			break;
		}
	}
	if (inputTimes>0 && CorrectlyOpened )
	{
		
		LinkedListPrinter();
		while (true){
		 cout << endl;
		 cout<<"**********************************************************************"<<endl
		 <<"**************** 0 - EXIT PROGRAM *************"<<endl
		 <<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST *************"<<endl
		 <<"**************** 2 - ADD A STUDENT SERVICE REQUEST *************"<<endl
		 <<"**************** 3 - SERVE (PROCESS) A REQUEST *************"<<endl
		 <<"**********************************************************************"<<endl;
			cout << endl;
			int option;
			cout << "Pick an option from above (int number from 0 to 3): ";
			cin>>option;
			switch (option)
			{
				case 0:
					cout<<"PROGRAM EXITING ... "<<endl;
					system("pause");
					exit(0);
				case 1:
					addInstructorRequest();
					break;
				case 2:
					addStudentRequest();
					break;
				case 3:
					processARequest();
					break;
				default:
					cout<<"INVALID OPTION!!! Try again"<<endl;
			}
		}	
	}
	

	// BELOW PARTS FOR RETURNING DYNAMICALLY ALLOCATED MEMORY TO THE HEAP.

	// THIS IS FOR DEALLOCATING MEMORY OF STUDENTS' QUEUE BY USING MEMBER FUNCTION(CLEAR()) OF DYNAMIC QUEUE CLASS.
	StudentQueue.clear();

	// THIS IS FOR DEALLOCATING MEMORY OF STATIC INSTRUCTORS' QUEUE.
	delete [] InstructorQueue.queueArray;

	// THIS IS FOR DEALLOCATING MEMORY OF SHARED STACK. I WROTE CLEAR MEMBER FUNCTION FOR DYNAMIC STACK CLASS.
	sharedStack.clear();

	// THIS IS FOR DEALLOCATING MEMORY OF LINKED LIST THAT HOLDS FUNCTIONS AND COMMANDS.
	commands *removeCommand;
	while (head)
	{
		commands *iterator = head->firstCommand;
		while (iterator)
		{
			removeCommand= iterator->down;
			delete iterator;
			iterator =removeCommand;
		}
		functions *removeHead =head;
		head = head	->next;
		delete removeHead;
	}
	head = NULL;

	return 0;
}