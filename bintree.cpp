// ---------------------------------------bintree.cpp-----------------------------------------------------
// -
// Name: Andrew Chou
// Course Section: CSS 343 B
// Creation Date: 04/19/2022
// Date of Last Modification: 04/24/2022
// ----------------------------------------------------------------------------------------------------
// Purpose: .cpp file for bintree class
//          have functions to insert element, makeEmpty to delete everything
//			have operater == != = 
//          have virtual destructor
//			
// ----------------------------------------------------------------------------------------------------

#include "bintree.h"
#include <iostream>

using namespace std;

//------------------------- Constructor ---------------------------------
// initiate the root to nullptr
// Preconditions: NONE
// Postconditions: create an empty tree, root point to nullptr.
BinTree::BinTree() {
	this->root = nullptr;
}
//--------------------------Copy Constructor-----------------------------
// destroy the current tree, and copy the content of source tree to current
// Preconditions: None
// Postconditions: destroy current tree, copy the tree from the param
BinTree::BinTree(const BinTree& source) {
	// destroy current tree
	this->root = nullptr;
	// copy the content of the params to the original tree
	*this = source;
}

//---------------------------Destructor----------------------------------
// destroy the whole tree directly
// Preconditions: tree remains the same
// Postconditions: the whole being destroy, all memory used being deallocated
BinTree::~BinTree() {
	this->makeEmpty();
}

// operator-------------
//---------------------------operator=------------------------------------
// assign the lhs tree with the rhs trees
// Preconditions: tree remain the same
// Postconditions: the lhs tree being destroy and copy the whole tree of rhs
BinTree& BinTree::operator=(const BinTree& rhs) {
	if (*this == rhs) {
		return *this;
	}
	// at this point, the original tree is not the same as rhs
	// delete the whole original tree
	makeEmpty();
	equalHelper(root, rhs.root);

	return *this;
}

//----------------------------equalHelper------------------------------------
// to recursively traverse the rhs tree and copy the data to original tree
// Preconditions: no recursion traversal happens
// Postconditions: recurse the whole rhs tree and copy the data as traverse
void BinTree::equalHelper(Node*& orig, Node* rhs) {
	if (rhs != nullptr) {
		orig = new Node;
		// new pointers that contain the data
		NodeData* container = new NodeData(*rhs->data);
		// copy data
		orig->data = container;

		// traverse left (copy left data as well)
		equalHelper(orig->left, rhs->left);
		// traverse right (copy right data as well)
		equalHelper(orig->right, rhs->right);
	}
	// rhs is nullptr (empty tree)
	else {
		orig = nullptr;
	}
}

//-------------------------------operator==------------------------------------
// compare the lhs with the rhs tree
// Preconditions: no comparison occured
// Postconditions: compare the lhs tree with the rhs tree, true if equal, false otherwise
bool BinTree::operator==(const BinTree& rhs) const {
	return equalityTestHelper(this->root, rhs.root);
}

//------------------------------------==helper---------------------------------------
// recursively traverse in preorder to test data for equality
// Preconditions: no recursion traversal occured
// Postconditions: recursively traverse the tree and compare data. Return true if all
//		all data are the same, false otherwise
bool BinTree::equalityTestHelper(Node* lhsPtr, Node* rhsPtr) const {
	// case 1: both tree are empty, so they are the same
	if (lhsPtr == nullptr && rhsPtr == nullptr) {
		return true;
	}
	// case 2: one of them might be empty, so not the same
	if (lhsPtr == nullptr || rhsPtr == nullptr) {
		return false;
	}
	// case 3: data are the same, and for leaf testing (no child for both tree)
	// if left tree current pointer data equal to right tree current pointer data
	// and there's no child for both side for both tree
	if (*lhsPtr->data == *rhsPtr->data && lhsPtr->left == nullptr && rhsPtr->left == nullptr
		&& lhsPtr->right == nullptr && rhsPtr->right == nullptr) {
		return true;
	}
	// case 4: data are the same for current ptr, traverse in preorder to test data recursively
	return (*lhsPtr->data == *rhsPtr->data && equalityTestHelper(lhsPtr->left, rhsPtr->left)
		&& equalityTestHelper(lhsPtr->right, rhsPtr->right));
}

//-------------------------------------operator!=--------------------------
// test for inequality
// Preconditions: no comparision
// Postconditions: using the operator== to test the lhs and rhs tree, true if data are 
//		not the same, false if the trees are identical.
bool BinTree::operator!=(const BinTree& rhs) const {
	return !(*this == rhs);
}

