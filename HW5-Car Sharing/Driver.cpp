/******************************
Created by Taner Giray Sonmez
Date of Creation: 6.12.2021
Driver Class
******************************/
#include "Driver.h"
#include "Car.h"
#include<iostream>
#include<string>

using namespace std;



/***************************************************************************************
This function takes the kilometer(km) that the driver has driven so far as a parameter
and increases the total distance that the car has travelled by this km. 
Also, this function reduces the fuel level of the car by using this km.
****************************************************************************************/
void Driver::drive(int kilometers)
{
	distance+=kilometers;
	fuel-= (0.25)*kilometers;
}

/*************************************************************************************************************
According to the damage that the car had(as a parameter, namely: large, small, or medium), this function 
reduces the budget of the driver. Furthermore, this function increases the insurance fee of the car according
to damage that the car took.
**************************************************************************************************************/
void Driver::repairCar(string accident)
{
	if (accident=="LARGE")
	{
		initialBudget-=300;
		insurance += (insurance*0.20);
		cout << "300$ is reduced from the driver's budget because of the LARGE accident"<<endl;
		cout << "Yearly insurance fee is increased to "<<insurance<< " because of the LARGE accident"<<endl;
	}
	else if (accident=="MEDIUM")
	{
		initialBudget-=150;
		insurance += (insurance*0.10);
		cout << "150$ is reduced from the driver's budget because of the MEDIUM accident"<<endl;
		cout << "Yearly insurance fee is increased to "<<insurance<< " because of the MEDIUM accident"<<endl;
	}
	else if(accident=="SMALL"){
		initialBudget-=50;
		insurance += (insurance*0.05);
		cout << "50$ is reduced from the driver's budget because of the SMALL accident"<<endl;
		cout << "Yearly insurance fee is increased to "<<insurance<< " because of the SMALL accident"<<endl;
	}
}

/*************************************
This function displays driver's budget.
**************************************/
void Driver::display() const
{
	cout << "Driver Budget: " << initialBudget<<endl;
}

/************************************************************
This function fulls the fuel of the car to its maximum level.
Moreover, it decreases the budget of the driver accordingly.
************************************************************/
void Driver::fullFuel()
{
	double neededFuel = maxFuel- fuel;
	fuel=maxFuel;
	initialBudget -= neededFuel;
	cout << "Fuel is full"<<endl;
	cout << endl;
}

