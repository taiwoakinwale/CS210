#include <iostream>
#include <fstream>
#include <string>
#include "ExamRoom.h"
#include "Doctor.h"
#include "Patient.h"
using namespace std;


//Enumerated Operation used for switch menu readability
enum Operation { DOCTOR_IN, DOCTOR_OUT, PATIENT_IN, PATIENT_OUT };

//number of rooms in Clinic
const int NUM_CLINIC_ROOMS = 100;

//for printing input and output
fstream outFile;

//Array of exam rooms for all functions to use
ExamRoom rooms[NUM_CLINIC_ROOMS];


// 1. DISPLAY MENU
void displayMenu(Operation&);

// 2. DISPLAY CODES
void displayCodes();

// 3. ASSIGN DOCTOR
bool assign(Doctor&);

// 4. ASSIGN PATIENT
bool assign(Patient&, int);

// 5. ASSIGN PATIENT BEST FIT
void assignBestFit(Patient&);

// 6. DOCTOR CHECK-IN
void doctorCheckIn();

// 7. DOCTOR CHECK-OUT
void doctorCheckOut();

// 8. PATIENT CHECK-IN
void patientCheckIn();

// 9. PATIENT CHECK-OUT
void patientCheckOut();

// 10. GOODBYE
void goodbye();

// 11. ANOTHER USER?
bool anotherUser();

// 12. ASSIGN GENERATED DOCTOR
void assignGenerated(Doctor&);

// 13. GENERATE CLINIC
void generateClinic();


int main()
{
	outFile.open("trans.out"); //opens "trans.out" for output
	Operation choice; //to hold user's choice

	//for Generate Clinic function
	unsigned seed = time(0);
	srand(seed);

	//Uncomment next line to start program with doctors and patients in the clinic
	//generateClinic();

	do
	{
		displayMenu(choice);

		switch (choice)
		{

		case DOCTOR_IN:
			doctorCheckIn();
			break;

		case DOCTOR_OUT:
			doctorCheckOut();
			break;

		case PATIENT_IN:
			patientCheckIn();
			break;

		case PATIENT_OUT:
			patientCheckOut();
			break;
		}
	} while (anotherUser());

	goodbye();

	return 0;
}

//Displays the menu screen to the console and specified output file


void displayMenu(Operation& choice)
{

	//Local Variables
	bool running = true; //used for loop control

	string input1, //to hold first user input
		input2, //to hold second user input
		input3; //to hold third user input

	cout << endl << "Welcome to the Medical Clinic Scheduling Service" << endl << endl;
	outFile << endl << "Welcome to the Medical Clinic Scheduling Service" << endl << endl;

	//Doctor or patient?
	while (running)
	{
		cout << "Type 'D' for Doctor or 'P' for Patient: ";
		outFile << "Type 'D' for Doctor or 'P' for Patient: ";

		getline(cin, input1);
		outFile << input1 << endl;

		//sets input equal to its first element and makes it uppercase
		input1 = toupper(input1[0]);

		//checks the validity of "input"
		if (input1 == "D" || input1 == "P")
			running = false;

		else
		{
			cout << endl << "Invalid input." << endl;
			outFile << endl << "Invalid input." << endl;
		}
	}

	running = true; //set running to true for next check

	//In or out?
	while (running)
	{
		cout << "Type 'I' for check-in or 'O' for checkout: ";
		outFile << "Type 'I' for check-in or 'O' for checkout: ";

		getline(cin, input2);

		input2 = toupper(input2[0]);
		outFile << input2 << endl;

		if (input2 == "I" || input2 == "O")
			running = false;

		else
		{
			cout << endl << "Invalid input." << endl;
			outFile << endl << "Invalid input." << endl;
		}
	}

	//choice set appropriately
	if (input1 == "D" && input2 == "I")
		choice = DOCTOR_IN;
	else if (input1 == "D" && input2 == "O")
		choice = DOCTOR_OUT;
	else if (input1 == "P" && input2 == "I")
		choice = PATIENT_IN;
	else
		choice = PATIENT_OUT;
}

