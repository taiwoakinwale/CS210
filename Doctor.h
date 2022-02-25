#include <string>

#ifndef Doctor_h
#define Doctor_h

using namespace std;

//Specialty Code Constants
const int PED = 1;
const int GEN = 2;
const int INT = 3;
const int CAR = 4;
const int SUR = 5;
const int OBS = 6;
const int PSY = 7;
const int NEU = 8;
const int ORT = 9;
const int DET = 10;
const int OPT = 11;
const int ENT = 12;

//Doctor class
class Doctor
{
private:

	//Variables
	string name; //to hold doctor's name
	int room; //to hold doctor's preferred room number
	int code; //to hold doctor's specialty code

public:

	//Constructor
	Doctor()
	{
		name = "";
		room = -1;
		code = -1;
	}

	//Mutators

	//SET NAME
	void setName(string docName) //sets doctor's name
	{
		name = docName;
	}

	//SET ROOM
	void setRoom(int docRoom) //sets doctor's room #
	{
		room = docRoom;
	}

	//SET CODE
	void setCode(int docCode) //sets doctor's code
	{
		code = docCode;
	}

	//Accessors

	//GET NAME
	string getName() //returns doctor's name
	{
		return name;
	}

	//GET ROOM
	int getRoom() //returns doctor's room number
	{
		return room;
	}

	//GET CODE
	int getCode() //returns doctor's specialty code
	{
		return code;
	}

};


#endif /* Doctor_h */
