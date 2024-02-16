/*******************************************************************************************************************
Purpose: 
Basically, the main idea of this program is finding, displaying and comparing the perimeter, area
and the volume of both 2D (concretely, rectangles) as well as 3D figures (right hexahedrons - boxes)
with each-other.

Author: Taner Giray Sonmez

Date: 7/01/2022

Any known bugs: No known bugs
******************************************************************************************************************/
#include <iostream>
#include <string>

using namespace std;

//This is the base class for all other classes. It is an abstract class.
//This class was designed for manipulating shapes in general.
class shape
{
public:

	virtual ~shape() {} 
	virtual float perimeter() = 0;
	virtual float area() = 0;
	virtual float volume() = 0;

	string getName() const 
	{
		return myName;
	}
protected:
	string myName; //It keeps the name of the shape.
};


//Inherits class shape. This is also an abstract class.
//This class was designed for manipulating 2D shapes.
class TwoDShape: public shape
{
public:
	TwoDShape(): volume(0.0) {}
protected:
	float volume;
};

//Inherits class shape. This is also an abstract class.
//This class was designed for manipulating 3D shapes.
class ThreeDShape: public shape	
{
public:
	ThreeDShape(): perimeter(0.0) {}
protected:
	float perimeter;
};


//Inherits class TwoDShape. This is not an abstract class.
//This class was designed for manipulating rectangles(2D shapes, i.e calculating perimeter, area etc.)
class rectangle: public TwoDShape
{
public:

	rectangle(float w, float l,string name): width(w),length(l)
	{
		myName =name;
	}

	virtual float perimeter() 
	{
		return (2*(width+length));
	}

	virtual float area() 
	{
		return (width*length);
	}

	virtual float volume()
	{
		return 0;
	}


protected:
	float width;
	float length;
};



//Inherits class ThreeDShape. This is not an abstract class.
//This class was designed for manipulating boxes(3D shapes, i.e calculating perimeter, area, volume etc.)
class Box: public ThreeDShape
{
public:

	Box(float w, float l,float h,string name): width(w),length(l),height(h)
	{
		myName=name;
	}

	virtual float perimeter()
	{
		return 0;
	}

	virtual float volume()
	{
		return (width*length*height);
	}

	virtual float area()
	{
		return (2*(width*length+width*height+length*height));
	}

protected:
	float width;
	float length;
	float height;
};




//This function gets a 1 or a 2 from the user, and according to
//user-input either creates a dynamically allocated rectangle or box.
//Moreover, in the end, it returns the shape type of pointer.
shape * getShape() {
	int userOption;
	cout << "Choose an option <1 or 2>:"<<endl;
	cout << "1. Rectangle"<<endl;
	cout << "2. Box" << endl;
	cin >> userOption;
	//This loop asks the options until the user gives correct input(i.e either 1 or 2).
	while (userOption!=1 && userOption!=2)
	{
		cout <<"UNAVAILABLE OPTION CHOSEN. Try again."<<endl;
		cout << "Choose an option <1 or 2>:"<<endl;
		cout << "1. Rectangle"<<endl;
		cout << "2. Box" << endl;
		cin >> userOption;
	}

	shape *shapePtr;//Pointer to the shape, in the end of the function, it will be returned.
	if (userOption==1)
	{
		string shapeName;
		float shapeWidth,shapeLength;
		cout<< "You chose rectangle. Give it's width, length and name:"<<endl;
		cin >>shapeWidth;
		cin>>shapeLength;
		cin >> shapeName;
		shapePtr = new rectangle(shapeWidth,shapeLength,shapeName);//Rectangle was dynamically created.
	}
	else if (userOption==2)
	{
		string shapeName;
		float shapeWidth,shapeLength,shapeHeight;
		cout<< "You chose box. Give it's width, length, height and name:"<<endl;
		cin >>shapeWidth;
		cin>>shapeLength;
		cin>>shapeHeight;
		cin >> shapeName;
		shapePtr = new Box(shapeWidth,shapeLength,shapeHeight,shapeName);//Box was dynamically created.
		
	}
	return shapePtr;// It returns pointer to shape.

}//getShape()


int main()
{
	cout<<"WELCOME TO THE SHAPE COMPARISONN PROGRAM"<<endl;
	cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
	shape *shape_1, *shape_2; /* defining two varibles, named shape_1 and shape_2 of the class shape.*/
	char c;
	while (tolower(c = getchar())!='y')
	{
		cout<<"Defining (getting) shape 1..."<<endl;
		
		shape_1 = getShape();
		cout<<"Defining (getting) shape 2..."<<endl;
		shape_2 = getShape();
		cout<<"********************************************************************"<<endl;
		cout<<"PRINTING SHAPE_1 INFOS:"<<endl<<"Name: "<<shape_1->getName()<<", perimeter: "
			<<shape_1->perimeter()<<", area: "<<shape_1->area()<<", volume: "<<shape_1->volume()<<endl<<endl;
		cout<<"PRINTING SHAPE_2 INFOS:"<<endl<<"Name: "<<shape_2->getName()<<", perimeter: "
			<<shape_2->perimeter()<<", area: "<<shape_2->area()<<", volume: "<<shape_2->volume()<<endl;		
		bool nothingInCommon=true; // to check whether they have anything in common (perimeter, area, volume)
		if(shape_1->perimeter()==shape_2->perimeter())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same perimeter, which is: "
				<<shape_1->perimeter()<<" cm."<<endl;
		}
		if(shape_1->area()==shape_2->area())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same area, which is: "
				<<shape_1->area()<<" cm^2."<<endl;
		}
		if(shape_1->volume()==shape_2->volume())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same volume, which is: "
				<<shape_1->volume()<<" cm^3."<<endl;
		}
		if (nothingInCommon)
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" don't have anything in common."<<endl;		
		
		delete shape_1;
		delete shape_2;

		cout<<"********************************************************************"<<endl;
		cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
		cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
  	}//while(tolower(c = getchar())!='y')
	cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
	system("pause");
	return 0;
}