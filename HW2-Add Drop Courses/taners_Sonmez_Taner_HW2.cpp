/************************************************************************************************************
Purpose: This program is a simplified version of the add/drop system that is used in the universities.
Author: Taner Giray Sonmez
Date: 26/10/2021
*************************************************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "strutils.h"//for using atoi


using namespace std;

struct courseNode
{
	string courseCode, courseName;
	vector<int> studentsAttendingIDs;
	courseNode * next;

	courseNode::courseNode(string code,string name,int id,courseNode *ptr){
		courseCode=code;
		courseName=name;
		studentsAttendingIDs.push_back(id);
		next= ptr;
	}
};

/****************************************************************************************
This function returns true if the nodes contain given course, otherwise it returns false.
*****************************************************************************************/
bool courseExistenceChecker(const string & courseCode,courseNode *head){
	bool result=false;
	while (head!=NULL)
	{
		if (head->courseCode==courseCode)
		{
			result=true;
		}
		head=head->next;
	}
	return result;
}

/**************************************************************************************
This function appends student's id into vector of the proper node, if given node exist.
***************************************************************************************/
void existenceCourseUpdater(const string & courseCode,courseNode *head,const int & studentID){
	while (head!=NULL)
	{
		if (head->courseCode==courseCode)
		{
			head->studentsAttendingIDs.push_back(studentID);
		}
		head=head->next;
	}
}

/***************************************************
This function prints the nodes in the wanted format.
****************************************************/
void nodePrinter(courseNode *head){
	while (head!=NULL)
	{
		cout<< head->courseCode<<" "<<head->courseName<<": ";
		for (int i = 0; i < head->studentsAttendingIDs.size(); i++)
		{
			cout << head->studentsAttendingIDs[i]<<" ";
		}
		head=head->next;
		cout <<endl;
	}
}

/*******************************************************************************
This function builds the nodes while at the same time sorting nodes as desired.
********************************************************************************/
void nodeSorter(courseNode * & head,const string & courseCode,const string & courseName,const int & studentId){
	courseNode *temp =head;//for iteration
	courseNode *temp2=head;
	courseNode *temp3;
	while (temp!=NULL)
	{
		if((courseName > temp->courseName ) && (temp->next==NULL))//if coursename comes after the tail.
		{
			temp->next= new courseNode(courseCode,courseName,studentId,NULL);
		}
		else if (courseName < (head->courseName))//if coursename comes before the head.
		{
			head = new courseNode(courseCode,courseName,studentId,temp2);
		}
		else if((courseName>(temp->courseName)) && (courseName<(temp->next->courseName)) && (temp->next!=NULL))//if coursename is between tail and head.
		{
			temp3=temp->next;
			temp->next=new courseNode(courseCode,courseName,studentId,temp3);
		}
		temp=temp->next;
	}
}

/********************************************
This function sorts the vector in the nodes.
*********************************************/
void vectorSorter(courseNode *head){
	while (head!=NULL)
	{
		for (int i = 1; i < head->studentsAttendingIDs.size(); i++)
		{
			for (int a = i; a > 0; a--)
			{
				if (head->studentsAttendingIDs[a] < head->studentsAttendingIDs[a-1])
				{
					int temp = head->studentsAttendingIDs[a];
					head->studentsAttendingIDs[a] = head->studentsAttendingIDs[a-1];
					head->studentsAttendingIDs[a-1] = temp;
				}       
			}    
		}
		head=head->next;
	}		
}

/***************************************************************************************************************************
If the user choose option 1(Add to List),this function calls function nodeSorter(in line 80) for building new node and prints
proper output messages.
****************************************************************************************************************************/
void addToListPlacements(const string & courseName,const string & courseCode,const int & studentId,courseNode * & head){
	courseNode *temp=head;
	bool alreadyEnrolled=false;
	bool courseExist=false;
	while (temp!=NULL)
	{
		if (temp->courseCode==courseCode)
		{
			courseExist=true;
			for (int i = 0; i <temp->studentsAttendingIDs.size() ; i++)
			{
				if (temp->studentsAttendingIDs[i]==studentId)
				{
					alreadyEnrolled=true;
				}
			}
			if (!alreadyEnrolled)
			{
				temp->studentsAttendingIDs.push_back(studentId);
			}
		}
		temp=temp->next;
	}
	if (alreadyEnrolled && courseExist)
	{
		cout << "Student with id " << studentId << " already is enrolled to " << courseCode<< ". No action taken."<<endl;
	}
	if (!alreadyEnrolled && courseExist)
	{
		cout<<"Student with id " << studentId << " is enrolled to "<< courseCode<<"."<<endl;
	}
	if (courseExist==false)
	{
		nodeSorter(head,courseCode,courseName,studentId);
		cout<< courseCode << " does not exist in the list of Courses. It is added up."<<endl;
		cout<<"Student with id " << studentId << " is enrolled to "<< courseCode<<"."<<endl;
	}
	vectorSorter(head);
}

/****************************************************************************************************************
If the user choose option 2(Drop from List),this function removes given student's id from the node and prints
proper output messages.
*******************************************************************************************************************/
void DropListPlacements(const string & courseName,const string & courseCode,const int & studentId,courseNode * & head){
	courseNode *temp=head;
	bool alreadyEnrolled=false;
	bool courseExist=false;
	int removingIdx=0;
	while (temp!=NULL)
	{
		if (temp->courseCode==courseCode)
		{
			courseExist=true;
			for (int i = 0; i <temp->studentsAttendingIDs.size() ; i++)
			{
				if (temp->studentsAttendingIDs[i]==studentId)
				{
					alreadyEnrolled=true;
					removingIdx=i;
					temp->studentsAttendingIDs.erase(temp->studentsAttendingIDs.begin()+removingIdx);
					
				}
			}
		}
		temp=temp->next;
	}
	if (alreadyEnrolled && courseExist)
	{
		cout<<"Student with id " << studentId << " has dropped "<< courseCode<<"."<<endl;
	}
	if (!alreadyEnrolled && courseExist)
	{
		cout<<"Student with id " << studentId << " is not enrolled to "<< courseCode<<", thus he can't drop that course."<<endl;
	}
	if (courseExist==false)
	{
		cout << "The "<<courseCode <<" course is not in the list, thus student with id " << studentId << " can't be dropped"<<endl;
	}
	vectorSorter(head);
}