//Displays list of codes to console and output file


void displayCodes()
{
	cout << endl
		<< "1. PED - Pediatrics" << endl
		<< "2. GEN - General practice" << endl
		<< "3. INT - Internal medicine" << endl
		<< "4. CAR - Cardiology" << endl
		<< "5. SUR - Surgeon" << endl
		<< "6. OBS - Obstetrics" << endl
		<< "7. PSY - Psychiatry" << endl
		<< "8. NEU - Neurology" << endl
		<< "9. ORT - Orthopedics" << endl
		<< "10. DET - Dermatology" << endl
		<< "11. OPT - Ophthalmology" << endl
		<< "12. ENT - Ear, Nose, and Throat" << endl << endl;

		outFile << endl
		<< "1. PED - Pediatrics" << endl
		<< "2. GEN - General practice" << endl
		<< "3. INT - Internal medicine" << endl
		<< "4. CAR - Cardiology" << endl
		<< "5. SUR - Surgeon" << endl
		<< "6. OBS - Obstetrics" << endl
		<< "7. PSY - Psychiatry" << endl
		<< "8. NEU - Neurology" << endl
		<< "9. ORT - Orthopedics" << endl
		<< "10. DET - Dermatology" << endl
		<< "11. OPT - Ophthalmology" << endl
		<< "12. ENT - Ear, Nose, and Throat" << endl << endl;
}


//Assigns doctor to preferred room if available


bool assign(Doctor& newDoctor)
{
	bool assigned = false; //value to return
	int preferred = newDoctor.getRoom(); //to hold preferred room number
	Doctor roomDoctor; //to hold the doctor in specified room


	for (int i = 0; i < NUM_CLINIC_ROOMS; i++)
	{
		if (rooms[i].hasDoctor())
		{
			roomDoctor = rooms[i].getDoctor();

			if (roomDoctor.getName() == newDoctor.getName())
			{
				cout << endl << "There is already a Doctor " << roomDoctor.getName()
					<< " in the clinic." << endl;
				outFile << endl << "There is already a Doctor " << roomDoctor.getName()
					<< " in the clinic." << endl;

				assigned = false; //doctor was not assigned
				return assigned; //returns false
			}
		}
	}


	if (rooms[preferred].hasDoctor())
	{
		roomDoctor = rooms[preferred].getDoctor();

		cout << endl << "Doctor " << roomDoctor.getName() << " is using room #"
			<< preferred + 1 << ". Please try to check-in another time." << endl;
		outFile << endl << "Doctor " << roomDoctor.getName() << " is using room #"
			<< preferred + 1 << ". Please try to check-in another time." << endl;

		assigned = false; //doctor was not assigned
		return assigned; //returns false
	}

	//if the room is open and no other doctors share the same name, request is granted
	//returns true
	else
	{
		rooms[preferred].setDoctor(newDoctor); //assigns doctor to requested room
		assigned = true;

		cout << endl << "Doctor " << newDoctor.getName() << " has been assigned to room #"
			<< preferred + 1 << "." << endl;
		outFile << endl << "Doctor " << newDoctor.getName() << " has been assigned to room #"
			<< preferred + 1 << "." << endl;

		return assigned; //returns true
	}
}

//FUNCTION ASSIGN PATIENT


