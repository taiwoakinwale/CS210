#include <string>
#include "Doctor.h"

#ifndef Patient_HEADER
#define Patient_HEADER
using namespace std;

//Patient class
class Patient
{
private:

	//Variables
	string name; //to hold patient name
	int age; //to hold patient age
	int code; //to hold patient specialty code

public:

	//Constructor
	Patient()
	{
		name = "";
		age = -1;
		code = -1;
	}

	// Setters

	//SET NAME
	void setName(string patName) //sets patient name
	{
		name = patName;
	}

	//SET AGE
	void setAge(int patAge) //sets patient age
	{
		age = patAge;
	}

	//SET CODE
	void setCode(int patCode) //sets patient specialty code
	{
		if (age >= 16)
			code = patCode;

		//if under 16, code is automatically set to 1 (PED) for pediatrician
		if (age < 16)
			code = PED;
	}

	//Accessors

	//GET NAME
	string getName() //returns patient's name
	{
		return name;
	}

	//GET AGE
	int getAge() //returns patient's age
	{
		return age;
	}

	//GET CODE
	int getCode() //returns patient's specialty code
	{
		return code;
	}

};

#endif