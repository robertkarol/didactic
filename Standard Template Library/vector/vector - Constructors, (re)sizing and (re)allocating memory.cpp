#include <iostream>
#include <vector>

using namespace std;


void vector_with_default_constructor_and_pushback()
{
	// We declare a vector.
	// With this declaration, there is currently no memory allocated in it: it's empty!
	// We called the allocated amount of memory capacity, and the actual number of elements - size
	// The memory is allocated on the heap, even though this is a local variable
	vector<int> myData;
	int desiredSize = 2500;

	cout << "myData has a size of " << myData.size() << "\n"; // 0
	cout << "myData has a capacity of " << myData.capacity() << "\n"; // 0

	// myData[anyIndex] => Segmentation fault!!!

	// We will add elements one by one
	// This approach does (re)allocations in the background. Every time you want to add a new element: 
	// if there is enough space (size < capacity), it adds the element at the end of the vector
	// if not, the capacity gets increased every time (it becomes 1 for the first element).
	// "Increased" means in the most implementations "doubled".
	for (int i = 0; i < desiredSize; i++)
	{
		myData.push_back(i);
	}

	cout << "myData has a size of " << myData.size() << "\n"; // 2500
	cout << "myData has a capacity of " << myData.capacity() << "\n"; // 4096 (GNU C++); 3597 (Visual Studio 2019)

	// We don't need to deallocate the heap memory. 
	// When exiting its scope, the destructor of the vector is automatically called and frees the memory
	// Time complexity for "adding" each element: O(1) amortized 
	// Amortized beacuse reallocations require linear-time complexity, 
	// which is amortized by the fact that such events occur with no great frequency relatively to vector size
}

void vector_with_fill_constructor()
{
	// We declare a vector.
	// With this declaration, we initially allocate memory for 5000 elements
	// Using this contructor, we'll declare an element with size = capacity = 5000
	// The memory is allocated on the heap, even though this is a local variable
	int desiredSize = 5000;
	vector<int> myData(desiredSize); // linear time complexity, elements have residual value
	// int defaultValue = 0;
	// vector<int> myData(desiredSize, defaultValue); - linear time complexity, default value applied for each element

	cout << "myData has a size of " << myData.size() << "\n"; // 5000
	cout << "myData has a capacity of " << myData.capacity() << "\n"; // 5000

	// myData[anyIndex] => no segmentation fault for 0 <= anyIndex < 5000

	// We have elements => we set values as we are used to
	for (int i = 0; i < desiredSize; i++)
	{
		myData[i] = i;
	}

	cout << "myData has a size of " << myData.size() << "\n"; // 5000
	cout << "myData has a capacity of " << myData.capacity() << "\n"; // 5000

	myData.push_back(5); // We'll need more capacity for this one => reallocation

	cout << "myData has a size of " << myData.size() << "\n"; // 5001
	cout << "myData has a capacity of " << myData.capacity() << "\n"; // 10000 (GNU C++); 7500 (Visual Studio 2019)

	// We don't need to deallocate the heap memory. 
	// When exiting its scope, the destructor of the vector is automatically called and frees the memory
	// Time complexity for "adding" each element: O(1)
}

void vector_with_preallocation_with_reserve_and_resize()
{
	// We declare a vector.
	// With this declaration, we initially allocate memory for 5000 elements
	// Using this contructor, we'll declare an element with size = capacity = 5000
	// The memory is allocated on the heap, even though this is a local variable
	int desiredSize = 5000;
	vector<int> myData1; // empty
	vector<int> myData2; // empty

	myData1.resize(desiredSize); // Work similarly to vector_with_preallocation
	myData2.reserve(desiredSize); // Reserves capacity but does not "add" elements

	cout << "myData1 has a size of " << myData1.size() << "\n"; // 5000
	cout << "myData1 has a capacity of " << myData1.capacity() << "\n"; // 5000

	cout << "myData2 has a size of " << myData2.size() << "\n"; // 0
	cout << "myData2 has a capacity of " << myData2.capacity() << "\n"; // 5000

	// myData1[anyIndex] => no segmentation fault for 0 <= anyIndex < 5000
	// myData2[anyIndex] => Segmentation fault!!!

	// We have elements => we set values as we are used to
	for (int i = 0; i < desiredSize; i++)
	{
		myData1[i] = i;
		myData2.push_back(i);
	}

	cout << "myData1 has a size of " << myData1.size() << "\n"; // 5000
	cout << "myData1 has a capacity of " << myData1.capacity() << "\n"; // 5000

	cout << "myData2 has a size of " << myData2.size() << "\n"; // 5000
	cout << "myData2 has a capacity of " << myData2.capacity() << "\n"; // 5000

	// We don't need to deallocate the heap memory. 
	// When exiting its scope, the destructor of the vector is automatically called and frees the memory
}

void vector_with_copy_range_and_initializerlist_constructors()
{
	int defaultValue = 5, desiredSize = 5000;
	vector<int> myData(desiredSize, defaultValue); // 5000 elements with a value of 5
	cout << "myData has a size of " << myData.size() << "\n"; // 5000
	cout << "myData has a capacity of " << myData.capacity() << "\n"; // 5000

	vector<int> copyOfMyData(myData); //copy constructor; 5000 elements with a value of 5; linear time complexity
	cout << "copyOfMyData has a size of " << copyOfMyData.size() << "\n"; // 5000
	cout << "copyOfMyData has a capacity of " << copyOfMyData.capacity() << "\n"; // 5000

	vector<int> aRangeFromMyData(myData.begin(), myData.begin() + 5); // range constructor; uses iterators (later topic)
																	  // 5 elements of value 5
	cout << "aRangeFromMyData has a size of " << aRangeFromMyData.size() << "\n"; // 5
	cout << "aRangeFromMyData has a capacity of " << aRangeFromMyData.capacity() << "\n"; // 5

	int myDataArray[] = { 1, 2, 3, 4, 5, 6 };
	vector<int> myDataFromArray(myDataArray, myDataArray + 3);
	cout << "myDataFromArray has a size of " << myDataFromArray.size() << "\n"; // 3
	cout << "myDataFromArray has a capacity of " << myDataFromArray.capacity() << "\n"; // 3
}

int main()
{
	cout << "Using default construcor and push_back method:\n";
	vector_with_fill_constructor();
	cout << "\n-----------------------------------------------\n";
	cout << "Using fill constructor and indexing elements:\n";
	vector_with_default_constructor_and_pushback();
	cout << "\n-----------------------------------------------\n";
	cout << "Using resize (myData1) and reserve (myData2):\n";
	vector_with_preallocation_with_reserve_and_resize();
	cout << "\n-----------------------------------------------\n";
	cout << "Using copy, range, any initializer list constructors:\n";
	vector_with_copy_range_and_initializerlist_constructors();
	cout << "\n-----------------------------------------------\n";

	return 0;
}