bool assign(Patient& newPatient, int code)
{
	bool assignStatus = false;
	Doctor roomDoctor;

	try
	{
		ExamRoom* busyDocs[NUM_CLINIC_ROOMS];
		int numBusyDocs = 0;

		for (int i = 0; i < NUM_CLINIC_ROOMS; i++)
		{

			if (rooms[i].getCode() == code && !rooms[i].hasPatient())
			{
				roomDoctor = rooms[i].getDoctor();
				rooms[i].setPatient(newPatient);

				assignStatus = true;

				cout << endl << "Patient " << newPatient.getName() <<
					" has been assigned to room #" << i + 1
					<< " with Doctor " << roomDoctor.getName() << "." << endl;
				outFile << endl << "Patient " << newPatient.getName() <<
					" has been assigned to room #" << i + 1
					<< " with Doctor " << roomDoctor.getName() << "." << endl;

				return assignStatus;
			}

			else if (rooms[i].getCode() == code && rooms[i].hasPatient())
			{
				busyDocs[numBusyDocs] = &rooms[i];
				numBusyDocs++;
			}
		}

		if (numBusyDocs == 0)
		{
			assignStatus = false;
			return assignStatus;
		}

		int leastCrowded = busyDocs[0]->getWait();
		ExamRoom* assignment = busyDocs[0];

		for (int i = 1; i < numBusyDocs; i++)
		{
			if (busyDocs[i]->getWait() < leastCrowded)
			{
				leastCrowded = busyDocs[i]->getWait();
				assignment = busyDocs[i];
			}
		}

		roomDoctor = assignment->getDoctor();
		assignment->addToWait(newPatient);

		assignStatus = true;

		cout << endl << "Patient " << newPatient.getName() <<
			" has been assigned to room #" << assignment->getRoomNumber() + 1
			<< " with Doctor " << roomDoctor.getName() << "." << endl;
		outFile << endl << "Patient " << newPatient.getName() <<
			" has been assigned to room #" << assignment->getRoomNumber() + 1
			<< " with Doctor " << roomDoctor.getName() << "." << endl;

		return assignStatus;
	}

	catch (ExamRoom::NoDoctor)
	{
		cout << "There's no doctor in this room!";
		outFile << "There's no doctor in this room!";
	}

	return assignStatus;
}


//FUNCTION ASSIGN PATIENT BEST FIT


void assignBestFit(Patient& newPatient)
{
	int code = newPatient.getCode(); //sets code to patient's code
	bool assigned = false; //to determine whether assignment worked or not

	//tries to assign patient according to patient's specialty code
	//if succeeds, function ends
	assigned = assign(newPatient, code);

	//if the patient is a child and not assigned, there's no pediatricians
	if (!assigned && code == PED)
	{
		cout << endl << "Sorry, there's no pediatricians in the clinic right now." << endl
			<< "Please try to check-in another time." << endl;
		outFile << endl << "Sorry, there's no pediatricians in the clinic right now." << endl
			<< "Please try to check-in another time." << endl;
	}

	//if patient is not a child, tries to assign patient to a GP
	if (!assigned && code != PED)
	{
		assigned = assign(newPatient, GEN);

		//if a GP is found, patient is assigned and displays message
		if (assigned)
		{
			cout << "There is currently no doctor of the requested specialty in the clinic."
				<< endl << "However, there is a General Practitioner available." << endl;
			outFile << "There is currently no doctor of the requested specialty in the clinic."
				<< endl << "However, there is a General Practitioner available." << endl;
		}
	}


	if (!assigned && code != PED)
	{
		for (code = INT; !assigned && code <= ENT; code++)
		{
			assigned = assign(newPatient, code);

			//displays message if patient is assigned
			if (assigned)
			{
				cout << "There is currently no doctor of the requested specialty in the clinic."
					<< endl << "However, there is another doctor available." << endl;
				outFile << "There is currently no doctor of the requested specialty in the clinic."
					<< endl << "However, there is another doctor available." << endl;
				break;
			}
		}

		//if the patient's still not assigned, there are no doctors in the clinic
		//message is displayed
		if (!assigned)
		{
			cout << endl << "There are no doctors for adults in the clinic." << endl
				<< "Please come back another time." << endl;
			outFile << endl << "There are no doctors for adults in the clinic." << endl
				<< "Please come back another time." << endl;
		}
	}
}

// FUNCTION DOCTOR CHECK-IN


