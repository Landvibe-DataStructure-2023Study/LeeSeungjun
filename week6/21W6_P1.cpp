#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
	Node* parent;
	vector<Node*> childList;
	int value;

	Node(Node* parent, int value)
	{
		this->parent = parent;
		this->value = value;
	}
};

class Tree
{
public:
	Node* root;
	vector<Node*> nodeList;

	Tree()
	{
		root = new Node(nullptr, 1);
		nodeList.push_back(root);
	}
	Node* findNode(int v)
	{
		for (int i{ 0 }; i < nodeList.size(); i++)
		{
			if (nodeList[i]->value == v)
				return nodeList[i];
		}
		return nullptr;
	}
	void insertNode(int x, int y)
	{
		Node* parentNode = findNode(x);
		if (parentNode == nullptr)
			cout << "-1\n";
		else
		{
			Node* newNode = new Node(parentNode, y);
			parentNode->childList.push_back(newNode);
			nodeList.push_back(newNode);
		}
	}
	void deleteNode(int x)
	{
		Node* deleteNode = findNode(x);

		if (deleteNode == root || deleteNode == nullptr)
		{
			cout << "-1\n";
			return;
		}
		else
		{
			for (int i{ 0 }; i < deleteNode->childList.size(); i++)
			{
				deleteNode->parent->childList.push_back(deleteNode->childList[i]);
				deleteNode->childList[i]->parent = deleteNode->parent;
			}

			for (int i{ 0 }; i < deleteNode->parent->childList.size(); i++)
			{
				if (deleteNode == deleteNode->parent->childList[i])
				{
					deleteNode->parent->childList.erase(deleteNode->parent->childList.begin() + i);
					break;
				}
			}

			for (int i{ 0 }; i < nodeList.size(); i++)
			{
				if (nodeList[i] == deleteNode)
				{
					nodeList.erase(nodeList.begin() + i);
					break;
				}
			}

			delete deleteNode;
		}
	}
	void printChild(int x)
	{
		Node* targetNode = findNode(x);
		if (targetNode->childList.size() == 0 || targetNode == nullptr)
			cout << "-1\n";
		else
		{
			for (int i{ 0 }; i < targetNode->childList.size(); i++)
			{
				cout << targetNode->childList[i]->value << ' ';
			}
			cout << '\n';
		}
	}
};

int main()
{
	Tree t = Tree();
	int test;
	cin >> test;
	while (test--)
	{
		string s;
		cin >> s;
		if (s == "insert")
		{
			int x, y;
			cin >> x >> y;
			t.insertNode(x, y);
		}
		else if (s == "print")
		{
			int x;
			cin >> x;
			t.printChild(x);
		}
		else if (s == "delete")
		{
			int x;
			cin >> x;
			t.deleteNode(x);
		}
	}
}