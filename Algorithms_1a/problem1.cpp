#include <iostream>
#include <time.h>
#include <stack>
#include <list>

using namespace std;

//////header_file_content//////
struct Node {
	int data;
	stack<int> mStack;

}node;

/////Common-functions//////
void printMaxVals(int max1, int max2);

/////Array-Recursive//////
void ArrayRecursiveInput(int &size);
void printArray(Node* array, int size);
Node ArrayRecursive(Node *myArray, int first, int last, int size);
void findMaxforOutput(Node myArray);
Node findMaxRecursive(Node* myArray, int size);

/////List-Iterative//////
void ListIterativeInput(int &size);
void printList(list<Node> &myList, int size);
void FindMaxList(list<Node> &myList);



void main() {
	int size;
	int menu;
	srand(time(NULL));


	cout << " Choose Program" << endl;
	cout << " 1 - Array (recursive)." << endl;
	cout << " 2 - Linked list (iterative) " << endl;
	cout << " 3 - Exit  " << endl;
	cout << " Enter 1/2/3 : ";
	cin >> menu;


	while (menu != 1 && menu != 2 && menu != 3) {
		cout << " WRONG INPUT! : " << endl << endl;
		cout << " Enter 1/2/3 : ";
		cin >> menu;
	}

	switch (menu) {
	case 1: ArrayRecursiveInput(size); break;
	case 2: ListIterativeInput(size); break;
	case 3: exit(1);
	default: cout << "done!" << endl;
	}

}


/////Array-Recursive//////

void ArrayRecursiveInput(int &size) {

	cout << "Choose size for the array :";
	cin >> size;
	if (size < 1) {
		cout << "Wrong input - array size cannot be less then 1" << endl;
		system("pause");
		exit(1);
	}
	Node *myArray = new Node[size];

	for (int i = 0; i < size; i++) {
		myArray[i].data = rand() % 100 + 1;

	}
	printArray(myArray, size);

	if (size == 1) {
		cout << "Size of the array is 1 - max1 is : " << myArray->data << endl; \
			system("pause");
		exit(1);

	}
	else {
		Node finalNode = findMaxRecursive(myArray, size);
		findMaxforOutput(finalNode);
		system("pause");
	}
}

void printArray(Node *array, int size) {
	for (int i = 0; i < size; i++) {
		cout << array[i].data << " , ";
	}
	cout << endl;

}



Node findMaxRecursive(Node* myArray, int size)
{
	int even_odd;



	if (size < 2) {
		return myArray[0];
	}

	else {

		if (size % 2 != 0)

		{
			even_odd = (size / 2) + 1;
		}
		else
		{
			even_odd = size / 2;
		}




		Node left = findMaxRecursive((myArray + size / 2), even_odd);
		Node right = findMaxRecursive(myArray, size / 2);
		if (left.data > right.data)
		{
			left.mStack.push(right.data);
			return left;
		}
		else
		{
			right.mStack.push(left.data);
			return right;
		}


	}
}


Node ArrayRecursive(Node *myArray, int first, int last, int size) {
	int mid = size / 2;

	if (size == 1) {
		return myArray[0];
	}

	Node left = ArrayRecursive(myArray, first, mid, size / 2);
	Node right = ArrayRecursive(myArray, mid, last, size / 2);

	if (right.data < left.data) {
		left.mStack.push(right.data);
		return left;
	}
	else {
		right.mStack.push(left.data);
		return right;
	}
}



void findMaxforOutput(Node myArray) {

	int max2, max1;
	max2 = 0;
	max1 = myArray.data;

	while (!myArray.mStack.empty()) {
		if (max2 <= myArray.mStack.top()) {
			max2 = myArray.mStack.top();
		}
		myArray.mStack.pop();

	}
	printMaxVals(max1, max2);
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////List-Iterative//////


void ListIterativeInput(int &size) {

	list<Node> myList;
	Node extraNode;

	cout << "Choose a size for the list : ";
	cin >> size;
	if (size < 1) {
		cout << " wrong input , list must be size of 1 or bigger " << endl;
		system("pause");
		exit(1);
	}


	for (int i = 0; i < size; i++) {
		extraNode.data = rand() % 100 + 1;
		myList.push_front(extraNode);

	}
	printList(myList, size);
	FindMaxList(myList);
	system("pause");

}


void printList(list<Node> &myList, int size) {
	list<Node>::iterator start = myList.begin();
	list<Node>::iterator end = myList.end();
	for (; start != end; start++)
	{
		cout << "-{" << start->data << "}-";

	}
	cout << endl;
}

void printMaxVals(int max1, int max2) {
	cout << "Max1 is : " << max1 << endl;
	cout << "Max2 is : " << max2 << endl;
}


void FindMaxList(list<Node> &myList) {
	int max1, max2;
	max1 = max2 = 0;
	//assigning iterator
	list<Node>::iterator start = myList.begin();
	list<Node>::iterator end = myList.end();

	if (myList.size() == 1) {
		max1 = start->data;
		cout << "list size is 1 - max number is : " << start->data << endl;
		system("pause");
		exit(1);

	}

	while (myList.size() > 1) {
		start = myList.begin();
		list<Node>::iterator next = myList.begin();
		int size = myList.size();
		next++;


		for (int i = 0; i < size / 2; i++) {
			if (start->data > next->data) {
				start->mStack.push(next->data);
				myList.erase(next);
				next = start;
				next++;;
				if (i < size / 2 - 1)
					next++;
			}
			else {
				next->mStack.push(start->data);
				myList.erase(start);
				start = next;
				next++;
				if (i < size / 2 - 1)
					next++;
			}
		}
		start = myList.begin();
		max1 = start->data;

	}
	while (!start->mStack.empty()) {
		if (start->mStack.top() > max2) {
			max2 = start->mStack.top();
			start->mStack.pop();

		}
		else {
			start->mStack.pop();

		}

	}

	printMaxVals(max1, max2);
}