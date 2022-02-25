#include <string>
#include <iostream>
#include "Queue.h"
#include "Doctor.h"
#include "Patient.h"
#include "ExamRoom.h"
using namespace std;

// Setters

//SET DOCTOR
void ExamRoom::setDoctor(Doctor newDoctor) //sets room doctor
{
	roomDoctor = newDoctor;
}

//SET PATIENT
void ExamRoom::setPatient(Patient newPatient) //sets room patient
{
	roomPatient = newPatient;
}

// Getters

//HAS DOCTOR
bool ExamRoom::hasDoctor()
{
	//returns false if room doctor's name is empty string
	if (roomDoctor.getName() == "")
		return false;

	//otherwise returns true
	else
		return true;
}

//HAS PATIENT
bool ExamRoom::hasPatient()
{
	//returns false if room patient's name is empty string
	if (roomPatient.getName() == "")
		return false;

	//otherwise returns false
	else
		return true;
}

//GET DOCTOR
Doctor ExamRoom::getDoctor()
{
	//returns room doctor if has doctor returns true
	if (hasDoctor())
		return roomDoctor;

	//otherwise throws exception class NoDoctor
	else
		throw NoDoctor();
}

//GET PATIENT
Patient ExamRoom::getPatient()
{
	//returns room doctor if has doctor returns true
	if (hasPatient())
		return roomPatient;

	//otherwise throws exception class NoPatient
	else
		throw NoPatient();
}

//GET ROOM NUMBER
int ExamRoom::getRoomNumber()
{
	//gets the doctor's room if there is one
	if (hasDoctor())
		return roomDoctor.getRoom();

	//otherwise returns -1 (invalid room)
	else
		return -1;
}

//GET CODE
int ExamRoom::getCode()
{
	//returns doctor's specialty code if there's a doctor
	if (hasDoctor())
		return roomDoctor.getCode();

	//otherwise returns -1 (invalid code)
	else
		return -1;
}

//GET WAIT
int ExamRoom::getWait()
{
	//returns # of patients in waiting room
	return waitingRoom.getLength();
}

//ADD TO WAIT
void ExamRoom::addToWait(Patient& waitingPatient)
{
	//adds patient to end of waiting room queue
	waitingRoom.enqueue(waitingPatient);
}

//GET NEXT PATIENT
void ExamRoom::getNextPatient()
{
	Patient nextPatient; //blank patient to be modified

	//nextPatient info becomes the patient at the front of waiting list
	waitingRoom.dequeue(nextPatient);

	//sets room patient with next patient's info
	roomPatient = nextPatient;
}

//VACATE ROOM
void ExamRoom::vacateRoom()
{
	//creates blank patient and doctor to replace current
	//room patient and room doctor
	Patient defaultPatient;
	Doctor defaultDoctor;

	roomPatient = defaultPatient;
	roomDoctor = defaultDoctor;
}