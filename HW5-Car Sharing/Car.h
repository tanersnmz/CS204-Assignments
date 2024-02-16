/******************************
Created by Taner Giray Sonmez
Date of Creation: 6.12.2021
Car Class
******************************/

#ifndef CAR_H
#define CAR_H

class Car
{
	public:

		//PARAMETRIC CONSTRUCTOR
		Car(double fuel,double insurance,double distance); 

		//MEMBER FUNCTIONS
		void display() const;
		double & getFuel(); 
		double & getInsurance();
		double & getDistance(); 

	private:
		double fuelLevel; // It holds the fuel level of the car.
		double insuranceFee; // It holds the insurance fee of the car.
		double totalDistance; // It holds the total distance that the car has travelled.

};
#endif

