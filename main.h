#include <thread>
#include <wiringPi.h>
#include <iostream>
#include <list>
#include <string>

#include <sstream>
#include <time.h>
#include <sys/time.h>

#include <sys/types.h>
#include <dirent.h>

namespace SCR {
  enum SCR{
    CLEAR,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    BLACK_WHITE,
    GLAY_BLACK
  };
}

using namespace std;

void screen_set(int in);

void output();

string get_time();

void search_file();

int selects(const dirent *dir);
