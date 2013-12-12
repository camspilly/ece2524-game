#include<iostream>
#include <ostream>
#include<sstream>
#include <curses.h>
#include <termios.h>
#include <conio.h>
#include <stdio.h>

using namespace std;
char map[50][50];
bool gameOver;
struct position_e
{
  int x_cor;
  int y_cor;
};

void loadMap(string fileName);
void bufferOff();
void updateMap(position_e currPos);
void printMap();
void moveLeft(position_e currPos);
void moveRight(position_e currPos);
void moveUp(position_e currPos);
void moveDown(position_e currPos);


int main()
{


    position_e currPos;
    currPos.x= 49;
    currPos.y= 49;

    //Desactivate stdin buffer
    bufferOff();
  
    //Loading map from file
    loadMap(map1);
    updateMap(currPos);
    printMap();

    gameOver= false;    

    char userInput;

    //Main game loop

    while (!gameOver)

    {

    userInput=getc();
    mapUpdate();
    mapPrint();
    switch(userInput)

    {

    case 'a': moveLeft();

    case'd': moveRight();

    case's': moveDown();

    case'w': moveUp();

    }

    }

}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
void loadMap(string map)
{

    ifstream inputFile(map+"txt");
    int i,j;
    for (i=0;i<5-;i++)
      {
	for (j=0; j<50; j++)
	  {
             inputFile >> map[i][j];
	    
	  }

      }   
}

void updateMap(position_e currPos)
{
  map[currPos.x_cor][currPos.y_cor]= 1;
}

void printMap()
{
int i,j;
  for(i=0;i<50;i++)
  {
    for(j=0;j<50;j++)
    {
     cout<<map[i][j];
    }
  }
}

void bufferOff()
{  
  //Desactivating standard input buffer
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ICANON;
  tcsetattr(STDIN_FILENO, TSCANOW, &t);
}



void moveLeft(position_e currPos)
{
  currPos.x_cor=(map[currPos.x -1][currPos.y]=="X")? currPos.x_cor: currPos.x_cor--;
}
void moveRight(position_e currPos)
{
  currPos.x_cor=(map[currPos.x +1][currPos.y]=="X")? currPos.x_cor: currPos.x_cor++;
}
void moveUp(position_e currPos)
{
  currPos.y_cor=(map[currPos.x][currPos.y-1]=="X")? currPos.y_cor: currPos.y_cor--;
}
void moveDown(position_e currPos)
{
 currPos.y_cor=(map[currPos.x][currPos.y+1]=="X")? currPos.y_cor: currPos.y_cor++;
}
