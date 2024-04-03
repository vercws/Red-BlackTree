#include "Header.h"


template <typename T, typename Comparator1, typename Comparator2>
typename Tree<T, Comparator1, Comparator2>::Node* Tree<T, Comparator1, Comparator2>::returnSibling(Node*& node)
{
	if (node == root) return nullptr;
	else
	{
		if (node == node->parent->left) return node->parent->right;
		else return node->parent->left;
	}
}

template <typename T, typename Comparator1, typename Comparator2>
void typename Tree<T, Comparator1, Comparator2>::LeftRotation(Node* child, Node* parent)
{
	if (parent->right == nullptr) return;
	parent->right = child->left;
	if (child->left != nullptr) child->left->parent = parent;
	child->parent = parent->parent;
	if (parent->parent == nullptr) root = child;
	else if (parent == parent->parent->left) parent->parent->left = child;
	else parent->parent->right = child;

	child->left = parent;
	parent->parent = child;
	
}

template <typename T, typename Comparator1, typename Comparator2>
void typename Tree<T, Comparator1, Comparator2>::RightRotation(Node* child, Node* parent)
{ 
	if (parent->left == nullptr) return;
	parent->left = child->right;
	if (child->right != nullptr) child->right->parent = parent;
	child->parent = parent->parent; 
	if (parent->parent == nullptr) root = child;
	else if (parent == parent->parent->right) parent->parent->right = child;
	else parent->parent->left = child;

	child->right = parent;
	parent->parent = child;

}

template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::ColourCheck(Node* newElement) 
{
	while (newElement != root && newElement->parent->colour == false)
	{			
		Node* parent = newElement->parent;
		Node* grandparent = parent->parent;
		if (parent == grandparent->left) 
		{

			Node* ParentsSisBro = grandparent->right;
			// if parent's sibling/s is not NULLL nad it is red
			// change the colour and
			// check if parent's parent (granparent) is root, 
			// changer colour to black and check again
			if (ParentsSisBro != nullptr && ParentsSisBro->colour == false)
			{
				//CHange the colours of parent and parentsSibling
				parent->colour = true;
				ParentsSisBro->colour = true; 
				grandparent->colour = false; 
				newElement = grandparent;
				std::swap(newElement, grandparent);
			}

			else // If parent is an only child or is black
			{
				if (newElement == parent->right)
				{	//newElement = parent;
					LeftRotation(newElement, parent);
					std::swap(newElement, parent);
				}
				parent->colour = true;
				grandparent->colour = false;
				if (newElement->parent->parent->left != nullptr) RightRotation(newElement->parent, newElement->parent->parent);
			}
		}
		else
		{
			Node* parentsSisBro = grandparent->left;
		// if parent's sibling/s is not NULLL nad it is red
		// change the colour and
		// check if parent's parent (granparent) is root, 
		// change color to black and check again
			if (parentsSisBro != nullptr && parentsSisBro->colour == false)
			{
				//Change colours for parent and parentsSibling
				parent->colour = true;
				parentsSisBro->colour = true; 
				grandparent->colour = false; 
				newElement = grandparent;
				std::swap(newElement, grandparent);
			}
		

			else // If parent does not have siblings or they are black
			{
				if (newElement == newElement->parent->left)
				{
					RightRotation(newElement, parent);
					std::swap(newElement, parent);
				}
				parent->colour = true;
				if(grandparent->right != nullptr) grandparent->colour = false;
				if (grandparent->right != nullptr) LeftRotation(parent, grandparent);
			}
		}
	}
	root->colour = true;
	return;
}

