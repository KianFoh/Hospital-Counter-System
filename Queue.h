#ifndef _QUEUE_
#define _QUEUE_
#include "Patient.h"

class Queue{
	private:
		struct Node{
			Patient data;
      		Node *next;
		};
		Node *front;
		Node *rear;
		int numItems;
	public:
		Queue();
		~Queue();
		void enQueue(Patient); // Enter to the queue
		void enQueue_Sequence(Patient); // Enter to the following counter sequence
		void deQueue(Patient &); // Delete from the queue
		void deQueue_by_counter(int, Patient &); // Delete from the queue by counter
		bool isEmpty() const;
		void clear(); // Clear all the queue items
		int get_NumItems();
		void print() const; // Print out the queue
};

#endif
