/*******************************************************************************************************************
Purpose: This program is a simplified version of a bus line/stop management system that is used in the everyday life.
Author: Taner Giray Sonmez
Date: 17/11/2021
******************************************************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;



struct busStop
{
	string busStopName;
	busStop *left;
	busStop *right;

	busStop::busStop(const string & name, busStop *Right, busStop *Left){
		right=Right;
		left=Left;
		busStopName=name;
	}
};

struct busLine 
{
	string busLineName;
	busLine *next;
	busStop *busStops;

	busLine::busLine(const string & name, busLine *linePtr, busStop *stopsPtr){
		busLineName=name;
		next= linePtr;
		busStops= stopsPtr;
	}
};

busLine * head=NULL;

void printMainMenu() {
	cout << endl;
	cout <<"I***********************************************I"<<endl
	<<"I 0 - EXIT PROGRAM I"<<endl
	<<"I 1 - PRINT LINES I"<<endl
	<<"I 2 - ADD BUS LINE I"<<endl
	<<"I 3 - ADD BUS STOP I"<<endl
	<<"I 4 - DELETE BUS LINE I"<<endl
	<<"I 5 - DELETE BUS STOP I"<<endl
	<<"I 6 - PATH FINDER I"<<endl
	<<"I***********************************************I"<<endl
	<<">>";
	cout << endl;
}

bool consistencyCheck() {
	busLine* currBL = head; //a global variable
	while(currBL) {
	busStop* currBS = currBL->busStops;
	while(currBS) {
	busStop* rightBS = currBS->right;
	if(rightBS && rightBS->left != currBS) {
	cout << "Inconsistency for " << currBL->busLineName
	 << " " << currBS->busStopName << endl;
	return false;
	}
	currBS = currBS->right;
	}
	currBL = currBL->next;
	}
	return true;
}

/********************************************************
This function prints the bus lines in the desired format.
*********************************************************/
void printBusLines(){
	busLine *temp= head;
	busStop *stemp= temp->busStops;
	while (temp !=NULL)
	{
		cout << temp->busLineName<<":";
		while (stemp!=NULL)
		{
			if (stemp->right==NULL)
			{
				cout<<stemp->busStopName;
			}
			else
			{
				cout<<stemp->busStopName<< "<->";
			}
			stemp = stemp->right;	
		}
		cout<<endl;
		temp = temp->next;
		if (temp!=NULL)
		{
			stemp = temp->busStops;	
		}
	}
}

/**************************************************************************************************************************
This function takes the name of the bus line as an input and then returns true if such bus line exists in the linked list. 
Otherwise, it returns false.
**************************************************************************************************************************/
bool existentLineChecker(const string & busLineName){
	busLine *temp =head;
	while (temp!=NULL)
	{
		if (temp->busLineName==busLineName)
		{
			return true;
		}
		temp=temp->next;
	}
	return false;
}

/******************************************************************************************************************************************
This function takes a vector of string that contains stop names and it also takes a single bus stop as a second input.
If a bus stop exists in the vector, it returns true. Otherwise, it returns false. I used this function as a kind of helper in addBusLine().
*******************************************************************************************************************************************/
bool existentStopChecker(const vector<string> & Stops,const string & stopName){
	for (int i = 0; i < Stops.size(); i++)
	{
		if (Stops[i]==stopName)
		{
			return true;
		}
	}
	return false;
}