// Accessor----
//------------------------------operator<<--------------------------------
// friend ostream function to print the tree out to console
// Preconditions: no tree print to console
// Postconditions: displaying the tree in an inorder order to console
ostream& operator<<(ostream& out, const BinTree& bin) {
	bin.inorderTraversal(bin.root);
	out << "\n";
	return out;
}

//------------------------------Inorder Traverse helper------------------
// traverse and print tree recursively in inorder order
// Preconditions: no recursion on the tree traversal
// Postconditions: traverse the tree recursively in inorder and print data
void BinTree::inorderTraversal(Node* root) const{
	if (root != nullptr) {
		inorderTraversal(root->left);
		cout << *root->data << " ";
		inorderTraversal(root->right);
	}
}

//----------------------------------------retrieve------------------------------
// retrieve data from the tree
// Preconditions: no scan on tree done
// Postconditions: scan the tree for the data, return true if found, false otherwise
bool BinTree::retrieve(const NodeData& data, NodeData*& nodePtr) {
	return retrieveHelper(this->root, data, nodePtr);
}

//---------------------------------retrieveHelper-------------------------------------
// recursively scan tree for data, left first, right later
// Preconditions: no traversal scan
// Postconditions: traverse the whole tree until found the data or reaching nullptr
bool BinTree::retrieveHelper(Node*& root, const NodeData& data, NodeData*& dataPointer) const {
	// empty tree
	if (root == nullptr) {
		dataPointer = nullptr;
		return false; // tree is empty, nothing found
	}
	if (*root->data == data) {
		dataPointer = root->data;
		return true; // found the exact same value
	}
	// traversing the tree 
	// left traverse
	else if (data < *root->data) {
		return retrieveHelper(root->left, data, dataPointer);
	}
	// right traverse
	else if (data > *root->data) {
		return retrieveHelper(root->right, data, dataPointer);
	}
	// tree is not empty and after exhausive traversal, still cannot find exact value
	else {
		return false;
	}
}

//--------------------------------getHeight()----------------------------------
// height of a node to the longest leaf, the node itself counts as one as well
// Preconditions: no height returned
// Postconditions: scan the tree for data as target, then count the height from the target
//		to longest leaf
int BinTree::getHeight(const NodeData& data) const {
	return getHeightHelper(this->root, data);
}

//--------------------------------getHeightHelper()----------------------------
// recursively traverse the tree until finding the target
// Preconditions: no traversal
// Postconditions: traverse the tree until found the target node
//		then call the counterhelper method to count to longest leaf
int BinTree::getHeightHelper(Node* root, const NodeData& data) const{
	// if the root is at nullptr, so it's empty, height is 0
	if (root == nullptr) {
		return 0;
	}
	// found the node on the tree, start counting until reaching longest path
	else if (*root->data == data) {
		return heightCounter(root);
	}
	// search on the tree to find the data on the tree, until reaching leaf if node not present
	else {
		int leftBranch = getHeightHelper(root->left, data);
		int rightBranch = getHeightHelper(root->right, data);
		return max(rightBranch, leftBranch);
	}
}

//-------------------------heightCounter()----------------------------------
// count the height from targeted node (root now) to longest path
// Preconditions: no count occured
// Postconditions: count the height from target node and return the value
int BinTree::heightCounter(Node* root) const {
	if (root == nullptr) {
		return 0;
	}
	// found the node, recursively count the node on either left and right path
	// then max function uses the bigger number (longer path) + 1 (the nodedata of param)
	else {
		return 1 + max(heightCounter(root->left), heightCounter(root->right));
	}
}

// Other functions---------
//--------------------------------------bstreeToArray-------------------------------
// call helper method to traverse the tree and add them to array
// Preconditions: tree remain the same
// Postconditions: traversed the tree and add them to array, then delete the tree
// function to fill an array of NodeData* by using an inorder traversal of tree
void BinTree::bstreeToArray(NodeData* arr[]) {
	bstreeToArrayHelper(root, arr);
	makeEmpty();
}

//-------------------------------------bstreeToArrayHelper---------------------------
// traverse tree and add the element to array
// Preconditions: no traversal
// Post conditions: traverse tree and add element to array
int BinTree::bstreeToArrayHelper(Node* root, NodeData* arr[]) {
	// base case when reaching leaf
	if (root == nullptr) {
		return 0;
	}
	// traverse to left branch
	int leftBranch = bstreeToArrayHelper(root->left, arr);
	// a temporary container to store data pointer.
	NodeData* container = root->data;
	// disconnect the data from the tree.
	root->data = nullptr;
	*(arr + leftBranch) = container;
	container = nullptr;
	int rightBranch = bstreeToArrayHelper(root->right, arr + leftBranch + 1);
	return 1 + leftBranch + rightBranch;
}