/*******************************************************************************
This function takes and parses inputs(if option 1 or 2 selected) and sends input
as a argument to either DropListPlacements() or addToListPlacements().
********************************************************************************/
void TakingInput(courseNode * & head,const int & selectedOption){
	if (selectedOption==1)
	{
		cout<<"Give the student ID and the course names and course codes that he/she wants to add:"<<endl;
	}
	else if (selectedOption==2)
	{
		cout<<"Give the student ID and the course names and course codes that he/she wants to drop:"<<endl;
	}
	string userAnswer;
	string word;
	string courseName,courseCode;
	int counter=0;
	int studentId=0;
	bool temp=false;
	int write=0;
	getline(cin,userAnswer);
	getline(cin,userAnswer);
	istringstream parse(userAnswer);
	while (parse>>word)
	{
		if (atoi(word)==0 && word.length()!=0)
		{
			counter++;
		}	
		if (atoi(word)==0 && counter==1 && word.length()!=0)
		{
			courseCode=word;
			write++;			
		}
		else if (atoi(word)==0 && counter==2 && word.length()!=0)
		{
			courseName=word;
			write++;
			counter=0;
		}
		else if(atoi(word)!=0)
		{
			studentId = atoi(word);
			temp=true;
		}
		if (temp && write==0 && word.length()!=0)
		{
			if (selectedOption==1)
			{
				addToListPlacements(courseName,courseCode,studentId,head);
			}
			else if (selectedOption==2)
			{
				DropListPlacements(courseName,courseCode,studentId,head);
			}
			
		}
		if (write==2)
		{
			write=0;
		}
	}
}

/**************************************************************************************************
This function prints the nodes as wanted format, if option 4(Finish Add/Drop and Exit) is selected.
***************************************************************************************************/
void finishAndPrint(courseNode *head){
	while (head!=NULL)
	{
		if (head->studentsAttendingIDs.size() < 3)
		{
			cout<< head->courseCode<<" "<<head->courseName<<" ";
			for (int i = 0; i < head->studentsAttendingIDs.size(); i++)
			{
				cout << head->studentsAttendingIDs[i]<<" ";
			}
			cout <<"-> This course will be closed";
		}
		else
		{
			cout<< head->courseCode<<" "<<head->courseName<<": ";
			for (int i = 0; i < head->studentsAttendingIDs.size(); i++)
			{
				cout << head->studentsAttendingIDs[i]<<" ";
			}
		}
		head=head->next;
		cout <<endl;
	}
}

/*******************************************************************************************************
This function returns all the dynamically allocated memory to the heap before the termination. I took it
from the lecture material which is "2.2-pointers-linkedlists".
*********************************************************************************************************/
void deleteNodes(courseNode *head){
	if (head != NULL)
	{
      deleteNodes(head->next);
      delete head;
	}
}

int main(){
	cout <<"Please enter file name:"<<endl;
	string fileName;
	cin >>fileName;
	ifstream input;
	input.open(fileName.c_str());
	cout << "Successfully opened file " << fileName<<endl;
	string line;
	courseNode *head;
	courseNode *iterator;
	int counter=0;
	while (getline(input,line))
	{
		counter++;
		istringstream parse(line);
		string courseCode,courseName,studentId;
		parse >> courseCode >> courseName >> studentId;
		if (line.length()!=0)
		{
				if (counter==1)
				{
					head= new courseNode(courseCode,courseName,atoi(studentId),NULL);	
					iterator =head;
				}
				else
				{
					if (courseExistenceChecker(courseCode,head))
					{		
						existenceCourseUpdater(courseCode,head,atoi(studentId));
					}
					else
					{
						nodeSorter(head,courseCode,courseName,atoi(studentId));
					}
				}
		}	
	}
	vectorSorter(head);
	cout << "The linked list is created."<<endl;
	cout << "The initial list is:"<<endl;
	nodePrinter(head);
	cout<<endl;
	int userSelection;
	do
	{
		cout << "Please select one of the choices:"<<endl;
		cout <<"1. Add to List"<<endl;
		cout<<"2. Drop from List"<<endl;
		cout<<"3. Display List"<<endl;
		cout <<"4. Finish Add/Drop and Exit"<<endl;
		cin >> userSelection;
		if (userSelection==1)
		{
			TakingInput(head,1);
			cout <<endl;
		}
		else if (userSelection==2)
		{
			TakingInput(head,2);
			cout <<endl;
		}
		else if (userSelection==3)
		{
			cout << "The current list of course and the students attending them:"<<endl;
			nodePrinter(head);
			cout <<endl;
		}
		else if (userSelection==4)
		{
			cout<<"The add/drop period is finished. Printing the final list of courses and students attending them."<<endl;
			cout<<"NOTE: Courses with less than 3 students will be closed this semester."<<endl;
			finishAndPrint(head);
			cout<<endl;
			deleteNodes(head);
			head=NULL;
		}
	} while (userSelection!=4);
	input.close();
	return 0;
}