/*********************************************************************
This function was coded for adding a new bus line to the linked list.
**********************************************************************/
void addBusLine(){
	string userAnswer;
	vector<string> newStops;
	string userChoice;
	cout << "Enter the name of the new bus line (0 for exit to main menu)."<<endl;
	cin>>userChoice;
	if (userChoice!="0")
	{
		while (userChoice!="0" && existentLineChecker(userChoice))
		{
			cout <<"Bus line already exists: enter a new one (0 for exit)"<<endl;
			cin>>userChoice;
		}
		if (userChoice !="0")
		{
			newStops.push_back(userChoice);
			cout <<"Enter the name of the next bus stop (enter 0 to complete)"<<endl;
			cin>>userChoice;
			if (userChoice=="0")
			{
				cout << "You are not allowed to add an empty bus line"<<endl;
			}
			else
			{
				int stopCounter=0;
				newStops.push_back(userChoice);
				stopCounter++;
				while (true)
				{
					cout <<"Enter the name of the next bus stop (enter 0 to complete)"<<endl;
					cin>>userChoice;
					if (userChoice=="0")
					{
						break;
					}
					else if (existentStopChecker(newStops,userChoice))
					{
						cout << "Bus stop already exists in the line"<<endl;
					}
					else if (userChoice!="0" && existentStopChecker(newStops,userChoice)==false)
					{
						stopCounter++;
						newStops.push_back(userChoice);
					}
				}
				if (stopCounter==0)
				{
					cout <<"You are not allowed to add an empty bus line"<<endl;
				}
				else
				{
					cout<<"The bus line information is shown below"<<endl;
					cout <<newStops[0]<<":";
					for (int i = 1; i < newStops.size(); i++)
					{
						if (i!=newStops.size()-1)
						{
							cout << newStops[i]<<"<->";
						}
						else
						{
							cout << newStops[i];
						}
					}
					cout <<endl;
					cout<<"Are you sure? Enter (y/Y) for yes (n/N) for no?"<<endl;
					cin>>userAnswer;
					if (userAnswer=="Y" || userAnswer=="y")
					{
						busLine *newLine;
						busLine *temp=head;
						busStop *newStop;
						busStop *iterator;
						for (int i = 0; i < newStops.size(); i++)
						{
							if (i==0)
							{
								newLine = new busLine(newStops[i],NULL,NULL);
								head = newLine;
								head->next=temp;
							}
							else if(i==1)
							{
								 newStop = new busStop(newStops[i],NULL,NULL);
								 head->busStops = newStop;
								 iterator = newStop;
							}
							else
							{
								newStop = new busStop(newStops[i],NULL,iterator);
								iterator->right =newStop;
								iterator=iterator->right;
							}
						}
						printBusLines();
					}
				}
			}
		}
	}
}

/***********************************************************************
This function returns true if a given bus stop exists in the linked list.
Otherwise, it returns false.
************************************************************************/
bool existentStopChecker2(const string & stopName,busStop *iterator){
	bool status=false;
	while (iterator!=NULL)
	{
		if (iterator->busStopName==stopName)
		{
			status=true;
		}
		iterator = iterator->right;
	}
	return status;

}