void doctorCheckIn()
{
	bool running = true; //for loop control
	string name; //to hold doctor's name
	int room = -1; //to hold doctor's preferred room number
	int code = -1; //to hold doctor's specialty code
	Doctor newDoctor; //to hold a doctor's information

	cout << endl << "***DOCTOR CHECK-IN***" << endl << endl;
	outFile << endl << "***DOCTOR CHECK-IN***" << endl << endl;

	//prompts for name
	cout << "Name: ";
	outFile << "Name: ";

	//gets user input name
	getline(cin, name);
	outFile << name << endl;

	while (running)
	{
		//prompts for room number
		cout << "Preferred Room Number (1-100): ";
		outFile << "Preferred Room Number (1-100): ";

		//gets user input room number
		cin >> room;
		outFile << room << endl;

		//validates room number
		//if between 1 and 100, loop breaks
		if (room >= 1 && room <= 100)
			running = false;

		//error message if invalid room number
		//loops running
		else
		{
			cout << endl << "Invalid number." << endl;
			outFile << endl << "Invalid number." << endl;
		}
	}


	room--; //decrement room number for proper indexing

	running = true; //reset running for specialty loop

	displayCodes(); //displays specialty codes

	while (running)
	{
		//prompts for specialty code
		cout << "Specialty Code Number (1-12): ";
		outFile << "Specialty Code Number (1-12): ";

		//gets user input code number
		cin >> code;
		outFile << code << endl;

		cin.ignore();

		//validates code number
		//loop ends if code between 1 and 12
		if (code >= 1 && code <= 12)
			running = false;

		//if number is invalid, error message
		//loops running
		else
		{
			cout << endl << "Invalid number." << endl;
			outFile << endl << "Invalid number." << endl;
		}
	}

	//sets doctor's information appropriately
	newDoctor.setName(name);
	newDoctor.setRoom(room);
	newDoctor.setCode(code);

	//assigns the new doctor appropriately
	assign(newDoctor);

}

//FUNCTION DOCTOR CHECK-OUT


