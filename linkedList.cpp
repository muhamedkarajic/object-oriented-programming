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

	void operator-=(const int &location)
	{
		Node *current = _nodes;
		Node *saved = nullptr;

		if (location == 0)
		{
			_nodes = _nodes->getNext();
			current->setNext(nullptr);
			delete current;
			return;
		}
		else if (location < 0)
			return;

		int brojac = 0;
		while (current != nullptr)
		{
			if (++brojac == location)
			{
				if (current->getNext() != nullptr)
				{
					saved = current->getNext();
					
					Node *after = saved->getNext();
					saved->setNext(nullptr);
					current->setNext(after);

					delete saved;
					saved = nullptr;
					return;
				}
				return;
			}
			current = current->getNext();
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
	LinkedList list;
	list += 4;
	list += 3;
	list += 2;
	list += 1;
	list += 0;

	cout << list << crt;
	list -= 2;
	cout << list << crt;

	system("PAUSE>0");
}