//---------------------------------arrayToBSTree------------------------------------
// build bst from a sorted array
// Preconditions: array remain the same, no tree created
// Postconditions: get size of non-null pointers in array, and call helper method for 
//		tree creation from the array elements, all elements of array are set nullptr
void BinTree::arrayToBSTree(NodeData* source[]) {
	// delete and deallocate tree first
	this->makeEmpty();
	int maxArrSize = 0;
	// only looping for 100 elements only, 
	// assuming the max array is less or equal to 100
	for (int i = 0; i < 100; i++) {
		// test for the size of the array of pointers
		// since some elements may be nullptr, use if to do exception handling
		if (source[i] != nullptr) {
			maxArrSize++;
		}
		// per instruction, set everything of the array to nullpointer
		else {
			source[i] = nullptr;
		}
	}
	// counter starts from 0, the highest end is the maxArrSize - 1 
	//		since array starts at index 0
	arrayToBSTreeHelper(root, source, 0, maxArrSize - 1);
}

//---------------------------arrayToBSTHelper-------------------------------------------
// recursively scan array of pointers and add the value to tree
// uses the midpoint data to assign as the root or parents
// Preconditions: array remain the same, no tree created
// Postconditions: tree created from the array elements, all elements of array are nullptr
void BinTree::arrayToBSTreeHelper(Node* root, NodeData* source[], int counter, int maxArr) {
	// base case 
	// when counter is equal to max array size, then reach the end of array
	// the end of array, the pointer would be at leaf, set them to nullptr
	if (counter < maxArr) {
		root = nullptr;
	}
	else {
		// find the mid of array, use the element as the root data
		int mid = (counter + maxArr) / 2;
		// assign element of root as the source[mid]
		NodeData* container = source[mid];
		// after obtained the element data, set the array element to null per instruction
		source[mid] = nullptr;
		// uses insert function to add the value to tree
		insert(container);
		// recursively add the value starting from parents 
		// first recursion, the mid of first half of array is the root of left branch
		// the mid of second half of array is the root of right branch
		arrayToBSTreeHelper(root, source, counter, mid - 1);
		arrayToBSTreeHelper(root, source, mid + 1, maxArr);

	}
}

// Other Helper Methods -----
//--------------------------------isEmpty()------------------------------
// check if the tree is empty
// Preconditions: NONE
// Postconditions: using the root data to check if the tree is empty or not
//		true if empty, false otherwise
bool BinTree::isEmpty() const {
	if (this->root == nullptr) {
		return true;
	}
	return false;
}

//---------------------------------makeEmpty()-------------------------------
// make the entire tree empty
// Preconditions: tree remain the same
// Postconditions: tree being destroy and deallocated
void BinTree::makeEmpty() {
	makeEmptyHelper(root);
}

//--------------------------------makeEmptyHelper()--------------------------
// recursive scan tree and delete/deallocate tree
// Preconditions: tree remains the same
// Postconditions: tree being destroyed and deallocated
void BinTree::makeEmptyHelper(Node*& root) {
	// check if the root of tree point to nullptr
	// if points to nullptr, then it's empty tree, no action needed
	if (root != nullptr) {
		// if the data pointer is nullptr = no data
		// only perform action when it's not nullptr
		if (root->data != nullptr) {
			delete root->data;
			root->data = nullptr;
		}
		// traverse until reaching leaf, then delete their data recursively
		makeEmptyHelper(root->left);
		makeEmptyHelper(root->right);

		// until everything is deleted besides the root, start deleting root and set to null
		delete root;
		root = nullptr;
	}
}

//--------------------------------insert()---------------------------------
// insert the data to tree accordingly while maintaining BST structure
// Preconditions: no data added
// Postconditions: insert data to tree while keeping BST structure
bool BinTree::insert(NodeData* data) {
	return insertHelper(this->root, data);
}

//-------------------------------insertHelper-----------------------------
// recursively find the right place for insertion then add the value to tree
// Preconditions: no data added
// Postconditions: insert data to tree accordingly
bool BinTree::insertHelper(Node*& root, NodeData* newData) {
	// nothing in tree now
	if (root == nullptr) {
		root = new Node();
		root->data = newData;
		root->left = nullptr;
		root->right = nullptr;
	}
	// recursive traversal
	// if root is bigger than newData to insert, have new data go to left tree branch
	else if (*root->data > *newData) {
		insertHelper(root->left, newData);
	}
	// go to right branch
	else if (*root->data < *newData) {
		insertHelper(root->right, newData);
	}
	// the *root->data == *newData, no action performed
	else {
		return false;
	}
	return true;
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}