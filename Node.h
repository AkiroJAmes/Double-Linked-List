#pragma once
class Node
{
public:
	Node(int value);
	~Node();

	int GetData() { return data; }
	Node* GetNext() { return next; }
	Node* GetPrevious() { return previous; }

	bool HasNext() { return next != nullptr; }
	bool HasPrevious() { return previous != nullptr; }

	void SetData(int value) { data = value; }
	void SetNext(Node* value) { next = value; }
	void SetPrevious(Node* value) { previous = value; }

	void Draw(int x, int y, bool selected = false);

private:
	int data;

	// Node children
	Node* next;
	Node* previous;
};