void doctorCheckOut()
{
	bool found = false; //to indicate if the given name is found in an exam room
	string name; //to hold user input name
	int room = 0; //to hold a room number
	int numDocs = 0; //to hold number of doctors in clinic
	int numPats = 0; // to hold number of patients in exam rooms
	int numPeds = 0; // to hold number of pediatricians in clinic
	int numKids = 0; //to hold number of kids in exam rooms (age < 16)
	Doctor localDoctor; //to hold a doctor's information
	Patient localPatient; //to hold a patients information
	ExamRoom* localRoom = nullptr; //to hold an exam room's address

	cout << endl << "***DOCTOR CHECK-OUT***" << endl << endl;
	outFile << endl << "***DOCTOR CHECK-OUT***" << endl << endl;

	//prompts user to enter name
	cout << "Name: ";
	outFile << "Name: ";

	//gets user input name
	getline(cin, name);
	outFile << name << endl;

	//searches each room in the clinic for the given name
	//keeps track of number of doctors, patients, pediatricians, and kids
	for (int i = 0; i < NUM_CLINIC_ROOMS; i++)
	{
		//if the exam room is occupied, increment numDocs
		if (rooms[i].hasDoctor())
		{
			numDocs++;

			//if there's a patient in the room, increment numPats
			if (rooms[i].hasPatient())
				numPats++;

			//if the code is PED, increment numPeds
			if (rooms[i].getCode() == PED)
			{
				numPeds++;

				//if a PED room has a patient, increment numKids
				if (rooms[i].hasPatient())
					numKids++;
			}

			//sets localDoctor to doctor in current room
			localDoctor = rooms[i].getDoctor();


			if (localDoctor.getName() == name)
			{
				localRoom = &rooms[i];
				room = i + 1;
				found = true;
			}
		}
	}

	//if no doctors in the clinic, displays message
	if (numDocs == 0)
	{
		cout << endl << "There are no doctors in the clinic." << endl;
		outFile << endl << "There are no doctors in the clinic." << endl;
	}

	else
	{
		//if doctors but no matching name, displays message
		if (!found)
		{
			cout << endl << "There is no doctor in the clinic named " << name << "." << endl;
			outFile << endl << "There is no doctor in the clinic named " << name << "." << endl;
		}

		//if name is found, displays an appropriate message
		else
		{
			cout << endl;
			outFile << endl;

			int numAdultDocs = numDocs - numPeds; //finds # of doctors that aren't pediatricians
			int numAdultPats = numPats - numKids; //finds # of patients >= 16 years old

			if (numDocs == 1 && numPats > 0)
			{
				cout << "You're the only doctor in the clinic! You can't check out until all the "
					<< "patients have been seen or another qualifying doctor arrives." << endl;
				outFile << "You're the only doctor in the clinic! You can't check out until all the "
					<< "patients have been seen or another qualifying doctor arrives." << endl;
			}

			else if (numAdultDocs == 1 && numAdultPats > 0 && localRoom->getCode() != PED)
			{
				cout << "You're the only doctor for adults in the clinic! You can't check out until all the "
					<< "adult patients have been seen or another qualifying doctor arrives." << endl;
				outFile << "You're the only doctor for adults in the clinic! You can't check out until all the "
					<< "adult patients have been seen or another qualifying doctor arrives." << endl;
			}

			else if (numPeds == 1 && numKids > 0 && localRoom->getCode() == PED)
			{
				cout << "You're the last pediatrician in the clinic! You can't check out until all the "
					<< "children have been seen or another pediatrician arrives." << endl;
				outFile << "You're the last pediatrician in the clinic! You can't check out until all the "
					<< "children have been seen or another pediatrician arrives." << endl;
			}

			//if doctor is able to check-out, displays check-out message
			else
			{
				try
				{
					localPatient = localRoom->getPatient();

					//room doctor and room patient are reset to default
					localRoom->vacateRoom();

					cout << "Patient " << localPatient.getName() << " has been seen by Doctor "
						<< name << " and checked out of room #" << room << "." << endl;
					outFile << "Patient " << localPatient.getName() << " has been seen by Doctor "
						<< name << " and checked out of room #" << room << "." << endl;

					//if doctor has a wait, displays appropriate message
					if (localRoom->getWait() > 0)
					{
						cout << "Reassigning patients in " << name << "'s waiting room..."
							<< endl;
						outFile << "Reassigning patients in " << name << "'s waiting room..."
							<< endl;
					}

					//reassigns waiting room patients appropriately
					while (localRoom->getWait() >= 0)
					{
						//sets exam room's patient to next patient in waiting room queue
						localRoom->getNextPatient();

						//reassigns each patient according to code
						localPatient = localRoom->getPatient();
						assignBestFit(localPatient);
					}

				}

				//when no patients remain, doctor checks out
				catch (ExamRoom::NoPatient)
				{
					cout << endl << "Doctor " << name << " has checked out of room #"
						<< room << "." << endl;
					outFile << endl << "Doctor " << name << " has checked out of room #"
						<< room << "." << endl;
				}

				//Resets room to default to clear last patient from room
				localRoom->vacateRoom();
			}
		}
	}
}

//FUNCTION PATIENT CHECK-IN


