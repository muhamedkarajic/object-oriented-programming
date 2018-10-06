#include <iostream>

using namespace std;
const char* crt = "\n--------------------\n";

class Node
{
private:
	int _data;
	Node *_next;
public:
	int getData() const { return _data; }
	Node *getNext() const { return _next; }

	void setData(const int &data) { _data = data; }
	void setNext(Node *next) { _next = next; }

	Node(int data, Node *next = nullptr)
	{
		_data = data;
		_next = next;
	}

	Node(const Node &node)
	{
		_data = node._data;
		_next = node._next;
	}
	
	Node()
	{
		_data = 0;
		_next = nullptr;
	}
	
	~Node() { delete _next; }

	friend ostream &operator<<(ostream &COUT, const Node &node)
	{
		COUT << "Data: " << node.getData() << endl;
		COUT << "Next: " << node.getNext() << endl;
		return COUT;
	}
	void operator=(const Node& node)
	{
		_data = node._data;
		_next = node._next;
	}
};

class LinkedList
{
private:
	Node *_nodes;
public:
	friend ostream &operator<<(ostream &COUT, const LinkedList &list)
	{
		if (list._nodes == nullptr)
			return COUT;

		Node *temp = list._nodes;

		COUT << *temp << endl;
		while (temp->getNext() != nullptr)
		{
			temp = temp->getNext();
			COUT << *temp << endl;
		}
		return COUT;
	}

	void operator-=(const int &lokacija)
	{
		Node *temp = _nodes;

		Node *spasi = nullptr;
		if (lokacija == 0)
		{
			Node *n = _nodes->getNext();
			delete temp;
			_nodes = n;
			return;
		}
		else if (lokacija < 0)
			return;

		int brojac = 0;
		while (temp != nullptr)
		{
			if (++brojac == lokacija)
			{
				if (temp->getNext() != nullptr)
				{
					spasi = temp->getNext();
					Node *poslje = temp->getNext()->getNext();
					temp->setNext(poslje);

					spasi->setNext(nullptr);
					delete spasi->getNext();
					return;
				}
				return;
			}
			temp = temp->getNext();
		}
	}

	void operator+=(const int &data)
	{
		Node *temp = new Node;
		temp->setData(data);
		temp->setNext(_nodes);

		_nodes = temp;
	}

	Node *getNodes() const { return _nodes; }

	LinkedList() { _nodes = nullptr; }
	~LinkedList() { delete _nodes; }
};


void main()
{
	LinkedList lista;
	lista += 4;
	lista += 3;
	lista += 2;
	lista += 1;
	lista += 0;

	cout << lista << crt;
	lista -= 2;
	cout << lista << crt;

	system("PAUSE>0");
}