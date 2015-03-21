/*
	A box-pushing game.
	-----------Program structure---------------------
	1.Read the map file(./map) and load the map(15x20)
	2.Draw the main character
	3.Draw the box(2x2 in size)
	3.Listen keyboard input and determine movement
	4.Check if the route is valid(Not approaching the wall).
		- Method: If the next coordinate is wall in the matrix, stop moving.
	5.Move the box and character
	6.Check if the box has successfully gone out.
	-----------Operation-----------------------------
	W - Up              D - Right
	S - Down            A - Left
	Q - Exit
	-----------Map file format-----------------------
	'.'(dot) for space and '/'(slash) for wall and '!' for exit
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../inc/console.h"

#define SPACE '.'
#define WALL '#'
#define BOX '$'

int maze[15][20];
int sucX, sucY;
int myX=0, myY=0;
int boxX=1, boxY=1;

void initMaze(void);
bool checkFile(FILE *fp);
void draw(char myself, int x_me, int y_me, int x_box, int y_box);
void move(char key, char myself);

int main(int argc, char const *argv[])
{
	initMaze();
	while(1){
		char key = getch();
		if(key == 'Q' || key == 'q'){
			break;
		} else {
			move(key, '*');
		}
		if(boxX + 1 == sucX && boxY + 1 == sucY){
			moveCursor(16, 0);
			printf("Success!\n");
			break;
		}
	}
	return 0;
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
	fclose(fp);
	draw('*', 0, 0, 1, 1);
	moveCursor(0, 0);
}

void draw(char myself, int x_me, int y_me, int x_box, int y_box){
	moveCursor(0, 0);
	for(int i=0; i<15; i++){
		for(int j=0; j<20; j++){
			if(i==x_me && j==y_me){
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
	//Draw the box
	moveCursor(x_box+1, y_box+1);
	putchar(BOX);
	putchar(BOX);
	moveCursor(x_box+2, y_box+1);
	putchar(BOX);
	putchar(BOX);
}

void move(char key, char myself){
	switch(key){
		case 'w':   //Up
		case 'W':
		if(myX>0 && !maze[myX-1][myY]){    // Check if toward the wall
			if( (myX - 1 == (boxX + 1)) && (myY == boxY || myY == boxY+1) ){   							//Check if the character is pushing the box
				if( (boxX > 0) && !maze[boxX - 1][boxY] && !maze[boxX - 1][boxY + 1] ){					//Check if the box is toward the wall.
					clearScreen();
					draw(myself, --myX, myY, --boxX, boxY);
				}
			} else {
				draw(myself, --myX, myY, boxX, boxY);
			}
		}
		break;

		case 'a':   //Left
		case 'A':
		if(myY>0 && !maze[myX][myY-1]){    // Check if toward the wall
			if( (myY - 1 == (boxY + 1)) && (myX == boxX || myX == boxX+1) ){   						
				if( (boxY > 0) && !maze[boxX][boxY-1] && !maze[boxX+1][boxY-1] ){					
					clearScreen();
					draw(myself, myX, --myY, boxX, --boxY);
				}
			} else {
				draw(myself, myX, --myY, boxX, boxY);
			}
		}

		break;

		case 'S':   //Down
		case 's':
		if(myX<15 && !maze[myX+1][myY]){   
			if( (myX + 1 == (boxX)) && (myY == boxY || myY == boxY+1) ){   						
				if( (boxX < 14) && !maze[boxX + 2][boxY] && !maze[boxX+2][boxY + 1] ){				
					clearScreen();
					draw(myself, ++myX, myY, ++boxX, boxY);
				}
			} else {
				draw(myself, ++myX, myY, boxX, boxY);
			}
		}
		break;

		case 'd':   //Right
		case 'D':
		if(myY<20 && !maze[myX][myY+1]){    
			if( (myY + 1 == (boxY)) && (myX == boxX || myX == boxX+1) ){   						
				if( (boxY < 19) && !maze[boxX][boxY+2] && !maze[boxX+1][boxY+2] ){					
					clearScreen();
					draw(myself, myX, ++myY, boxX, ++boxY);
				}
			} else {
				draw(myself, myX, ++myY, boxX, boxY);
			}
		} 
		break;

		default:
		break;
	}		
}						