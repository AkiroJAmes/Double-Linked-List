#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "DoubleLinkedList.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    srand(time(NULL));

    DoubleLinkedList m_doubleLinkedList;
    Node* m_selectedNode = nullptr;

    int insertValueBoxValue = (rand() % 100) + 1;
    bool insertValueBoxEditMode = false;
    float offset = 50;

    int posValueBoxValue = 0;
    bool posValueBoxEditMode = false;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);

        // First column UI
        if (GuiValueBox(Rectangle{ 75, 25, 125, 30 }, NULL, &insertValueBoxValue, 0, 100, insertValueBoxEditMode)) insertValueBoxEditMode = !insertValueBoxEditMode;
        if (GuiButton(Rectangle{ 75, 60, 125, 30 }, GuiIconText(RICON_REPEAT, "Sort"))) m_doubleLinkedList.SortList();
        if (GuiButton(Rectangle{ 75, 95, 125, 30 }, GuiIconText(RICON_BIN, "Remove all"))) m_doubleLinkedList.RemoveAll();

        // Second column UI
        GuiDrawRectangle({ 205, 25, 125, 30 }, 1, GRAY, RAYWHITE);
        GuiDrawText("Front", { 205, 25, 125, 30 }, 1, GRAY);

        if (GuiButton(Rectangle{ 205, 60, 125, 30 }, GuiIconText(RICON_FILE_SAVE, "Insert"))) {
            // Limit list size so it doesn't go offscreen
            if (m_doubleLinkedList.Count() < 14) {
                m_doubleLinkedList.InsertFront(insertValueBoxValue);
                insertValueBoxValue = (rand() % 100) + 1;
            }
        }

        if (GuiButton(Rectangle{ 205, 95, 125, 30 }, GuiIconText(RICON_BIN, "Remove"))) m_doubleLinkedList.RemoveFront();


        // Third column UI
        GuiDrawRectangle({ 335, 25, 125, 30 }, 1, GRAY, RAYWHITE);
        GuiDrawText("End", { 335, 25, 125, 30 }, 1, GRAY);

        if (GuiButton(Rectangle{ 335, 60, 125, 30 }, GuiIconText(RICON_FILE_SAVE, "Insert"))) {
            // Limit list size so it doesn't go offscreen
            if (m_doubleLinkedList.Count() < 14) { 
                m_doubleLinkedList.InsertEnd(insertValueBoxValue);
                insertValueBoxValue = (rand() % 100) + 1;
            }
        }

        if (GuiButton(Rectangle{ 335, 95, 125, 30 }, GuiIconText(RICON_BIN, "Remove"))) m_doubleLinkedList.RemoveEnd();


        // Fourth column UI
        if (GuiValueBox(Rectangle{ 465, 25, 125, 30 }, NULL, &posValueBoxValue, (m_doubleLinkedList.Count() == 0) ? 0 : 1, m_doubleLinkedList.Count(), posValueBoxEditMode)) posValueBoxEditMode = !posValueBoxEditMode;

        if (GuiButton(Rectangle{ 465, 60, 125, 30 }, GuiIconText(RICON_FILE_SAVE, "Insert"))) {
            // Limit list size so it doesn't go offscreen
            if (m_doubleLinkedList.Count() < 14) {
                m_doubleLinkedList.InsertAt(insertValueBoxValue, posValueBoxValue);
                insertValueBoxValue = (rand() % 100) + 1;
            }
        }

        if (GuiButton(Rectangle{ 465, 95, 125, 30 }, GuiIconText(RICON_BIN, "Remove"))) m_doubleLinkedList.RemoveAt(posValueBoxValue);


        // Fifth column UI
        GuiDrawRectangle({ 595, 25, 125, 30 }, 1, GRAY, RAYWHITE);
        GuiDrawText(GuiIconText(RICON_INFO, "List Info"), { 595, 25, 125, 30 }, 1, GRAY);

        std::string empty, count, sorted, firstLast, isSorted, isEmpty;
        isEmpty = m_doubleLinkedList.IsEmpty() ? "False" : "True";
        isSorted = m_doubleLinkedList.IsSorted() ? "True" : "False";
        empty = "Is Empty? : " + isEmpty;
        count = "Node Count : " + std::to_string(m_doubleLinkedList.Count());
        sorted = "Is Sorted? : " + isSorted;
        firstLast = "First: " + (m_doubleLinkedList.GetFirstNode() != nullptr ? std::to_string(m_doubleLinkedList.GetFirstNode()->GetData()) : "-")
            + "  Last : " + (m_doubleLinkedList.GetLastNode() != nullptr ? std::to_string(m_doubleLinkedList.GetLastNode()->GetData()) : "-");

        GuiDrawRectangle({ 595, 54, 125, 71 }, 1, GRAY, RAYWHITE);
        GuiDrawText(empty.c_str(), { 595, 56, 125, 24 }, 1, GRAY);
        GuiDrawText(sorted.c_str(), { 595, 64, 125, 38 }, 1, GRAY);
        GuiDrawText(count.c_str(), { 595, 72, 125, 52 }, 1, GRAY);
        GuiDrawText(firstLast.c_str(), { 595, 80, 125, 66 }, 1, GRAY);


        // Draw the nodes
        m_doubleLinkedList.Draw(m_selectedNode);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}