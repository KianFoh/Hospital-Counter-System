#include <iostream>
#include <string>
#include "Queue.h"

using namespace std;

// Constructor
Queue::Queue(){
	front = rear = NULL;
	numItems = 0;
}

// Destruction
Queue::~Queue(){
	clear();
}

// Check empty queue
bool Queue::isEmpty() const{
	return (numItems==0);
}

void Queue::enQueue(Patient new_data){
	Node *newNode = new Node();
	newNode->data = new_data;
	newNode->next = NULL;
	
	// Case1:list is empty
	if(isEmpty()){
		front = newNode;
		rear = newNode;
	}
	
	// Case2: List has value
	else{
		rear->next = newNode;
		rear = newNode;
	}
	
	// Increase numItems
	numItems++;
}

void Queue::enQueue_Sequence(Patient new_data){
	Node *current = front;
	Node *previous = front;
	int counter = new_data.getCounter();
	Node *newNode = new Node();
	newNode->data = new_data;
	newNode->next = NULL;
	
	
	// Case1:list is empty
	if(isEmpty()){
		front = newNode;
		rear = newNode;
	}
	
	else{
		// Insert as first item
		if(counter < front->data.getCounter()){
			newNode->next = front;
			rear = front = newNode;
		}
		else{
			while(current->next != NULL && !counter < current->data.getCounter()){
				previous = current;
				current = current->next;
			}
			
			// Insert in between front and rear
			if(current->next==NULL){
				rear->next = newNode;
				rear = rear->next;
			}
			// Insert in rear
			else{
				previous->next = newNode;
				newNode->next = rear;
				
			}
		}
		
	}
	numItems++;
}

void Queue::deQueue(Patient &data){
	Queue *temp;
	
	if(isEmpty()){
		cout << "The queue is empty!" << endl;
	}
	else{
		Node *temp = front;
		data = front->data;
		front = front->next;
		delete temp;
		numItems--;
	}
}

void Queue::deQueue_by_counter(int counter, Patient &data){
	Node *current = front;
	Node *temp = new Node();
	
	// Case 1 Queue is Empty
	if(isEmpty())
		cout << "The queue is empty!" << endl;
	else{
		// Case 2 first item is the target
		if(front->data.getCounter()==counter){
			temp = front;
			data = front->data;
			front = front->next;
			delete temp;
			numItems--;
		}
		else{
			while(current->next != NULL && current->next->data.getCounter()!=counter){
				current = current->next;
			}
			if(current->next == NULL)
				cout << "Patient with Counter number " << counter <<" is not found.\n";
			else{
				
				// Case 5 the last Node is the target
				if(current->next == rear){
					temp = rear;
					data = rear->data;
					current->next = NULL;
					rear = current;
				}
				// Case 6 the target is not the front or rear
				else{
					temp = current->next;
					data = current->next->data;
					current->next = current->next->next;
				}
				delete temp;
				numItems--;
			}
		}
	}
}

void Queue::clear(){
	Patient value;
	while(!isEmpty()){
		deQueue(value);
	}
}

int Queue::get_NumItems(){
	return numItems;
}

// Print all patient in the queue in a format
void Queue::print() const{
	string info = "";
	string bar = "";
	string arrow = "";
	string spacing = "";
	
	Node *current = front;
	while(current != NULL){
		info = "| [" + to_string(current->data.getCounter()) + "] " + current->data.getTime() + ", "
		+ current->data.getName() + ", (" + current->data.getGender() + "), " + to_string(current->data.getAge()) + " |";
		bar = "+";
		for(int i = 0; i < (info.size()-2); i++)
			bar += "-";
		bar += "+";	
		
		spacing = "";
		for(int i = 0; i < (info.size()/2); i++)
			spacing += " ";
		arrow = spacing + "|" + "\n";
		spacing.pop_back();
		arrow = arrow + spacing + "\\" + " /\n";
		cout << bar << endl;
		cout << info << endl;
		cout << bar << endl;
		if(current->next!= NULL)
			cout << arrow;
		current = current->next;
	}
}


