#include <thread>
#include <wiringPi.h>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <time.h>
#include <sys/time.h>

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
