#include "AVL_Tree.h"

int main() 
{
	AVLTree t;
	std::ifstream file("avlTreeInit.txt");
	t.AVLfromStream(file);
	/*t.append(4);
	t.append(3);
	t.append(1);
	t.append(0);
	t.append(15);
	t.append(228);
	t.append(-34);
	t.append(66);
	t.append(6);


	t.remove(t.getRoot(), 0);*/

	/*t.removeMax(t.getRoot());
	t.removeMin(t.getRoot());*/

	t.printTree(std::cout);
}