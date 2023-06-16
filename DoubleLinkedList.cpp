#include "DoubleLinkedList.h"
#include "raylib.h"
#include <iostream>
#include <vector>

DoubleLinkedList::DoubleLinkedList() : root(nullptr)
{

}

DoubleLinkedList::~DoubleLinkedList() {

}

int DoubleLinkedList::Count() {
	Node* nCurrent = root;
	int count = 0;

	// Iterate through from the root to end to find count
	while (true) {
		if (nCurrent == nullptr) 
			return count;

		nCurrent = nCurrent->GetNext();
		count++;
	}
}

void DoubleLinkedList::InsertFront(int value) {
	Node* nCurrent = root;
	Node* nNewNode = new Node(value);

	if (IsEmpty()) {
		std::cout << "Inserting to front." << std::endl;
		
		// Update pointers
		nCurrent->SetPrevious(nNewNode);
		nNewNode->SetNext(nCurrent);
		root = nNewNode;
	}
	else { // Set root node if list is empty
		InsertRootNode(nNewNode);
	}
}

void DoubleLinkedList::InsertEnd(int value) {
	Node* nCurrent = GetLastNode();
	Node* nNewNode = new Node(value);

	if (IsEmpty()) {
		std::cout << "Inserting to end" << std::endl;

		// Update pointers
		nCurrent->SetNext(nNewNode);
		nNewNode->SetPrevious(nCurrent);
	}
	else { // Set root node if list is empty
		InsertRootNode(nNewNode);
	}
}

void DoubleLinkedList::InsertAt(int value, int pos) {
	Node* nCurrent = GetNodeAt(pos);
	Node* nNewNode = new Node(value);
	
	if (IsEmpty()) {
		std::cout << "Inserting at " << pos << "." << std::endl;

		// Update pointers
		nNewNode->SetNext(nCurrent);
		nNewNode->SetPrevious(nCurrent->GetPrevious());
		if(nCurrent->HasPrevious())
			nCurrent->GetPrevious()->SetNext(nNewNode);
		nCurrent->SetPrevious(nNewNode);

		// Set the root to current to avoid not inserting at count 1
		if (root == nCurrent)
			root = nNewNode;
	}
	else { // Set root node if list is empty
		InsertRootNode(nNewNode);
	}
}

void DoubleLinkedList::InsertRootNode(Node* node) {
	std::cout << "Inserting root node." << std::endl;
	root = node;
}

void DoubleLinkedList::RemoveFront() {
	Node* nCurrent = root;
	Node* nNext = nullptr;

	if (nCurrent) {
		std::cout << "Removing front node." << std::endl;

		// Update pointers
		nNext = nCurrent->GetNext();
		if (nNext) nNext->SetPrevious(nullptr);
		root = nNext;
	}
}

void DoubleLinkedList::RemoveEnd() {
	Node* nCurrent = GetLastNode();
	Node* nPrevious = nullptr;

	if (nCurrent) {
		std::cout << "Removing end node." << std::endl;

		// Update pointers
		nPrevious = nCurrent->GetPrevious();
		if (nPrevious) nPrevious->SetNext(nullptr);
		nCurrent = nPrevious;

		// Set root to null when the last is removed
		if (!nCurrent) root = nCurrent;
	}
}

void DoubleLinkedList::RemoveAt(int pos) {
	Node* nCurrent = GetNodeAt(pos);
	Node* nNext = nullptr;
	Node* nPrevious = nullptr;

	if (nCurrent) {
		std::cout << "Removing at " << pos << "." << std::endl;

		// Update pointers
		nPrevious = nCurrent->GetPrevious();
		nNext = nCurrent->GetNext();

		if (nPrevious) nPrevious->SetNext(nNext);
		if (nNext) nNext->SetPrevious(nPrevious);

		if (nCurrent == root)
			root = nNext;

		nCurrent = nullptr;
	}
}

void DoubleLinkedList::RemoveAll() {
	Node* nCurrent = root;

	std::cout << "Removing all nodes." << std::endl;

	// Iterate through from root 
	while (nCurrent) {
		Node* nNext = nCurrent->GetNext();
		if(nNext) nNext->SetPrevious(nullptr);
		root = nNext;
		nCurrent = root;
	}
}

Node* DoubleLinkedList::GetNodeAt(int index) {
	if (index > Count()) return nullptr;

	Node* nCurrent = root;

	// Iterate through nodes to find node[index]
	if (nCurrent) {
		for (int i = 0; i < index - 1; i++) {
			nCurrent = nCurrent->GetNext();
		}
	}

	return nCurrent;
}

Node* DoubleLinkedList::GetFirstNode() {
	// Simple, just return root
	return root;
}

Node* DoubleLinkedList::GetLastNode() {
	// Return node at last position
	return GetNodeAt(Count());
}

void DoubleLinkedList::SortList() {
	int temp;
	Node *nCurrent = nullptr, *nNext = nullptr;

	if (IsEmpty()) {
		std::cout << "Sorting nodes." << std::endl;

		// Start at root and iterate to next node
		for (nCurrent = root; nCurrent->HasNext(); nCurrent = nCurrent->GetNext()) {
			// Loop as long as nNext is not null
			for (nNext = nCurrent->GetNext(); nNext; nNext = nNext->GetNext()) {
				// Swap data
				if (nCurrent->GetData() > nNext->GetData()) {
					temp = nCurrent->GetData();
					nCurrent->SetData(nNext->GetData());
					nNext->SetData(temp);
				}
			}
		}
	}
}

bool DoubleLinkedList::IsSorted() {
	Node* nCurrent = nullptr, * nNext = nullptr;

	if (IsEmpty()) {
		// Start at root and iterate to next node
		for (nCurrent = root; nCurrent->HasNext(); nCurrent = nCurrent->GetNext()) {
			// Loop as long as nNext is not null
			for (nNext = nCurrent->GetNext(); nNext; nNext = nNext->GetNext()) {
				if (nCurrent->GetData() > nNext->GetData()) {
					return false;
				}
			}
		}
	}

	return true;
}

void DoubleLinkedList::Draw(Node* selected) {
	int size = Count();

	Draw(root, (GetScreenWidth() / 2) - (25 * size), GetScreenHeight() / 2, selected);
}

void DoubleLinkedList::Draw(Node* nCurrent, int x, int y, Node* selected) {
	if (nCurrent) {
		if (nCurrent->HasNext()) {
			DrawLine(x + 40, y + 20, x + 50, y + 20, RED);
			Draw(nCurrent->GetNext(), x + 50, y, selected);
		}

		// Draw null box and first text indicator
		if (nCurrent == GetFirstNode()) {
			DrawLine(x, y + 20 , x - 10, y + 20, RED);
			DrawRectangle(x -40, y + 5, 30, 30, BLUE);
			DrawRectangleLines(x - 40, y + 5, 30, 30, DARKBLUE);
			DrawText("NULL", x - 37, y + 15, 10, BLACK);

			DrawText("FIRST", x + 5, y - 25, 10, BLACK);
		}

		// Draw null box and last text indicator
		if (nCurrent == GetLastNode()) {
			DrawLine(x + 40, y + 20, x + 50, y + 20, RED);
			DrawRectangle(x + 50, y + 5, 30, 30, BLUE);
			DrawRectangleLines(x + 50, y + 5, 30, 30, DARKBLUE);
			DrawText("NULL", x + 53, y + 15, 10, BLACK);

			DrawText("LAST", x + 8, y + 55, 10, BLACK);
		}

		// Draw nodes
		nCurrent->Draw(x, y, (selected == nCurrent));
	}
}