template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::addNode(T*& data, Comparator1& comp)
{

	if (root == nullptr)
	{
		Node* newElement = new Node(data);
		root = newElement;
		root->colour = true;
		size++;
	}
	else
	{
		Node* newElement = new Node(data);
		newElement->colour = false; // red
		Node* temp = new Node();
		int index = 0;
		temp = root;
		while (temp != nullptr)
		{
			if (comp(temp->data, newElement->data)) // if temp is bigger, add on the left side
			{
				if (temp->left == nullptr)
				{
					temp->left = newElement;
					newElement->parent = temp;
					

					// if parent is red 
					ColourCheck(newElement);
					//delete
					temp = nullptr;
					size++;
				}
				else
				{
					temp = temp->left;
				}
			}
			else if (comp(temp->data, newElement->data) == false) // temp is smaller or even
			{
				/*std::cout << "Test2";*/
				if (temp->right == nullptr)
				{
					/*std::cout << "Test3";*/
					temp->right = newElement;
					newElement->parent = temp;

					ColourCheck(newElement);
					//delete temp;
					temp = nullptr;
					size++;
				}
				else
				{
					temp = temp->right;
				}

			}
		}

	}
}

template <typename T, typename Comparator1, typename Comparator2>
typename Tree<T, Comparator1, Comparator2>::Node* Tree<T, Comparator1, Comparator2>::returnNode(T*& data, Comparator1& comp, Comparator2& even)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		Node* temp = root;
		while (even(temp->data, data) == false) //if temp different from data
		{
			if (comp(temp->data, data)) // if temp bigger
			{
				if (even(temp->data, data) == false)
				{
					temp = temp->left;
				}
			}
			else if (comp(temp->data, data) == false) // temp is smaller or even
			{
				if (even(temp->data, data) == false)
				{
					temp = temp->right;
				}
			}
			if (temp == nullptr)
			{
				return nullptr;
			}
		}
		return temp;
	}
}

template <typename T, typename Comparator1, typename Comparator2>
typename Tree<T, Comparator1, Comparator2>::Node* Tree<T, Comparator1, Comparator2>::findInOrderNew(Node* node)
{
	Node* theNew = node->right;
	while (theNew->left != nullptr)
	{
		theNew = theNew->left;
	}
	return theNew;
}

template <typename T, typename Comparator1, typename Comparator2>
typename Tree<T, Comparator1, Comparator2>::Node* Tree<T, Comparator1, Comparator2>::findInOrderNewRoot(Node* node)
{
	Node* theNew = node->right;
	while (theNew->right != nullptr)
	{
		theNew = theNew->right;
	}
	return theNew;
}

template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::deleteA(Node*& node)
{
	if (node != nullptr)
	{
		deleteA(node->left);
		deleteA(node->right);

		delete node;
		node = nullptr;
	}
}

template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::deleteAll()
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty" << std::endl;
		return;
	}
	else
	{
		deleteA(root);
		root = nullptr;
		size = 0;
	}
}

template <typename T, typename Comparator1, typename Comparator2>
int Tree<T, Comparator1, Comparator2>::HeightCheck(Node*& node)
{
	if (node == nullptr)
	{
		return 0;
	}

	int heightLeft = HeightCheck(node->left);
	int heightRight = HeightCheck(node->right);

	if (heightLeft > heightRight)
	{
		return heightLeft + 1;
	}
	else
	{
		return heightRight + 1;
	}
}

template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::displayTree(Node*& node)
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty" << std::endl;
		return;
	}
	else
	{
		if (node != nullptr)
		{
			std::cout << "Parent: ";
			if (node->parent != nullptr)
			{
				std::cout << node->parent->data; // << std::endl;
			}
			else
			{
				std::cout << "Brak" << std::endl;
			}
			std::cout << "Data: " << node->data << "Colour: " << Colour(node) << std::endl << "Left child: ";
			if (node->left != nullptr)
			{
				std::cout << node->left->data;
			}
			else
			{
				std::cout << "None" << std::endl;
			}
			std::cout << "Right child: ";
			if (node->right != nullptr)
			{
				std::cout << node->right->data;
			}
			else
			{
				std::cout << "None" << std::endl;
			}
			std::cout << std::endl;
			displayTree(node->left);
			displayTree(node->right);
		}
	}
}

