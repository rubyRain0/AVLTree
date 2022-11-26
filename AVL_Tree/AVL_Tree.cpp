#include "AVL_Tree.h"

AVLTree::AVLTree()
{
	root = nullptr;
}

AVLTree::AVLTree(int _key)
{
	root = new NODE(_key);
}

AVLTree::AVLTree(const AVLTree& tree)
{
	root = copyTree(tree.root);
}

AVLTree::~AVLTree() 
{ 
	std::cout << '\n';
	clear(root); 
};

AVLTree& AVLTree::AVLfromStream(std::istream& stream)
{
	int info;
	while (stream >> info) {
		append(info);
	}

	return *this;
}

void AVLTree::fixHeight(ptrNODE p)
{
	unsigned int hl = getHeight(p->left);
	unsigned int hr = getHeight(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

unsigned int AVLTree::getHeight(ptrNODE p)
{
	if (p == nullptr) return 0;
	else
	{
		fixHeight(p);
		return p->height;
	}
}

ptrNODE AVLTree::getRoot()
{ 
	return this->root; 
};

int AVLTree::balanceFactor(ptrNODE p)
{
	return getHeight(p->right) - getHeight(p->left);
}

ptrNODE AVLTree::rotateRight(ptrNODE p)
{
	ptrNODE q = p->left;
	p->left = q->right;
	q->right = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

ptrNODE AVLTree::rotateLeft(ptrNODE q)
{
	ptrNODE p = q->right;
	q->right = p->left;
	p->left = q;
	fixHeight(q);
	fixHeight(p);
	return p;
}

ptrNODE AVLTree::bigRotationBalance(ptrNODE p) // балансировка узла p
{
	fixHeight(p); 
	if (balanceFactor(p) == 2)
	{
		if (balanceFactor(p->right) < 0)
			p->right = rotateRight(p->right);
		return rotateLeft(p);
	}
	if (balanceFactor(p) == -2)
	{
		if (balanceFactor(p->left) > 0)
			p->left = rotateLeft(p->left);
		return rotateRight(p);
	}
	return p;
}

void AVLTree::append(int k)
{
	root = append(root, k);
}

ptrNODE AVLTree::append(ptrNODE p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p)
		p = new NODE(k);
	if (k < p->key)
		p->left = append(p->left, k);
	else if (k > p->key)
		p->right = append(p->right, k);
	return bigRotationBalance(p);
}

ptrNODE AVLTree::findMin(ptrNODE p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findMin(p->left) : p;
}

ptrNODE AVLTree::findMax(ptrNODE p)
{
	return p->right ? findMax(p->right) : p;
}

ptrNODE AVLTree::findByValue(int key)
{
	ptrNODE result = nullptr;

	if (root) {
		ptrNODE p = root;
		while (p && !result) {
			if (p->key == key) {
				result = p;
			}
			else {
				if (key > p->key) p = p->right;
				else  p = p->left;
			}
		}
	}
	return result;
}

ptrNODE AVLTree::removeMin(ptrNODE p)
{
	if (p->left == 0)
		return p->right;
	p->left = removeMin(p->left);
	return bigRotationBalance(p);
}

ptrNODE AVLTree::removeMax(ptrNODE p)
{
	if (p->right == 0)
		return p->left;
	p->right = removeMax(p->right);
	return bigRotationBalance(p);
}

ptrNODE AVLTree::remove(ptrNODE p, int k)
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		ptrNODE q = p->left;
		ptrNODE r = p->right;
		delete p;
		if (!r) return q;
		ptrNODE min = findMin(r);
		min->right = removeMin(r);
		min->left = q;
		return bigRotationBalance(min);
	}
	return bigRotationBalance(p);
}


ptrNODE AVLTree::copyTree(const ptrNODE node)
{
	ptrNODE n = nullptr;
	if (node) {
		n = new NODE(node->key);
		n->right = copyTree(node->right);
		n->left = copyTree(node->left);
	}
	return n;
}

std::ostream& AVLTree::print(std::ostream& stream, ptrNODE node, int level = 0)
{
	if (node)
	{
		if (level == 0)
			stream << "root: " << node->key << '\n';
		else
		{
			stream << "lvl: " << level << " ";
			stream << "value = " << node->key << '\n';
		}
		print(stream, node->left, level + 1);
		print(stream, node->right, level + 1);
	}
	return stream;
}

std::ostream& AVLTree::printTree(std::ostream& stream)
{
	if (root) {
		print(stream, root);
	}
	else {
		stream << "Tree is empty";
	}
	return stream;
}

void AVLTree::clear(ptrNODE p)
{
	if (p) {
		clear(p->right);
		clear(p->left);
		std::cout << "Key:" << p->key << " is deleted.\n";
		delete p;
	}
}