/********************************************************************************************
This function was coded for adding a new bus stop to an existing bus line in the linked list.
*********************************************************************************************/
void addBusStop(){
	busLine *temp=head;
	busStop *stemp;
	cout<<"Enter the name of the bus line to insert a new bus stop (0 for main menu)"<<endl;
	string busline;
	cin>>busline;
	if (busline != "0")
	{
		if (!existentLineChecker(busline))
		{
			cout<<"Bus line cannot be found. Going back to previous menu."<<endl;
		}
		else
		{
			while (temp->busLineName!=busline)
			{
				temp=temp->next;
			}	
			cout<<"The bus line information is shown below"<<endl;
			cout << temp->busLineName<<":";
			stemp= temp->busStops;
			while (stemp!=NULL)
			{
				if (stemp->right==NULL)
				{
					cout<<stemp->busStopName;
				}
				else
				{
					cout<<stemp->busStopName<< "<->";
				}
				stemp = stemp->right;	
			}
			cout<<endl;
			cout<<"Enter the name of the new bus stop"<<endl;
			string bustop;
			cin>>bustop;
			stemp= temp->busStops;
			bool status = existentStopChecker2(bustop,stemp);
			if (status==true)
			{
				cout<<"Bus stop already exists. Going back to previous menu."<<endl;
			}
			else
			{
				cout<<"Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)"<<endl;
				string newStop;
				cin>>newStop;
				if (newStop=="0")
				{
					busStop *temp2 = temp->busStops;
					temp->busStops = new busStop(bustop,temp2,NULL);
					temp2->left= temp->busStops;
					stemp = temp->busStops;
					printBusLines();
				}
				else
				{
					while (true)
					{
						if (existentStopChecker2(newStop,stemp)==false && newStop!="0")
						{
							cout<<"Bus stop does not exist. Typo? Enter again (0 for main menu)"<<endl;
							cin>>newStop;
						}
						else if(existentStopChecker2(newStop,stemp)==true && newStop!="0")
						{
							while (stemp!=NULL)
							{
								if (stemp->busStopName==newStop && stemp->right !=NULL)
								{
									busStop *stop = new busStop(bustop,stemp->right,stemp);
									stemp->right=stop;
									stemp->right->right->left =stop;
								}
								else if (stemp->busStopName==newStop && stemp->right ==NULL)
								{
									busStop *stop = new busStop(bustop,NULL,stemp);
									stemp->right = stop;
								}
								stemp=stemp->right;
							}
							stemp = temp->busStops;
							printBusLines();
							break;
						}
						else if(existentStopChecker2(newStop,stemp)==true && newStop=="0")
						{
							busStop *temp2 = temp->busStops;
							temp->busStops = new busStop(bustop,temp2,NULL);
							temp2->left= temp->busStops;
							stemp = temp->busStops;
							printBusLines();
							break;
						}
						else if (existentStopChecker2(newStop,stemp)==false && newStop=="0")
						{
							break;
						}
					}
				}
			}	
		}
	}
}

/****************************************************************
This function is deleting an existing bus line in the linked list.
*****************************************************************/
void deleteBusLine(){
	busLine *headTemp =head;
	cout<<"Enter the name of the bus line to delete"<<endl;
	string lineForDeleting;
	cin >>lineForDeleting;
	if (existentLineChecker(lineForDeleting))
	{
		int counter=0;
		while (headTemp->busLineName!=lineForDeleting)
		{
			counter++;
			headTemp=headTemp->next;
		}
		busStop *stopTemp = headTemp->busStops;
		if (headTemp==head)
		{
			while (stopTemp!=NULL)
			{
				busStop *forDelete = stopTemp->right;
				delete stopTemp;
				stopTemp = forDelete;
			}
			head = head->next;
			delete headTemp;
		}
		else if (headTemp!=head && headTemp->next!=NULL)
		{
			busLine *iterator = head;
			for (int i = 0; i < counter-1; i++)
			{
				iterator=iterator->next;
			}
			while (stopTemp!=NULL)
			{
				busStop *forDelete = stopTemp->right;
				delete stopTemp;
				stopTemp = forDelete;
			}
			iterator->next= headTemp->next;
			delete headTemp;
		}
		else if (headTemp!=head && headTemp->next==NULL)
		{
			busLine *forNull = head;
			while (forNull->next->next!=NULL)
			{
				forNull=forNull->next;
			}
			while (stopTemp!=NULL)
			{
				busStop *forDelete = stopTemp->right;
				delete stopTemp;
				stopTemp = forDelete;
			}
			delete headTemp;
			forNull->next=NULL;
		} 
		printBusLines();
	}
	else
	{
		cout<<"Bus line cannot be found. Going back to the previous (main) menu."<<endl;
	}
}

/**********************************************************************************************************************
This function was a part of the bonus question, it simply returns true if interchanges are existed between given stops.
***********************************************************************************************************************/
bool interChangeFinder(const string & stop1, const string & stop2,busLine * & returnerHead){
	busLine *headForPrinting =head;
	busStop *iterator;
	int counter;
	bool stat =false;
	int dontChange=0;
	while (headForPrinting!=NULL)
	{
		counter=0;
		iterator=headForPrinting->busStops;
		while (iterator!=NULL)
		{
			if (iterator->busStopName==stop1 || iterator->busStopName == stop2)
			{
				counter++;
			}
			if (counter==2)
			{
				dontChange++;
				if (dontChange==1)
				{
					returnerHead=headForPrinting;
				}
				stat=true;
			}
			iterator=iterator->right;
		}
		headForPrinting=headForPrinting->next;
	}
	return stat;
}

