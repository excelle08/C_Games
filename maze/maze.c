/*
	A simple Maze game on POSIX-Compatible OS console.
	-----------Program structure---------------------
	1.Read the map file(./map) and load the maze(15x20)
	2.Draw the main character
	3.Listen keyboard input and determine movement
	4.Check if the route is valid(Not approaching the wall).
		- Method: If the next coordinate is wall in the matrix, stop moving.
	5.Move the charachter
	6.Check if the character has successfully gone out.
	-----------Operation-----------------------------
	W - Up              D - Right
	S - Down            A - Left
	Q - Exit
	-----------Map file format-----------------------
	'.'(dot) for space and '/'(slash) for wall and '!' for exit
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../inc/console.h"

#define SPACE '.'
#define WALL '#'

bool maze[15][20];
int x = 0;
int y = 0;
int sucX, sucY;

void initMaze(void);
void draw(char myself, int x, int y);
void move(char key, char myself);
bool checkFile(FILE *fp);

int main(int argc, char const *argv[])
{
	clearScreen();
	initMaze();
	char in;
	while(in = getch()){
		move(in, '*');
		if(x==14 && y==19){
			moveCursor(16, 0);
			printf("Success!\n");
			break;
		}
	}
	return 0;
}

void initMaze(void){
	FILE * fp;
	if((fp=fopen("map", "rb")) == NULL){
		printf("An error occurred when opening the map.\n");
		exit(-1);
	}
	if(!checkFile(fp)){
		printf("Invalid map file.\n");
		exit(-2);
	}
	rewind(fp);
	for(int i=0; i<15; i++){
		for(int j=0; j<20; j++){
			char c;
			fread(&c, 1, 1, fp);
			maze[i][j] = (c == '.')?false:true;
			if(c == '!'){
				sucX = i;
				sucY = j;
				maze[i][j] = false;
			}
		}
	}
	draw('*', 0, 0);
	moveCursor(0, 0);
}

bool checkFile(FILE *fp)
{
	int size=0;
	char buf;
	while(!feof(fp)){
		fread(&buf,1,1,fp);
		if((buf != '.') && (buf != '/') && (buf != '!')){
			printf("Meet illegal char %c at %d\n", buf, size);
			return false;
		}
		size ++;
	}
	if(size-1 != 300){
		printf("Size = %d\n", size);
		return false;
	}
	return true;
}

void draw(char myself, int x, int y){
	moveCursor(0, 0);
	for(int i=0; i<15; i++){
		for(int j=0; j<20; j++){
			if(i==x & j==y){
				putchar(myself);
			} else {
				if(i == sucX && j == sucY){
					putchar('!');
				} else{
					putchar((maze[i][j])?WALL:SPACE);

				}
			}
		}
		putchar('\n');
	}
}

void move(char key, char myself){
	switch(key){
		case 'w':
		case 'W':
		case UP:
		if(x>0 && !maze[x-1][y]){
			clearScreen();
			draw(myself, --x, y);
		}
		break;

		case 's':
		case 'S':
		case DOWN:
		if(x<15 && !maze[x+1][y]){
			clearScreen();
			draw(myself, ++x, y);
		}
		break;

		case 'a':
		case 'A':
		case LEFT:
		if(y>0 && !maze[x][y-1]){
			clearScreen();
			draw(myself, x, --y);
		}
		break;

		case 'd':
		case 'D':
		case RIGHT:
		if(y<20 && !maze[x][y+1]){
			clearScreen();
			draw(myself, x, ++y);
		}
		break;

		case 'Q':
		case 'q':
		exit(0);

		default:
		break;
	}
}