#ifndef INTQUEUE_H
#define INTQUEUE_H

class IntQueue
{
private:
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	int *queueArray;
	IntQueue(int);  //constructor, parameter is capacity
  	void enqueue(int); 
  	void dequeue(int &);
  	bool isEmpty() const; 
  	bool isFull() const;
  	void clear();  //removes all elements
};
#endif