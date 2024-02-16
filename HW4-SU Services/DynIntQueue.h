#ifndef DYNINTQUEUE_H
#define DYNINTQUEUE_H

struct QueueNode
{
	int value;
	QueueNode *next;
	QueueNode(int num, QueueNode *ptr = NULL)
	{
		value = num;
		next = ptr;
	}
};

class DynIntQueue
{
private:
	// These track the front and rear of the queue.
	QueueNode *front;
	QueueNode *rear;	
public:
	// Constructor.
	DynIntQueue();
	
	// Member functions.
	void enqueue(int);
	void dequeue(int &);
	bool isEmpty() const;     
	void clear();
};
#endif