void patientCheckIn()
{
	bool running = true; //for loop control
	string name; //to hold patient's name
	int age = -1; //to hold patient's age
	int code = -1; //to hold patient's code
	Patient newPatient; //to hold new patient's information
	int numDocs = 0; //to hold number of doctors in clinic

	//looks for doctors and pediatricians in the clinic
	for (int i = 0; i < NUM_CLINIC_ROOMS; i++)
	{
		if (rooms[i].hasDoctor())
		{
			//increments numDocs if room has a doctor
			numDocs++;

		}

		//stops searching if a doctor is found
		if (numDocs > 0)
			break;
	}

	//if no doctors are found, displays message
	if (numDocs == 0)
	{
		cout << endl << "Sorry, there are no doctors in the clinic right now." << endl
			<< "Please come back another time." << endl;
		outFile << endl << "Sorry, there are no doctors in the clinic right now." << endl
			<< "Please come back another time." << endl;
	}

	//otherwise allows patient to check in
	else
	{
		cout << endl << "***PATIENT CHECK-IN***" << endl << endl;
		outFile << endl << "***PATIENT CHECK-IN***" << endl << endl;

		//prompts for patient name
		cout << "Name: ";
		outFile << "Name: ";

		//gets user input name
		getline(cin, name);
		outFile << name << endl;

		//prompts for age, gets age and verifies age is between 1 and 200
		while (running)
		{
			cout << "Age: ";
			outFile << "Age: ";

			cin >> age;
			outFile << age << endl;

			cin.ignore();

			//assumes no patient under age 1 or over 200
			if (age >= 1 && age <= 200)
				running = false;

			//error message if age not between 1 and 200
			//loop continues
			else
			{
				cout << endl << "Invalid number." << endl;
				outFile << endl << "Invalid number." << endl;
			}
		}

		running = true; //running reset to true for specialty code loop


		if (age >= 16)
		{
			//displays specialty codes
			displayCodes();

			while (running)
			{
				//prompts for specialty code
				cout << "Specialty Code Number: ";
				outFile << "Specialty Code Number: ";

				//gets user input code number
				cin >> code;
				outFile << code << endl;

				cin.ignore();

				//validates code
				//if appropriate breaks loop
				if (code >= 2 && code <= 12)
					running = false;

				//error message
				//loop continues
				else
				{
					cout << endl << "Invalid number." << endl;
					outFile << endl << "Invalid number." << endl;
				}
			}
		}

		//sets patient information accordingly
		newPatient.setName(name);
		newPatient.setAge(age);
		newPatient.setCode(code);

		//assigns patient to best fit
		assignBestFit(newPatient);
	}
}

//FUNCTION PATIENT CHECK-OUT


void patientCheckOut()
{
	bool found = false; //to determine if name was found or not
	string name; //to hold patient's name
	int room; //to hold a room number
	Doctor localDoctor; //to hold a doctor object
	Patient localPatient; //to hold a patient object
	ExamRoom* localRoom = nullptr; //exam room pointer to hold address of an exam room

	cout << endl << "***PATIENT CHECK-OUT***" << endl << endl;
	outFile << endl << "***PATIENT CHECK-OUT***" << endl << endl;

	//prompts for name
	cout << "Name: ";
	outFile << "Name: ";

	//gets user input name
	getline(cin, name);
	outFile << name << endl;

	//looks through each exam room for patient
	for (int i = 0; i < NUM_CLINIC_ROOMS; i++)
	{
		if (rooms[i].hasPatient())
		{
			localRoom = &rooms[i];
			localPatient = localRoom->getPatient();


			if (localPatient.getName() == name)
			{
				found = true;
				break;
			}
		}
	}

	//if the patient's not found in an exam room, displays message
	if (!found)
	{
		cout << endl << "Patient " << name
			<< " is either waiting for a doctor or not in the clinic." << endl;
		outFile << endl << "Patient " << name
			<< " is either waiting for a doctor or not in the clinic." << endl;
	}

	else
	{ //sets local doctor to local room's doctor
		localDoctor = localRoom->getDoctor();

		//room number set and formatted for output
		room = localRoom->getRoomNumber() + 1;

		//patient check-out message
		cout << endl << "Patient " << name << " has checked out of room #"
			<< room << "." << endl;
		outFile << endl << "Patient " << name << " has checked out of room #"
			<< room << "." << endl;

		name = localDoctor.getName(); //sets name to local doctor

		//if the waiting room isn't empty, puts next patient in the exam room
		if (localRoom->getWait() > 0)
		{
			localRoom->getNextPatient();
			localPatient = localRoom->getPatient();

			cout << "Doctor " << name << " is now seeing " << localPatient.getName()
				<< " in room #" << room << "." << endl;
			outFile << "Doctor " << name << " is now seeing " << localPatient.getName()
				<< " in room #" << room << "." << endl;
		}
		else //if no one is waiting, room patient becomes blank patient
		{
			Patient defaultPatient;
			localRoom->setPatient(defaultPatient);

			cout << "Doctor " << name << " in room #" << room << " has no more patients."
				<< endl;
			outFile << "Doctor " << name << " in room #" << room << " has no more patients."
				<< endl;
		}
	}
}


