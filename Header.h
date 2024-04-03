#include <random>
#include <iostream>
#include <string>

template<typename T, typename Comparator1, typename Comparator2>
class Tree
{
public:
	class Node
	{
	public:
		Node(T*& newData) //root
		{
			data = newData;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			colour = false;
		}
		Node()
		{
			data = nullptr;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			colour = false;

		}
		Node* parent;
		Node* left;
		Node* right;
		T* data;
		bool colour;
	};
	Node* root = nullptr;
	int size = 0;

	std::string Colour(Node*& node);
	void addNode(T*& data, Comparator1& comp);
	Node* returnNode(T*& data, Comparator1& comp, Comparator2& even);
	void pre_orderTraversal(Node*& node);
	void in_orderTraversal(Node*& node);
	void deleteAll();
	void deleteA(Node*& node);
	int HeightCheck(Node*& node);
	void displayTree(Node*& node);
	Node* findInOrderNew(Node* node);
	Node* findInOrderNewRoot(Node* node);

	Node* returnSibling(Node*& node);

	void RightRotation(Node* child, Node* parent); 
	void LeftRotation(Node* child, Node* parent);
	void ColourCheck(Node* node);
};

class Data
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Data* data)
	{
		os << data->value << ", ";
		os << data->character << "\n";
		return os;
	}
	Data(int val, char ch)
	{
		value = val;
		character = ch;
	};
	int value;
	char character;
};


class MyCompare //czy pierwsze jest wiêksze od drugiego
{
public:
	bool operator()(const Data* d1, const Data* d2) const
	{
		if (d1->value > d2->value)
		{
			return true;
		}
		else if (d1->value == d2->value && d1->character > d2->character)
		{
			return true;
		}
		else {
			return false;
		}

	}
};

class IfEven
{
public:
	bool operator()(const Data* d1, const Data* d2) const
	{
		if (d1->value == d2->value && d1->character == d2->character)
		{
			return true;
		}
		else
			return false;
	}
};


template <typename T, typename Comparator1, typename Comparator2>
std::string Tree<T, Comparator1, Comparator2>::Colour(Node*& node)
{
	if (node->colour == true)
	{
		return "Black";
	}
	else
		return "Red";

}