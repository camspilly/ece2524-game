#include <iostream>
#include <ostream>
#include <sstream>
#include <termios.h>
#include <string>
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
struct position_e {
	int x_cor;
	int y_cor;
};

struct Wizzard {
	string name;
	bool dead;
};

string prefix;
string levelScript;

map <char, Wizzard> mapOfLevels;

void loadMap(string fileName, position_e& currPos);
void bufferOff();
void printMap(position_e &currPos);
void getLevels(map<char, Wizzard> mapOfLevels);
void proceedInput(char userInput, position_e& currPos);

int main(int argc, char *argv[])
{


	//Building the path prefix
	// we stdup it twice because some implementations of dirname
	// return a pointer to internal static memory, and others
	// modify it inplace, so account for both variants like so:
	char* firstCopy = strdup(argv[0]);
	char* firstCopyDir = dirname(firstCopy);
	prefix = string (firstCopyDir);
	free(firstCopy);
	levelScript = prefix + "/shell-wrapper/run.sh";

	position_e currPos;



	//Desactivate stdin buffer
	bufferOff();

	//Loading map from file
	loadMap("main.map", currPos);
	printMap(currPos);

	//Loading the levels into the map structure
	getLevels(mapOfLevels);

	gameOver = false;

	char userInput;

	//Main game loop

	while (!gameOver)

	{

		cin >> userInput;
		proceedInput(userInput, currPos);
		printMap(currPos);

	}
	return 0;
}








/////////////////////////////////////////////
void proceedInput(char userInput,  position_e& currPos)
{
	int requestedX = currPos.x_cor;
	int requestedY = currPos.y_cor;

	switch (userInput) {
	case 'w':
		requestedY--;
		break;
	case 'a':
		requestedX--;
		break;
	case 's':
		requestedY++;
		break;
	case 'd':
		requestedX++;
		break;
	}

	char onTheMap = gameMap[requestedX][requestedY];

	if ( mapOfLevels.count(onTheMap) == 0) {
		if(onTheMap != 'X') {
			currPos.x_cor = requestedX;
			currPos.y_cor = requestedY;
		}
	} else {
		if(!(mapOfLevels.at(onTheMap).dead)) {
			// build the full path of the shell wrapper
			setenv("GAME_LEVEL_DIR", (prefix + "/" + mapOfLevels.at(onTheMap).name).c_str(), 1);
			int ret = system(levelScript.c_str());
			if (ret == 32) {
				mapOfLevels.at(onTheMap).dead = true;
				currPos.x_cor = requestedX;
				currPos.y_cor = requestedY;
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
	struct dirent *ent;

	dir = opendir((prefix + "/levels").c_str());

	if (dir == NULL) {
		cerr << "unable to load levels" << endl;
		exit(1);
	}

	while ((ent = readdir (dir)) != NULL) {
		Wizzard myWizzard;
		char wizzarS; //Symbol

		myWizzard.name = ent->d_name;
		myWizzard.dead = false;

		ifstream levelStream((prefix + "/levels/" + ent->d_name + "/ICON").c_str());
		if (!levelStream.is_open()) {
			cerr << "unable to load " << (ent->d_name) << ": missing ICON file" << endl;
			exit(1);
		}
		wizzarS = levelStream.get();

		mapOfLevels.insert (pair <char, Wizzard> (wizzarS, myWizzard));
	}
}

void loadMap(string fileName, position_e& currPos)
{
	ifstream inputFile(fileName.c_str());
	int i, j;
	for (i = 0; i < 50; i++) {
		for (j = 0; j < 50; j++) {
			char cell;
			inputFile >> cell;
			if (cell == '@') {
				currPos.x_cor = j;
				currPos.y_cor = i;
				gameMap[j][i] = '-';
			} else
				gameMap[j][i] = cell;
		}
	}
}

void printMap(position_e &currPos)
{
	int i, j;

	cout << "\x1b[2J"; //Clear the screen
	cout << "\x1b[;H"; // move cursor to top-left

	for(i = 0; i < 50; i++) {
		for(j = 0; j < 50; j++) {
			if (i == currPos.y_cor && j == currPos.x_cor)
				cout << "@";
			else
				cout << gameMap[j][i];
		}
		cout << endl;
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
