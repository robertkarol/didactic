#include <iostream>
#include <stack>
#include <vector>
#include <deque>

using namespace std;

void stack_iterating()
{
	cout << "You just don't!!!\n"; // You can't iterate with a for: you must remove top element to get access to the second and so on

	vector<int> myData(5, 10);
	stack<int, vector<int>> myDataStack(myData);

	// Uncomment the code below for getting errors

	//for (auto it : myDataStack)
	//	cout << it;
}

void stack_push_pop_top()
{
	// top() - get the element at the top of the stack (does not remove it)
	// pop() - removes the top element (does not return what element was removed)
	// push() - adds and element at the top of the current ones

	stack<int> myStack;

	// Pushing some elements to the stack; the stack will be (from top to bottom): 9 8 7 6 5 4 3 2 1 0
	for (int i = 0; i < 10; i++)
	{
		myStack.push(i);
	}
	cout << myStack.size() << " " << myStack.top() << "\n"; // 10 9

	// Poping elements from the stack; the stack will be (from top to bottom): 5 4 3 2 1 0
	while (myStack.top() > 5)
	{
		myStack.pop();
	}
	cout << myStack.size() << " " << myStack.top() << "\n"; // 6 5

	// Top value can also be modified
	myStack.top() += 5;
	cout << myStack.top() << "\n"; // 10
}

void stack_constructors()
{
	// stack - data structure which allows only opertions at it's top: push elements at top, pop elements at the top
	// In other words, you cannot insert, erase or update other elements than the first
	// In C++ stack is an adapter container: adapts other data structures (deque, vector) so that they satisfy the above constraints

	stack<int> myStack; // The default underlying container is deque
	cout << myStack.size() << "\n"; // 0; stack is empty

	vector<int> myData(5, 10);
	stack<int, vector<int>> myDataStack(myData); // creates a stack containing the data from vector
												 // must explicitly specify the container to be vector if initialized from vector
	cout << myDataStack.size() << "\n"; // 5

	deque<int> myDeque(10, 10);
	stack<int> myStackFromDeque(myDeque); // creates a stack containing the data from deque
	cout << myStackFromDeque.size() << "\n"; // 10
}

int main()
{
	cout << "Constructing some stacks:\n";
	stack_constructors();
	cout << "\n-----------------------------------------------\n";
	cout << "Adding, removing and updating elements:\n";
	stack_push_pop_top();
	cout << "\n-----------------------------------------------\n";
	cout << "Iterating the stack:\n";
	stack_iterating();

	return 0;
}