/*******************************************************************************************
This function is finding how many elements(bus stops) exist between given stops. 
It simply uses counters(and also returns counters by using reference parameter) to show,
how many times the program should use "->right" or "->left"
in order to arrive given bus stop from another given bus stop.
********************************************************************************************/
void twoStopExistence(busLine *h,const string & stop1, const string & stop2,int & stop, int & togo){
	busStop *iterator = h->busStops;
	int counter=0;
	int tempCounter=0;
	while (iterator!=NULL)
	{
		tempCounter++;
		if (iterator->busStopName == stop1)
		{
			counter++;
			stop = tempCounter;
		}
		if (iterator->busStopName ==stop2)
		{
			counter++;
			togo=tempCounter;
		}
		iterator = iterator->right;
	}
	
}

/**************************************************************
This function deletes an existing bus stop in the linked list.
****************************************************************/
void deleteBusStop(){
	busLine *temp=head;
	busStop *stemp;
	cout<<"Enter the name of the bus line to delete a new bus stop (0 for main menu)"<<endl;
	string busLine1;
	cin>>busLine1;
	if (busLine1!="0")
	{
		if (existentLineChecker(busLine1))
		{
			while (temp->busLineName!=busLine1)
			{
				temp=temp->next;
			}	
			cout<<"The bus line information is shown below"<<endl;
			cout << temp->busLineName<<":";
			stemp= temp->busStops;
			int counter=0;
			while (stemp!=NULL)
			{
				if (stemp->right==NULL)
				{
					cout<<stemp->busStopName;
				}
				else
				{
					cout<<stemp->busStopName<< "<->";
				}
				stemp = stemp->right;	
			}
			cout<<endl;
			stemp= temp->busStops;
			cout<<"Enter the name of the bus stop to delete (0 for main menu)"<<endl;
			string stopForDeleting;
			cin>>stopForDeleting;
			while (true)
			{
				if (stopForDeleting=="0")
				{
					break;
				}
				else if (existentStopChecker2(stopForDeleting,stemp) && stopForDeleting!="0")
				{
					int lastOne=0;
					busStop *copyStemp =temp->busStops;
					busStop *numOfStops = temp->busStops;
					while (copyStemp->right!=NULL)
					{
						copyStemp=copyStemp->right;
					}
					while (numOfStops!=NULL)
					{
						lastOne++;
						numOfStops=numOfStops->right;
					}
					if (lastOne==1)
					{
						string lineForDeleting = temp->busLineName;
						busLine *headTemp =head;
						int counter=0;
						while (headTemp->busLineName!=lineForDeleting)
						{
							counter++;
							headTemp=headTemp->next;
						}
						busStop *stopTemp = headTemp->busStops;
						if (headTemp==head)
						{
							while (stopTemp!=NULL)
							{
								busStop *forDelete = stopTemp->right;
								delete stopTemp;
								stopTemp = forDelete;
							}
							head = head->next;
							delete headTemp;
						}
						else if (headTemp!=head && headTemp->next!=NULL)
						{
							busLine *iterator = head;
							for (int i = 0; i < counter-1; i++)
							{
								iterator=iterator->next;
							}
							while (stopTemp!=NULL)
							{
								busStop *forDelete = stopTemp->right;
								delete stopTemp;
								stopTemp = forDelete;
							}
							iterator->next= headTemp->next;
							delete headTemp;
						}
						else if (headTemp!=head && headTemp->next==NULL)
						{
							busLine *forNull = head;
							while (forNull->next->next!=NULL)
							{
								forNull=forNull->next;
							}
							while (stopTemp!=NULL)
							{
								busStop *forDelete = stopTemp->right;
								delete stopTemp;
								stopTemp = forDelete;
							}
							delete headTemp;
							forNull->next=NULL;
						}
						cout <<endl;
						printBusLines();
						break;
					}
					else
					{
						if (temp->busStops->busStopName==stopForDeleting)
						{
							temp->busStops=stemp->right;
							temp->busStops->left=NULL;
							delete stemp;
						}
						else if (temp->busStops->busStopName!=stopForDeleting && stopForDeleting!=copyStemp->busStopName)
						{
							int counter=0;
							while (stemp->busStopName !=stopForDeleting)
							{
								counter++;
								stemp=stemp->right;
							}
							busStop *prevStop= temp->busStops;
							for (int i = 0; i < counter-1; i++)
							{
								prevStop=prevStop->right;
							}
							prevStop->right=stemp->right;
							stemp->right->left=prevStop;
							delete stemp;
							stemp= temp->busStops;
						}
						else if (temp->busStops->busStopName!=stopForDeleting && stopForDeleting==copyStemp->busStopName)
						{	
							int counter=0;
							while (stemp->busStopName !=stopForDeleting)
							{
								counter++;
								stemp=stemp->right;
							}
							busStop *prevStop= temp->busStops;
							for (int i = 0; i < counter-1; i++)
							{
								prevStop=prevStop->right;
							}
							delete stemp;
							prevStop->right=NULL;						
						}
						cout <<endl;
						printBusLines();
						break;
					}
				}
				else if (existentStopChecker2(stopForDeleting,stemp)==false && stopForDeleting!="0")
				{
					cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)"<<endl;
					cin>>stopForDeleting;
				}
			}
		}
		else
		{
			cout << "Bus line cannot be found. Going back to previous (main) menu."<<endl;
		}
	}
}

