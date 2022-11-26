#pragma once
#include <fstream>
#include <iostream>
#include "NODE.h"

class AVLTree {

	ptrNODE rotateRight(ptrNODE p);
	ptrNODE rotateLeft(ptrNODE p);
	ptrNODE bigRotationBalance(ptrNODE p); // balance node p
	std::ostream& print(std::ostream& stream, ptrNODE node, int level);
	ptrNODE append(ptrNODE p, int k); 
	ptrNODE root;
	void clear(ptrNODE p); // only for destructor
public:
	AVLTree();
	AVLTree(int _key);
	AVLTree(const AVLTree& tree);
	AVLTree& AVLfromStream(std::istream& stream);
	void fixHeight(ptrNODE p);
	int balanceFactor(ptrNODE p);
	void append(int k); // input container
	ptrNODE remove(ptrNODE p, int k);
	ptrNODE findByValue(int key);
	ptrNODE findMin(ptrNODE p);
	ptrNODE findMax(ptrNODE p);
	ptrNODE removeMin(ptrNODE p);
	ptrNODE removeMax(ptrNODE p);
	ptrNODE copyTree(const ptrNODE node);
	std::ostream& printTree(std::ostream& stream); // output container
	ptrNODE getRoot();
	unsigned int getHeight(ptrNODE p);
	~AVLTree();
};