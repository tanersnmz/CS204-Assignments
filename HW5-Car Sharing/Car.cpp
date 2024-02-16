/******************************
Created by Taner Giray Sonmez
Date of Creation: 6.12.2021
Car Class
******************************/
#include "Car.h"
#include <iostream>

using namespace std;

//Parametric Constructor
Car::Car(double fuel,double insurance,double distance)
{
	fuelLevel=fuel;
	insuranceFee=insurance;
	totalDistance=distance;
}

//Displays fuel level, insurance fee and total distance(car has travelled) of the Car object.
void Car::display() const
{
	cout << "Fuel Level: " <<fuelLevel<<endl;
	cout << "Insurance Fee: " << insuranceFee<<endl;
	cout << "Total distance that the car has travelled: " << totalDistance<<endl;
	cout << endl;
}

//For object sharing purposes, the return type of the below functions is the reference.


//Returns the fuel level in dollars of Car object.
double & Car::getFuel() {
	return fuelLevel;
}

//Returns the insurance fee of Car object.
double & Car::getInsurance(){
	return insuranceFee;
}

//Returns the total distance that the Car object has travelled.
double & Car::getDistance(){
	return totalDistance;
}