/***********************************************************************
This function returns true if the given stop exists in the linked list. 
Otherwise, it returns false.
***********************************************************************/
bool existenceOfStop(const string & stop){
	busLine *temp =head;
	busStop *iterator;
	bool status =false;
	while (temp!=NULL)
	{
		iterator=temp->busStops;
		while (iterator!=NULL)
		{
			if (iterator->busStopName ==stop)
			{
				status =true;
			}
			iterator=iterator->right;
		}
		temp=temp->next;
	}
	return status;
}

/*****************************************************************************
This function is used to find a path between two bus stops in the linked list.
It also does the job for bonus question.
******************************************************************************/
void pathfinder(){
	int noBusStop=0;
	busLine *temp= head;
	int useBonus=1;
	cout<<"Where are you now?"<<endl;
	string whereNow,toGo;
	cin>>whereNow;
	if (!existenceOfStop(whereNow))
	{
		cout << "Bus stop does not exist in the table. Going back to previous menu."<<endl;
		noBusStop=1;
	}
	else
	{
		cout << "Where do you want to go?"<<endl;
		cin >>toGo;
		if (whereNow!=toGo)
		{
			if (!existenceOfStop(toGo))
			{
				cout << "Bus stop does not exist in the table. Going back to previous menu."<<endl;
				noBusStop=1;
			}
			else
			{
				busLine *headForPathFinder;
				if (interChangeFinder(toGo, whereNow,headForPathFinder))
				{
					useBonus=0;
					busStop *pointingStop = headForPathFinder->busStops;
					busStop *pointingWhereToGo = headForPathFinder->busStops;
					int pointingStopCounter=0,pointingWhereToGoCounter=0;
					while (pointingStop->busStopName != whereNow)
					{
						pointingStopCounter++;
						pointingStop= pointingStop->right;
					}
					while (pointingWhereToGo->busStopName != toGo)
					{
						pointingWhereToGoCounter++;
						pointingWhereToGo=pointingWhereToGo->right;
					}
					cout <<"You can go there by " << headForPathFinder->busLineName<<":";
					if (pointingStopCounter>pointingWhereToGoCounter)
					{
						while (pointingWhereToGo->busStopName!= pointingStop->busStopName)
						{
							cout << pointingStop->busStopName<<"->";
							pointingStop=pointingStop->left;
						}
						cout << pointingStop->busStopName<<endl;
					}
					else if (pointingStopCounter<pointingWhereToGoCounter)
					{
						while (pointingWhereToGo->busStopName!= pointingStop->busStopName)
						{
							cout << pointingStop->busStopName<<"->";
							pointingStop=pointingStop->right;
						}
						cout << pointingStop->busStopName<<endl;
					}
				}
			}
		}	
	}
	cout << endl;
	cout << endl;
	int founded=0;
	int bonusFindTheSolution=0;
	if (useBonus==1 && whereNow!=toGo)
	{
		temp = head;
		busStop *busStopIterator;
		int stopCounter=0;
		int togoCounter=0;
		while (temp!=NULL)
		{
			busStopIterator=temp->busStops;
			while (busStopIterator!=NULL)
			{
				if (busStopIterator->busStopName == whereNow)
				{					
					busStop *tempForwardIterator = busStopIterator->right;				
					while (tempForwardIterator!=NULL)
					{						
						busLine *headForWriting =NULL;
						if (interChangeFinder(tempForwardIterator->busStopName,toGo,headForWriting) )
						{			
							bonusFindTheSolution=1;
							busStop *stopPrinting =busStopIterator;
							cout << "You can go there by "<< temp->busLineName<<":";
							while (stopPrinting->busStopName !=tempForwardIterator->busStopName)
							{
								cout <<stopPrinting->busStopName<<"->";
								stopPrinting=stopPrinting->right;
							}
							cout << stopPrinting->busStopName;
							cout << endl;
							twoStopExistence(headForWriting,tempForwardIterator->busStopName, toGo,stopCounter, togoCounter);;
							busStop *stopIterator = headForWriting->busStops;
							founded=1;
							if (stopCounter>togoCounter)
							{
								for (int i = 0; i < stopCounter-1; i++)
								{
									stopIterator=stopIterator->right;
								}
								cout << "                    ";
								cout << headForWriting->busLineName<<":";
								for (int i = 0; i < stopCounter-togoCounter; i++)
								{
									cout<<stopIterator->busStopName<<"->";
									stopIterator=stopIterator->left;
								}
								cout << stopIterator->busStopName;
								cout << endl<<endl;
								break;
							}
							else if (togoCounter>stopCounter) 
							{					
								for (int i = 0; i < stopCounter-1; i++)
								{
									stopIterator=stopIterator->right;
								}
								cout << "                    ";
								cout << headForWriting->busLineName<<":";
								for (int i = 0; i < togoCounter-stopCounter; i++)
								{
									cout<<stopIterator->busStopName<<"->";
									stopIterator=stopIterator->right;
								}
								cout << stopIterator->busStopName;
								cout << endl<<endl;
								break;
							}
							cout <<endl;					
							togoCounter=0;
							stopCounter=0;
						}
						tempForwardIterator=tempForwardIterator->right;
					}
				}
				busStopIterator=busStopIterator->right;
			}
			temp=temp->next;
		}
		cout << endl;
		temp = head;
		togoCounter=0;
		stopCounter=0;
		if (founded==0)
		{
				while (temp!=NULL)
				{
					busStopIterator=temp->busStops;
					while (busStopIterator!=NULL)
					{
						if (busStopIterator->busStopName == whereNow)
						{							
							busStop *tempBackwardIterator = busStopIterator->left;							
							while (tempBackwardIterator!=NULL)
							{															
								busLine *headForWriting =NULL;
								if (interChangeFinder(tempBackwardIterator->busStopName,toGo,headForWriting))
								{							
									busStop *stopPrinting =busStopIterator;
									bonusFindTheSolution=1;
									cout << "You can go there by "<< temp->busLineName<<":";
									while (stopPrinting->busStopName !=tempBackwardIterator->busStopName)
									{
										cout <<stopPrinting->busStopName<<"->";
										stopPrinting=stopPrinting->left;
									}
									cout << stopPrinting->busStopName;
									cout << endl;									
									twoStopExistence(headForWriting,tempBackwardIterator->busStopName, toGo,stopCounter, togoCounter);
									int times = stopCounter-togoCounter;
									busStop *stopIterator = headForWriting->busStops;
									if (stopCounter>togoCounter) 
									{
										for (int i = 0; i < stopCounter-1; i++)
										{
											stopIterator=stopIterator->right;
										}
										cout << "                    ";
										cout << headForWriting->busLineName<<":";
										for (int i = 0; i < stopCounter-togoCounter; i++)
										{
											cout<<stopIterator->busStopName<<"->";
											stopIterator=stopIterator->left;
										}
										cout << stopIterator->busStopName;
										cout << endl<<endl;
										break;
									}
									else if (togoCounter>stopCounter) 
									{
							
							
										for (int i = 0; i < stopCounter-1; i++)
										{
											stopIterator=stopIterator->right;
										}
										cout << "                    ";
										cout << headForWriting->busLineName<<":";
										for (int i = 0; i < togoCounter-stopCounter; i++)
										{
											cout<<stopIterator->busStopName<<"->";
											stopIterator=stopIterator->right;
										}
										cout << stopIterator->busStopName;
										cout << endl<<endl;
										break;
									}
									cout <<endl;					
									togoCounter=0;
									stopCounter=0;
								}
								tempBackwardIterator=tempBackwardIterator->left;
							}
						}
						busStopIterator=busStopIterator->right;
					}
					temp=temp->next;
				}
			}
		}	
	if (bonusFindTheSolution==0 && useBonus==1 && noBusStop==0 && whereNow!=toGo)
	{
		cout << "Sorry no path from " << whereNow << " to " << toGo << " could be found." << endl;
	}
	if (whereNow==toGo)
	{
		cout << "You are in the exact stop that you want to go!"<<endl;
	}
}

