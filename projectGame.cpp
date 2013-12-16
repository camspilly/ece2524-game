#include<iostream>
#include <ostream>
#include<sstream>
#include <termios.h>
#include<string>
#include <fstream>
#include <map>
#include <cstdlib>
#include <dirent.h>
#include <string.h>
#include <libgen.h>
//#include <conio.h>
//#include <stdio.h>

using namespace std;
char gameMap[50][50];
bool gameOver;
struct position_e
{
  int x_cor;
  int y_cor;
};

struct Wizzard
{
  string name;
  bool dead;
};

string prefix;
string levelScript;

map <char, Wizzard> mapOfLevels;

void loadMap(string fileName, position_e currPos);
void bufferOff();
void updateMap(position_e currPos);
void printMap();
void getLevels(map<char, Wizzard> mapOfLevels);
void proceedInput(char userInput, position_e currPos);



int main(int argc, char *argv[])
{


   //Building the path prefix
   // we stdup it twice because some implementations of dirname
   // return a pointer to internal static memory, and others
   // modify it inplace, so account for both variants like so:
    char* firstCopy= strdup(argv[0]);
    char* firstCopyDir= dirname(firstCopy);
    prefix = string (firstCopyDir);
    free(firstCopy);
    levelScript = prefix + "/shell-wrapper/run.sh";

    position_e currPos;
    currPos.x_cor= 49;
    currPos.y_cor= 49;

    //Desactivate stdin buffer
    bufferOff();

    //Loading map from file
    loadMap("main.map", currPos);
    updateMap(currPos);
    printMap();

    //Loading the levels into the map structure
    getLevels(mapOfLevels);

    gameOver= false;

    char userInput;

    //Main game loop

    while (!gameOver)

    {

    cin >> userInput;
    proceedInput(userInput,currPos);
    updateMap(currPos);
    printMap();

    }
     return 0;
}








/////////////////////////////////////////////
void proceedInput(char userInput,  position_e currPos)
{
  int requestedX= currPos.x_cor;
  int requestedY= currPos.y_cor;
  requestedX= (userInput == 'a')?requestedX--:
    (userInput == 'd')? requestedX++ :requestedX;

  requestedY= (userInput == 's')?requestedY--:
    (userInput == 'w')?requestedY++:requestedY;

  char  onTheMap= gameMap[requestedX][requestedY];

  if ( mapOfLevels.count(onTheMap)==0)
    {
      if(onTheMap != 'X')
	{
	  currPos.x_cor= requestedX;
	  currPos.y_cor= requestedY;
	}
    }
  else
    {
      if(!(mapOfLevels.at(onTheMap).dead))
      {
	// build the full path of the shell wrapper
	setenv("GAME_LEVEL_DIR",(prefix+"/"+mapOfLevels.at(onTheMap).name).c_str(), 1);
	int ret = system(levelScript.c_str());
	if (ret == 32) {
	  mapOfLevels.at(onTheMap).dead= true;
	  currPos.x_cor= requestedX;
	  currPos.y_cor= requestedY;
	} else if (ret == 33) {

	} else {
	  // some error
	}
      }
    }

}

void getLevels(map<char, Wizzard> mapOfLevels)
{
  DIR *dir;
  DIR *subdir;
  struct dirent *ent;
  struct dirent *subent;
  if ((dir = opendir((prefix+"/levels").c_str())) != NULL)
  {
    while ((ent= readdir (dir)) != NULL)
      {
	Wizzard myWizzard;
	char wizzarS; //Symbol

	myWizzard.name= ent->d_name;
	myWizzard.dead= false;

	subdir = opendir((prefix+"/levels/"+myWizzard.name).c_str());
	subent= readdir(subdir);

	ifstream levelStream(subent->d_name);
	wizzarS= levelStream.get();

	mapOfLevels.insert (pair <char, Wizzard> (wizzarS,myWizzard));
      }

  }

}

void loadMap(string fileName, position_e currPos)
{
  ifstream inputFile(fileName.c_str());
    int i,j;
    for (i=0;i<50;i++) {
	for (j=0; j<50; j++) {
             inputFile >> gameMap[i][j];
	     if (gameMap[i][j]=='@') {
	       currPos.x_cor= i;
	       currPos.y_cor= j;
	     }
	}
    }
}

void updateMap(position_e currPos)
{
  gameMap[currPos.x_cor][currPos.y_cor]= '@';
}

void printMap()
{
int i,j;
  for(i=0;i<50;i++)
  {
    for(j=0;j<50;j++)
    {
     cout<<gameMap[i][j];

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
