#pragma once
#include "Node.h"

class DoubleLinkedList
{
public:
	DoubleLinkedList();
	~DoubleLinkedList();

	bool IsEmpty() { return root != nullptr; }
	int Count();

	void InsertFront(int value);
	void InsertEnd(int value);
	void InsertAt(int value, int pos);

	void RemoveFront();
	void RemoveEnd();
	void RemoveAt(int pos);
	void RemoveAll();

	Node* GetNodeAt(int index);
	Node* GetFirstNode();
	Node* GetLastNode();

	void SortList();
	bool IsSorted();

	void Draw(Node* selected = nullptr);

private:
	Node* root;

	void Draw(Node* current, int x, int y, Node* selected);
	void InsertRootNode(Node* node);
};

