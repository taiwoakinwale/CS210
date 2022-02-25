#include "Queue.h"
#include <string>
#include "Doctor.h"
#include "Patient.h"
#ifndef ExamRoom_HEADER
#define ExamRoom_HEADER

using namespace std;

class ExamRoom
{
private:
	Doctor roomDoctor; //to hold the doctor in the exam room
	Patient roomPatient; //to hold the patient in the exam
	Queue waitingRoom; //to attach waiting room to exam room

public:
	//Exception classes
	class NoDoctor{};

	class NoPatient{};

	//Constructor
	ExamRoom(){};

	//setters
	void setDoctor(Doctor newDoctor); //sets room doctor
	
	void setPatient(Patient newPatient); //sets room patient


	//getters
	bool hasDoctor(); //true if there's a doctor, else false
	
	bool hasPatient(); //true if there's a patient, else false
	
	Doctor getDoctor(); //returns room doctor
	
	Patient getPatient(); //returns room patient
	
	int getRoomNumber(); //returns room number
	
	int getCode(); //returns current room code
	
	int getWait(); //returns length of waiting room
	
	void addToWait(Patient& waitingPatient); //adds patient to waiting room queue
	
	void getNextPatient(); //room patient set to next patient in waiting room queue
	
	void vacateRoom(); //room doctor and patient are set to default
};

#endif