template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::pre_orderTraversal(Node*& node)
{
	if (node == nullptr)
	{
		return;
	}
	std::cout << node->data << " ";

	pre_orderTraversal(node->left);
	pre_orderTraversal(node->right);
}

template <typename T, typename Comparator1, typename Comparator2>
void Tree<T, Comparator1, Comparator2>::in_orderTraversal(Node*& node)
{
	if (node == nullptr)
	{
		return;
	}
	in_orderTraversal(node->left);

	std::cout << node->data << " ";

	in_orderTraversal(node->right);
}

int RandomNumber(long from, long to)
{
	std::random_device rd;
	std::default_random_engine e{ rd() };
	std::uniform_int_distribution <unsigned> u(from, to);
	return u(e);
}

void displayMenu()
{
	bool showMenu = true;
	int choice = 0;

	Tree<Data, MyCompare, IfEven> RBT;
	MyCompare comparator;
	IfEven even;

	clock_t t1 = clock();
	for (int i = 0; i < 10000; i++)
	{
		int rvalue = RandomNumber(0, 1000000);
		char rcharacter = RandomNumber(33, 126);
		Data* newData = new Data(rvalue, rcharacter);
		RBT.addNode(newData, comparator);
	}
	clock_t t2 = clock();
	double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
	std::cout << "\n\n" << time;

	do
	{

		std::cout << "----------Menu----------\n\n";
		std::cout << "1. Add a new element to the tree\n"; // done
		std::cout << "2. Return a specific element from the tree\n"; //done
		std::cout << "3. Pre-order\n"; //done
		std::cout << "4. In-order\n"; //done
		std::cout << "5. Delete all elements\n"; //done
		std::cout << "6. Return the height of the tree\n"; //done
		std::cout << "7. Display the tree\n"; //done
		std::cout << "8. Close the program\n";
		std::cout << " \n\n";
		std::cout << "Choose the option: ";
		std::cin >> choice;
		system("cls");

		switch (choice)
		{
		case 1:
		{
			Data* newData1 = new Data(10, 43);
			RBT.addNode(newData1, comparator);
			Data* newData2 = new Data(18, 103);
			RBT.addNode(newData2, comparator);
			Data* newData3 = new Data(7, 77);
			RBT.addNode(newData3, comparator);
			Data* newData4 = new Data(15, 107);
			RBT.addNode(newData4, comparator);;
			Data* newData6 = new Data(16, 66);
			RBT.addNode(newData6, comparator);
			break;
		}
		case 2:
		{
			int envalue = 0;
			char encharacter;
			std::cout << "Enter the value: ";
			std::cin >> envalue;
			std::cout << "Enter the character: ";
			std::cin >> encharacter;
			Data* enData = new Data(envalue, encharacter);

			clock_t t1 = clock();
			if (RBT.returnNode(enData, comparator, even) != nullptr)
			{
				std::cout << RBT.returnNode(enData, comparator, even)->data << std::endl;
			}
			else
			{
				std::cout << "Cannot find such node..." << std::endl;
			}
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "\n\n" << time;
			break;
		}
		case 3:
		{
			clock_t t1 = clock();
			RBT.pre_orderTraversal(RBT.root);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "\n\n" << time;
			break;
		}
		case 4:
		{
			clock_t t1 = clock();
			RBT.in_orderTraversal(RBT.root);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "\n\n" << time;
			break;
		}
		case 5:
		{
			clock_t t1 = clock();
			RBT.deleteAll();
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "\n\n" << time;
			break;
		}
		case 6:
		{
			clock_t t1 = clock();
			int height = RBT.HeightCheck(RBT.root);
			std::cout << height;
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "\n\n" << time;
			break;
		}
		case 7:
		{
			std::cout << "Black-red Tree" << std::endl;
			RBT.displayTree(RBT.root);
			break;
		}

		case 8:
			showMenu = false;
			break;
		default:
			std::cout << "Error!\n\n";
		}
	} while (showMenu);
}


int main()
{
	setlocale(LC_ALL, "");
	displayMenu();
	return 0;
}