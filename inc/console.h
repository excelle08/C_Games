/*
	console.h
	This header file includes functions that control the console on both Windows and POSIX.
	Functions:
	char getch(void) 				- Get a keyboard input without pressing ENTER
	void clearScreen(void) 			- Refresh the console
	void moveCursor(int x,int y) 	- Move the cursor to line(x), col(y). 
*/

void moveCursor(int x, int y);
void clearScreen(void);

//Acheive compatibility on Windows and POSIX-compatible OS
#ifdef _WIN32
	#include <conio.h>
	#include <windows.h>
	#define getch() _getch()
	void clearScreen(void){
		system("cls");
	}
	void moveCursor(int x, int y)
	{
		COORD pos;
		pos.X = x - 1;
		pos.Y = y - 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	}

#else
	#include "key.h"
	//About UNIX-console cursor movement: http://tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
	//Payload: "\033[<L>;<C>H", L=line, C=col
	void moveCursor(int x, int y){
		printf("\033[%d;%dH", x,y);
	}
	void clearScreen(void){
		printf("\033[2J");
	}
#endif

//Arrow keys..
#define LEFT	37	
#define RIGHT	39
#define UP		38
#define DOWN	40
