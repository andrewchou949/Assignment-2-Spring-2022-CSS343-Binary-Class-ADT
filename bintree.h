// ---------------------------------------bintree.h-----------------------------------------------------
// -
// Name: Andrew Chou
// Course Section: CSS 343 B
// Creation Date: 04/19/2022
// Date of Last Modification: 04/24/2022
// ----------------------------------------------------------------------------------------------------
// Purpose: .h file for bintree class contain the contract interface for bintree.cpp file
// 
// ----------------------------------------------------------------------------------------------------


#ifndef ASS2_BINTREE_H
#define ASS2_BINTREE_H

#include "nodedata.h"
#include <iostream>
class BinTree {

	//------------------------------operator<<--------------------------------
	// friend ostream function to print the tree out to console
	// Preconditions: no tree print to console
	// Postconditions: displaying the tree in an inorder order to console
	friend ostream& operator<<(ostream& out, const BinTree& bin);

public:

	//------------------------- Constructor ---------------------------------
	// initiate the root to nullptr
	// Preconditions: NONE
	// Postconditions: create an empty tree, root point to nullptr.
	BinTree();

	//--------------------------Copy Constructor-----------------------------
	// destroy the current tree, and copy the content of source tree to current
	// Preconditions: None
	// Postconditions: destroy current tree, copy the tree from the param
	BinTree(const BinTree& source);

	//---------------------------Destructor----------------------------------
	// destroy the whole tree directly
	// Preconditions: tree remains the same
	// Postconditions: the whole being destroy, all memory used being deallocated
	virtual ~BinTree();

	//Operator -----
	//---------------------------operator=------------------------------------
	// assign the lhs tree with the rhs trees
	// Preconditions: tree remain the same
	// Postconditions: the lhs tree being destroy and copy the whole tree of rhs
	BinTree& operator=(const BinTree&);
	
	//-------------------------------operator==------------------------------------
	// compare the lhs with the rhs tree
	// Preconditions: no comparison occured
	// Postconditions: compare the lhs tree with the rhs tree, true if equal, false otherwise
	bool operator==(const BinTree&) const;
	
	//-------------------------------------operator!=--------------------------
	// test for inequality
	// Preconditions: no comparision
	// Postconditions: using the operator== to test the lhs and rhs tree, true if data are 
	//		not the same, false if the trees are identical.
	bool operator!=(const BinTree&) const;

	//Accessor -----
	//----------------------------------------retrieve------------------------------
	// retrieve data from the tree
	// Preconditions: no scan on tree done
	// Postconditions: scan the tree for the data, return true if found, false otherwise
	bool retrieve(const NodeData& data, NodeData*& node);

	//--------------------------------getHeight()----------------------------------
	// height of a node to the longest leaf, the node itself counts as one as well
	// Preconditions: no height returned
	// Postconditions: scan the tree for data as target, then count the height from the target
	//		to longest leaf
	int getHeight(const NodeData& data) const;

	//Other functions -----
	//--------------------------------------bstreeToArray-------------------------------
	// call helper method to traverse the tree and add them to array
	// Preconditions: tree remain the same
	// Postconditions: traversed the tree and add them to array, then delete the tree
	// function to fill an array of NodeData* by using an inorder traversal of tree
	void bstreeToArray(NodeData* arr[]);

	//---------------------------------arrayToBSTree------------------------------------
	// build bst from a sorted array
	// Preconditions: array remain the same, no tree created
	// Postconditions: get size of non-null pointers in array, and call helper method for 
	//		tree creation from the array elements, all elements of array are set nullptr
	void arrayToBSTree(NodeData* source[]);

	//------------------------- displaySideways ---------------------------------
	// Displays a binary tree as though you are viewing it from the side;
	// hard coded displaying to standard output.
	// Preconditions: NONE
	// Postconditions: BinTree remains unchanged.
	void displaySideways() const;

	// Other Helper Method-----------
	//--------------------------------isEmpty()------------------------------
	// check if the tree is empty
	// Preconditions: NONE
	// Postconditions: using the root data to check if the tree is empty or not
	//		true if empty, false otherwise
	bool isEmpty() const;

	//---------------------------------makeEmpty()-------------------------------
	// make the entire tree empty
	// Preconditions: tree remain the same
	// Postconditions: tree being destroy and deallocated
	void makeEmpty();

	//--------------------------------insert()---------------------------------
	// insert the data to tree accordingly while maintaining BST structure
	// Preconditions: no data added
	// Postconditions: insert data to tree while keeping BST structure
	bool insert(NodeData* data);

private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

	// Helper Methods --------
	//------------------------------Inorder Traverse helper------------------
	// traverse and print tree recursively in inorder order
	// Preconditions: no recursion on the tree traversal
	// Postconditions: traverse the tree recursively in inorder and print data
	void inorderTraversal(Node* root) const;

	//----------------------------equalHelper------------------------------------
	// to recursively traverse the rhs tree and copy the data to original tree
	// Preconditions: no recursion traversal happens
	// Postconditions: recurse the whole rhs tree and copy the data as traverse
	void equalHelper(Node*& orig, Node* rhs);

	//------------------------------------==helper---------------------------------------
	// recursively traverse in preorder to test data for equality
	// Preconditions: no recursion traversal occured
	// Postconditions: recursively traverse the tree and compare data. Return true if all
	//		all data are the same, false otherwise
	bool equalityTestHelper(Node* lhs, Node* rhs) const;

	//---------------------------------retrieveHelper-------------------------------------
	// recursively scan tree for data, left first, right later
	// Preconditions: no traversal scan
	// Postconditions: traverse the whole tree until found the data or reaching nullptr
	bool retrieveHelper(Node*& root, const NodeData& data, NodeData*& dataPointer) const;

	//--------------------------------getHeightHelper()----------------------------
	// recursively traverse the tree until finding the target
	// Preconditions: no traversal
	// Postconditions: traverse the tree until found the target node
	//		then call the counterhelper method to count to longest leaf
	int getHeightHelper(Node* root, const NodeData& data) const;

	//-------------------------heightCounter()----------------------------------
	// count the height from targeted node (root now) to longest path
	// Preconditions: no count occured
	// Postconditions: count the height from target node and return the value
	int heightCounter(Node* root) const;

	//---------------------------arrayToBSTHelper-------------------------------------------
	// recursively scan array of pointers and add the value to tree
	// uses the midpoint data to assign as the root or parents
	// Preconditions: array remain the same, no tree created
	// Postconditions: tree created from the array elements, all elements of array are nullptr
	void arrayToBSTreeHelper(Node* root, NodeData* source[], int counter, int maxArr);

	//-------------------------------------bstreeToArrayHelper---------------------------
	// traverse tree and add the element to array
	// Preconditions: no traversal
	// Post conditions: traverse tree and add element to array
	int bstreeToArrayHelper(Node* root, NodeData* arr[]);

	//--------------------------------makeEmptyHelper()--------------------------
	// recursive scan tree and delete/deallocate tree
	// Preconditions: tree remains the same
	// Postconditions: tree being destroyed and deallocated
	void makeEmptyHelper(Node*& current);

	//-------------------------------insertHelper-----------------------------
	// recursively find the right place for insertion then add the value to tree
	// Preconditions: no data added
	// Postconditions: insert data to tree accordingly
	bool insertHelper(Node*& root, NodeData* newData);

	//---------------------------- Sideways -------------------------------------
	// Helper method for displaySideways
	// Preconditions: NONE
	// Postconditions: BinTree remains unchanged.
	void sideways(Node*, int) const;			// provided below, helper for displaySideways()
};

#endif