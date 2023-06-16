#include "Node.h"
#include "raylib.h"
#include <string>

Node::Node(int value) : data(value), next(nullptr), previous(nullptr)
{

}

Node::~Node() { }

void Node::Draw(int x, int y, bool selected) {
	static char buffer[10];
	int count = 0;
	int number = data;
	int offset = 0;

	sprintf(buffer, "%d", data);

	// Offset value calc
	// Completely unnecessary but for my sanity

	while (number != 0) {
		number /= 10;
		count++;
	}

	if (count == 2) offset = 6;
	if (count == 3) offset = 9;

	DrawRectangle(x, y, 40, 40, WHITE);
	DrawRectangleLines(x, y, 40, 40, GRAY);
	DrawText(buffer, x + 15 - offset, y + 10, 20, RED);
}
