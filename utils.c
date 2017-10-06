
#include <windows.h>
#include <string.h>
#include <stdlib.h>

void gotoxy(int x, int y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) {x - 1, y - 1});
}

void clearScreen() {
    system("cls");
}

void textColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void backgroundColor(int color) {
    system("color 3F");
}

void setWindowSize(char *windowSize) {
    char command[20] = "mode ";

    strcat(command, windowSize);
    system(command);
}

void setWindowTitle(char *title) {
    SetConsoleTitleA((LPCSTR) {title});
}
