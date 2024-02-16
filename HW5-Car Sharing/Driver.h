/******************************
Created by Taner Giray Sonmez
Date of Creation: 6.12.2021
Driver Class
******************************/
#ifndef DRIVER_H
#define DRIVER_H

#include "Car.h"// For object sharing purposes.
#include<string>
#include<iostream>

using namespace std;

class Driver
{
	public:

		//PARAMETRIC CONSTRUCTOR
		Driver::Driver(Car & car,double budget)
		:sharedCar(car), initialBudget(budget),fuel(car.getFuel()),insurance(car.getInsurance()),
		distance(car.getDistance()),maxFuel(car.getFuel())
		{ }

		//MEMBER FUNCTIONS
		void drive (int);
		void repairCar(string);
		void display() const;
		void fullFuel();



	private:

		//Referenced variables (shared objects between two drivers).
		Car & sharedCar; // Car object that drivers share.
		double & fuel; // It holds car object's fuel level in dollars.
		double & insurance; // It holds car object's insurance fee in dollars.
		double & distance; // It holds car object's total distance travelled in kilometers.
		

		//Not referenced variables.
		const double maxFuel; // It holds the maximum fuel that a car can have.
		double initialBudget; // It holds the starting money of the driver.


};
#endif
