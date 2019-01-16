#include "stdafx.h"
#include "iostream"
#include "conio.h"
#include "utility"
#include "iterator"

using namespace std;

class myTree
{

private:
	struct  node
	{
		int data;
		struct  node *right;
		struct  node *left;
		struct  node *parent;
	};
	struct  node *p, *start, *ende, *q;
	int counter;
	int i;

	// preorder method
	int preorder(node* n)
	{
		preorder(n->right);
		preorder(n->left);
		i++;
		return n->data;
	}

	// bubble_sort method
	int * bubble_sort(int intArr[], int n){
	int i, j, t;
	for(i = n - 2 ; i >= 0 ; i--)
		for(j = 0 ; j <= i ; j++)
			if(intArr[j] > intArr[j + 1])
			{
				t = intArr[j];
				intArr[j] = intArr[j + 1];
				intArr[j + 1] = t;
			}

		return intArr;
	}

public:
	myTree();
	~myTree();
	bool insert(int number);
	void clear();
	node* begin();
	node* end();
	int cbegin();
	int cend();
	void balance();
	node* find(int number);
	bool is_empty();
	int get_counter();
	
};

// constructor Class
myTree::myTree()
{
	// initialized
	p = start = (struct node*)malloc(sizeof(node));
	start->data		= NULL;
	start->right	= nullptr;
	start->left		= nullptr;
	start->parent	= nullptr;

	counter			= 0;
}

// destructor Class
myTree::~myTree()
{
	free(p);
	free(start);
	free(q);
	free(ende);
}

// insert method
bool myTree::insert(int number)
{
	if(start->data == NULL)
	{
		start->data = number;
		counter++;
		return true;
	}
	else
	{
		if(start->left == nullptr && start->right == nullptr && start->data == number)
			return false;

		p = begin();

		while (true)
		{
			q = p;
			if(p->data < number)
			{
				if(p->right != nullptr)
					p = p->right;
				else
				{
					p->right = (struct node*)malloc(sizeof(node));
					break;
				}
				
			}
			else if(p->data > number)
			{
				if(p->left != nullptr)
					p = p->left;
				else
				{
					p->left = (struct node*)malloc(sizeof(node));
					break;
				}
			}
			else
				return false;
		}

		p->data		= number;
		p->parent	= q;
		p->left		= nullptr;
		p->right	= nullptr;
		ende		= p;
		counter++;
		return true;
	}
}

// clear method
void myTree::clear()
{
	free(p);
	free(start);
	free(ende);
	free(q);
	p = start = q = NULL;
	p = start = (struct node*)malloc(sizeof(node));
	start->data		= NULL;
	start->right	= nullptr;
	start->left		= nullptr;
	start->parent	= nullptr;

	counter			= 0;
}

// begin method
myTree::node* myTree::begin()
{
	return start;
}

// end method
myTree::node* myTree::end()
{
	return ende;
}

// cbegin method
int myTree::cbegin()
{
	return start->data;
}

// cend method
int myTree::cend()
{
	return ende->data;
}

// balance method
void myTree::balance()
{
	p = begin();
	int node_count = get_counter();
	if(node_count < 4)
		return;

	int *arr;
	arr = new (nothrow) int[node_count];
	if (arr == nullptr)
		return;
	else
	{
		i = 0;
		arr[i] = p->data;
		arr[i] = preorder(p);
		arr = bubble_sort(arr, i);
		clear();
		int main_parent = arr[i/2];
		insert(main_parent);

		for (int j = 0; j < i; j++)
		{
			if(main_parent==arr[j])
				continue;
			else
				insert(arr[j]);
		}
	}

	delete[] arr;
	return;
}

// find method
myTree::node* myTree::find(int number)
{
	p = begin();

	if(p->data == number)
		return p;

	while (true)
	{
		if(p->data < number)
		{
			if(p->right != nullptr)
				p = p->right;
			else
				return nullptr;
		}
		else if(p->data > number)
		{
			if(p->left != nullptr)
				p = p->right;
			else
				return nullptr;
		}
		else
			return p;
	}

	return nullptr;
}

// is_empty method
bool myTree::is_empty()
{
	if(start->data == NULL)
		return true;
	else
		return false;
}

// get_counter method
int myTree::get_counter()
{
	return counter;
}