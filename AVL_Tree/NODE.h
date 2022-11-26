
struct NODE
{
	int key;
	NODE* left, * right;
	int height;
	NODE() : left(nullptr), right(nullptr), key(0), height(1) {};
	NODE(int _key) : left(0), right(0), key(_key), height(1) {};
	~NODE()
	{
		left = nullptr;
		right = nullptr;
	};
};

using ptrNODE = NODE*;