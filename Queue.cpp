#include <iostream>
#include <string>
#include "Queue.h"
#include "Patient.h"




using namespace std;

//Constructor
Queue::Queue()
{
	//front and rear point to nothing
	//length set to 0
	front = nullptr;
	rear = nullptr;
	length = 0;
}

//Destructor
Queue::~Queue()
{
	//calls clear function
	clear();
}

//Enqueue
void Queue::enqueue(Patient& newPatient)
{
	//to hold a new patient object
	Node* newNode = nullptr;

	//creates new node and stores patient data
	newNode = new Node;
	newNode->data = newPatient;
	newNode->next = nullptr;

	if (isEmpty()) //if no patients in queue
	{
		//front and rear point to the new node
		front = newNode;
		rear = newNode;
	}

	else
	{
		//otherwise adds newNode to the end of the queue
		rear->next = newNode;
		rear = newNode;
	}

	//increment length
	length++;
}

//Dequeue
void Queue::dequeue(Patient& nextPatient)
{
	Node* temp = nullptr;

	if (!isEmpty())
	{
		//next patient data set to data in front node
		nextPatient = front->data;

		//front node deleted
		//front is set to the next node in queue
		temp = front;
		front = front->next;
		delete temp;

		//decrement length
		length--;
	}

	//if queue is empty, rear set to null
	if (isEmpty())
		rear = nullptr;

}

//Is Empty
bool Queue::isEmpty() const
{
	bool status; //to hold bool value to return

	if (length > 0) //if someone is in queue, function returns false
		status = false;

	else //if no one in queue, function returns true
		status = true;

	return status;
}

//Get Length
int Queue::getLength() const //returns length
{
	return length;
}

//Clear
void Queue::clear() //dequeues all patients in queue
{
	Patient somePatient;

	while (!isEmpty())
		dequeue(somePatient);
}