#include<iostream>
#include <ostream>
#include<sstream>
#include <termios.h>
#include<string>
#include <fstream>
//#include <conio.h>
//#include <stdio.h>

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
    currPos.x_cor= 49;
    currPos.y_cor= 49;

    //Desactivate stdin buffer
    bufferOff();
  
    //Loading map from file
    loadMap("map1");
    updateMap(currPos);
    printMap();

    gameOver= false;    

    char userInput;

    //Main game loop

    while (!gameOver)

    {

    cin >> userInput;
    updateMap(currPos);
    printMap();
    switch(userInput)

    {

    case 'a': moveLeft(currPos);

    case'd': moveRight(currPos);

    case's': moveDown(currPos);

    case'w': moveUp(currPos);

    }

    }
     return 0;
}

    
   





/////////////////////////////////////////////

void loadMap(string fileName)
{

  ifstream inputFile(fileName.c_str());
    int i,j;
    for (i=0;i<5;i++)
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
  tcgetattr(0, &t);
  t.c_lflag &= ~ICANON;
  tcsetattr(0, TCSANOW, &t);
}



void moveLeft(position_e currPos)
{
  currPos.x_cor=(map[currPos.x_cor -1][currPos.y_cor]=='X')? currPos.x_cor: currPos.x_cor--;
}
void moveRight(position_e currPos)
{
  currPos.x_cor=(map[currPos.x_cor +1][currPos.y_cor]=='X')? currPos.x_cor: currPos.x_cor++;
}
void moveUp(position_e currPos)
{
  currPos.y_cor=(map[currPos.x_cor][currPos.y_cor -1]=='X')? currPos.y_cor: currPos.y_cor--;
}
void moveDown(position_e currPos)
{
 currPos.y_cor=(map[currPos.x_cor][currPos.y_cor +1]=='X')? currPos.y_cor: currPos.y_cor++;
}
