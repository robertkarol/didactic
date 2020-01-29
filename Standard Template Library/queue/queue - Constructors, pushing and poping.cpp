#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <list>

using namespace std;

void queue_iterating()
{
	cout << "You just don't!!!\n"; // You can't iterate with a for: you must remove front element to get access to the second and so on

	vector<int> myData(5, 10);
	queue<int, vector<int>> myDataQueue(myData);

	// Uncomment the code below for getting errors

	//for (auto it : myDataQueue)
	//	cout << it;
}

void queue_push_pop_front_back()
{
	// front() - get the element at the front of the queue (does not remove it)
	// pop() - removes the front element (does not return what element was removed)
	// push() - adds and element at the front of the current ones

	queue<int> myQueue;

	// Pushing some elements to the queue; the queue will be (from front to bottom): 0 1 2 3 4 5 6 7 8 9
	for (int i = 0; i < 10; i++)
	{
		myQueue.push(i);
	}
	cout << myQueue.size() << " " << myQueue.front() << "\n"; // 10 9

	// Poping elements from the queue; the queue will be (from front to bottom): 5 6 7 8 9
	while (myQueue.front() < 5)
	{
		myQueue.pop();
	}
	cout << myQueue.size() << " " << myQueue.front() << "\n"; // 5 5

	// Front and back values can also be modified
	myQueue.front() += 5;
	myQueue.back() = myQueue.front() + 1;
	cout << myQueue.front() << "\n"; // 10
	cout << myQueue.back() << "\n"; // 11
}

void queue_constructors()
{
	// queue - data structure which allows insertions at it's back and extactions at it's front: push elements at back, pop elements at the front
	// In other words, you cannot insert, erase or update other elements than the first or last
	// In C++ queue is an adapter container: adapts other data structures (e.g. deque, vector) so that they satisfy the above constraints

	queue<int> myQueue; // The default underlying container is deque
	cout << myQueue.empty() << " " << myQueue.size() << "\n"; // true 0

	vector<int> myData(5, 10);
	queue<int, vector<int>> myDataQueue(myData); // creates a queue containing the data from vector
												 // must explicitly specify the container to be vector if initialized from vector
	cout << myDataQueue.size() << "\n"; // 5

	deque<int> myDeque(10, 10);
	queue<int> myQueueFromDeque(myDeque); // creates a queue containing the data from deque
	cout << myQueueFromDeque.size() << "\n"; // 10

	list<int> myList(7, 10);
	queue<int, list<int>> myQueueFromList(myList); // creates a queue containing the data from deque
	cout << myQueueFromList.size() << "\n"; // 7
}

int main()
{
	cout << "Constructing some queues:\n";
	queue_constructors();
	cout << "\n-----------------------------------------------\n";
	cout << "Adding, removing and updating elements:\n";
	queue_push_pop_front_back();
	cout << "\n-----------------------------------------------\n";
	cout << "Iterating the queue:\n";
	queue_iterating();

	return 0;
}