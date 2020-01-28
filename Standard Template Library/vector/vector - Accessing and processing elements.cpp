#include <iostream>
#include <vector>

using namespace std;

void vector_accessing_using_indices_and_rangefor(vector<int> myData) // Use references if you don't want data to be copied (linear time)
{
	for (int i = 0; i < myData.size(); i++)
	{
		cout << myData[i] << " "; // Do anything with the element
		myData.at(i) = i; // myData.at(i) equivalent to myData[i]; both have constant time complexity
	}
	cout << "\n";

	// This is called "range for". Appliable to all iterable collections
	for (const auto& it : myData) // Fastest way to iterate: you get unmodifiable references to elements
	// for(auto& it : myData) - it can be modified and the corresponding element of the vector will get updated
	// for(auto it : myData) - it will be a copy of each element => more time consuming
	{
		cout << it << " ";
	}
	cout << "\n";
}

void vector_using_iterators(vector<int> myData) // Use references if you don't want data to be copied (linear time)
{
	// We'll use iterators (similar somehow to pointers)
	// begin() points to the first element of vector
	// end() points to the location after the last element (outside of the vector)
	// iterator is an inner class of vector, acessed through scope operator ::

	for (vector<int>::iterator it = myData.begin(); it < myData.end(); it++) 
	{
		// We use * to access the value the same way we did with pointers
		cout << *it << " "; // Do anything with the element
		*it = it - myData.begin(); // Each element will have a value equal to the offset of the element relatively to begin
	}
	cout << "\n";

	// For iterating the reversed vector, use rbegin and rend the same way as above
	// Will output 4 3 2 1 0
	for (auto it = myData.rbegin(); it < myData.rend(); it++) // shorter way (type is inferred from what on the right side)
	{
		// We use * to access the value the same way we did with pointers
		cout << *it << " ";
	}
	cout << "\n";
}

void vector_accessing_with_front_and_back(vector<int> myData) // Use references if you don't want data to be copied (linear time)
{
	// Suppose we want to remove elements from the back of the vector while last element equals the first
	// myData wil initially be 4 4 4 4 4; we set the second element to 5 so we not empty the vector
	myData[1] = 5; // 4 5 4 4 4
	auto initialLastElementIterator = myData.end() - 1;

	// front() - get the element at the index 0
	// back() - get the element at the last valid index
	// pop_back() - removes the last element; we don't have pop_front() on vector
	while (myData.front() == myData.back())
	{
		myData.pop_back();
	}

	cout << "No of remaining elements: " << myData.size() << "\n"; // 2 (4 & 5 remained)

	// cout << *initialLastElementIterator; - CRASH! iterator is invalidated by removing elements!

	// We empty the vector 
	myData.pop_back();
	myData.pop_back();

	// myData.front(); - CRASH! Empty vector.
	// myData.back(); - CRASH! Empty vector.
}
void vector_insert_erase_elements_at_any_position(vector<int> myData)
{
	myData.erase(myData.begin() + 2); // Erase the 3rd element; linear time because we have to shift elements
	for (const auto& it : myData)
	{
		cout << it << " ";
	}
	cout << "\n";

	myData.insert(myData.begin() + 2, 55); // Insert 55 to be the 3rd element
	for (const auto& it : myData)
	{
		cout << it << " ";
	}
	cout << "\n";

	myData.erase(myData.begin() + 3, myData.end()); // Erase from the 4th element to the end; the method deletes all element in range [first, last)
	for (const auto& it : myData)
	{
		cout << it << " ";
	}
	cout << "\n";

	myData.insert(myData.begin() + 2, 2, 66); // Insert 2 elements of value 66 after the 3rd element
	for (const auto& it : myData)
	{
		cout << it << " ";
	}
	cout << "\n";

	int myDataArray[] = { 1, 2, 3, 4 };
	myData.insert(myData.end(), myDataArray, myDataArray + 4); // Insert the elements of the array at the end; other vector can be used too
	for (const auto& it : myData)
	{
		cout << it << " ";
	}
	cout << "\n";
}

void vector_clear_elements_free_memory(vector<int> myData)
{
	cout << "We got a vector with a capacity of " << myData.capacity() << " and a size of " << myData.size() << "\n"; // 5 and 5
	myData.clear(); // Clears the vector. Does not free the memory.
	cout << "After clear: capacity of " << myData.capacity() << " and a size of " << myData.size() << "\n"; // 5 and 0

	// Trick to empty memory:
	vector<int>().swap(myData); // Swaps the content to a temporary variable that is destructed immediately
}

int main()
{
	vector<int> myData(5, 4);
	cout << "Iterating elements with indices and range for:\n";
	vector_accessing_using_indices_and_rangefor(myData);
	cout << "\n-----------------------------------------------\n";
	cout << "Using iterators to access elements:\n";
	vector_using_iterators(myData);
	cout << "\n-----------------------------------------------\n";
	cout << "Accessing with front() and back():\n";
	vector_accessing_with_front_and_back(myData);
	cout << "\n-----------------------------------------------\n";
	cout << "Erasing and inserting elements in vector:\n";
	vector_insert_erase_elements_at_any_position(myData);
	cout << "\n-----------------------------------------------\n";
	return 0;
}