//FUNCTION GOODBYE


void goodbye()
{
	cout << endl << "Thank you for using the Medical Clinic Scheduling Service." << endl
		<< "Have a wonderful day!" << endl;
	outFile << endl << "Thank you for using the Medical Clinic Scheduling Service." << endl
		<< "Have a wonderful day!" << endl;

	outFile.close();
}

//FUNCTION ANOTHER USER?


bool anotherUser()
{
	bool running = true; //for loop control
	string input; //to hold user input

	while (running)
	{
		//user prompt
		cout << endl << "Type 'Y' if there's another user or 'N' to exit: ";
		outFile << endl << "Type 'Y' if there's another user 'N' to exit: ";

		//gets user input
		getline(cin, input);
		outFile << input << endl;

		//sets input's first letter to uppercase
		//sets input to first letter
		input = toupper(input[0]);

		//validates input, breaks out of loop
		if (input == "Y" || input == "N")
			running = false;

		//invalid input error message
		else
		{
			cout << endl << "Invalid input." << endl;
			outFile << endl << "Invalid input." << endl;
		}
	}

	//if Y, returns true
	if (input == "Y")
		return true;

	//if N, returns false
	else
		return false;
}

//FUNCTION ASSIGN GENERATED DOCTOR


void assignGenerated(Doctor& newDoctor)
{
	int preferred = newDoctor.getRoom();

	try
	{
		Doctor roomDoctor = rooms[preferred].getDoctor();
	}
	catch (ExamRoom::NoDoctor)
	{
		rooms[preferred].setDoctor(newDoctor);
	}
}

//FUNCTION GENERATE CLINIC


void GenerateClinic()
{
	const int NUM_DOCS = 100;
	const int NUM_PATS = 500; // max of 100 patients

	Doctor testDoc[NUM_DOCS]; //array of doctors of number NUM_DOCS
	Patient testPat[NUM_PATS]; //array of patients of number NUM_PATS


	for (int i = 0; i < NUM_DOCS; i++)
	{
		int room = i;

		int code = (rand() % 12) + 1; //random specialty code

		//Doctor name becomes "doctor (index + 1)"
		string number = to_string(i + 1);
		string name = "doctor ";
		name.append(number);

		//sets doctor and assigns appropriately
		testDoc[i].setName(name);
		testDoc[i].setRoom(room);
		testDoc[i].setCode(code);

		assignGenerated(testDoc[i]);
	}


	for (int i = 0; i < NUM_PATS; i++)
	{
		//sets age
		int age = (rand() % 100) + 1;
		int code = 0;

		//sets code if at least 16
		if (age >= 16)
			code = (rand() % 11) + 2;

		//sets name
		string number = to_string(i + 1);
		string name = "patient ";
		name.append(number);

		//sets patient and assigns appropriately
		testPat[i].setName(name);
		testPat[i].setAge(age);
		testPat[i].setCode(code);

		assignBestFit(testPat[i]); //calls assign best fit for each patient
	}

	//Displays information for each occupied room
	for (int i = 0; i < NUM_DOCS; i++)
	{
		Doctor roomDoctor = rooms[i].getDoctor();
		Patient roomPatient;

		if (rooms[i].hasPatient())
			roomPatient = rooms[i].getPatient();

		cout << "Room #: " << rooms[i].getRoomNumber() + 1 << endl;
		cout << "Code #: " << rooms[i].getCode() << endl;
		cout << "Doctor name: " << roomDoctor.getName() << endl;
		if (rooms[i].hasPatient())
		{
			cout << "Patient name: " << roomPatient.getName() << endl;
			cout << "Patient age: " << roomPatient.getAge() << endl;
			cout << "Patient code: " << roomPatient.getCode() << endl;
			cout << "# waiting: " << rooms[i].getWait() << endl;
		}
		cout << endl;
	}

	//displays number of doctors and patients generated
	cout << "# Doctors: " << NUM_DOCS << endl;
	cout << "# Patients: " << NUM_PATS << " (some patients may be unassigned)" << endl;
}