void processMainMenu() {
	char input;
	do
	{
		if(!consistencyCheck()) {
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
		printMainMenu();
		cout << "Please enter your option " << endl;
		cin >> input;
			switch (input) 
			{
				case '0':
					cout << "Thanks for using our program" << endl;
					return;
				case '1':
					printBusLines();
					break;
				case '2':
					addBusLine();
					break;
				case '3':
					addBusStop();
					break;
				case '4':
					deleteBusLine();
					break;
				case '5':
					deleteBusStop();
					break;
				case '6':
					pathfinder();
					break;
				default:
					cout << "Invalid option: please enter again" << endl;
		} //switch
	} while(true);
}//processMainMenu

int main(){
	string filename = "busLines.txt";
	ifstream input;
	input.open(filename.c_str());
	string line,word;
	int counter=0;
	int newline=0;
	busLine *busLineIterator;
	busStop *busStopIterator;

	while (getline(input,line))
	{
		istringstream parse(line);
		if (line.length()>0)
		{
			while (parse >> word)
			{
				counter++;
				if (counter==1 && newline==0)
				{
					head = new busLine(word.substr(0,word.length()-1), NULL, NULL);
					busLineIterator=head;
				}
				else if (counter==1 && newline==1)
				{
					busLineIterator->next = new busLine(word.substr(0,word.length()-1),NULL,NULL);//taner
					busLineIterator = busLineIterator->next;
				}
				else if(counter==2)
				{
					busLineIterator->busStops = new busStop(word,NULL,NULL);
					busStopIterator= busLineIterator->busStops;
				}
				else
				{
					busStop *stop = new busStop(word,NULL,busStopIterator);
					busStopIterator->right=stop;
					busStopIterator= busStopIterator->right;
				}
			}
			counter=0;
			newline=1;
		}		
	}
	input.clear();
	input.seekg(0);
	processMainMenu();

	//Below lines for deallocating all dynamically allocated memory.
	busStop *fordelete;
	while (head!=NULL)
	{
		busStop *temp= head->busStops;
		while (temp!=NULL)
		{
			fordelete =temp->right;
			delete temp;
			temp = fordelete;
		}
		busLine *deleteHead = head;
		head=head->next;
		delete deleteHead;
	}
	input.close();
	return 0;
}