#include "main.h"

using namespace std;

#define LED1 9
#define LED2 25
#define SWITCH1 24
#define SWITCH2 23
#define SWITCH3 10

bool end_flag = false;
int i = 0;
list<string> str_list;

int main(void){
    thread t1(output);

    DIR* dp=opendir("/home/pi/music/");
    if(dp!=NULL){
        struct dirent* dent;
        do{
            dent = readdir(dp);
            if(dent!=NULL){
                string str = string(dent->d_name);
                if(str != "."){
                    if(str != ".."){
                    str_list.push_back(str);
                    }
                }
            }
        }while(dent!=NULL);
        closedir(dp);
    }

    if(wiringPiSetupGpio() == -1){
        cout<<"error wiringPi setup"<<endl;
        return 1;
    }

    //pin Settings
    pinMode(SWITCH1, INPUT);
    pinMode(SWITCH2, INPUT);
    pinMode(SWITCH3, INPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    //flag for trigger mode
    bool switch1_flag = false;
    bool switch2_flag = false;

    //main routin
    for(;;){
        if(digitalRead(SWITCH1) == 1){
            if(!switch1_flag){
                switch1_flag = true;
                i--;
                if(i<0){
                    i=0;
                }
            }
            digitalWrite(LED1, 1);
        }else{
            if(switch1_flag){
                switch1_flag = false;
            }
            digitalWrite(LED1, 0);
        }
        if(digitalRead(SWITCH2) == 1){
            if(!switch2_flag){
                switch2_flag = true;
                i++;
            }
            digitalWrite(LED2, 1);
        }else{
            if(switch2_flag){
                switch2_flag = false;
            }
            digitalWrite(LED2, 0);
        }
        if(digitalRead(SWITCH1)==1 && digitalRead(SWITCH2)==1){
            end_flag = true;
            break;
        }
        if(digitalRead(SWITCH3)==1){
            end_flag = true;
            break;
        }
    delay(10);
    }

    t1.join();
    cout<<"\nexit"<<endl;
    digitalWrite(LED1, 0);
    digitalWrite(LED2, 0);
    return 0;
}

void screen_set(int in){
  switch(in){
    case SCR::CLEAR:
      cout<<"\e[2J\033[1;1H"<<flush;
      break;
    case SCR::UP:
      cout<<"\e[1A\4"<<flush;
      break;
    case SCR::DOWN:
      cout<<"\e[1B\r"<<flush;
      break;
    case SCR::LEFT:
      cout<<"\e[1D"<<flush;
      break;
    case SCR::RIGHT:
      cout<<"\e[1C"<<flush;
      break;
    case SCR::BLACK_WHITE:
      cout<<"\e[08m"<<flush;
      break;
    case SCR::GLAY_BLACK:
      cout<<"\e[80m"<<flush;
      break;
    default:
      break;
  }
}

void output(){
//    list<string> list;
//    list.push_back("ndendende");
//    list.push_back(".....");
//    list.push_back("nya-----nde");
    auto itr = str_list.begin();
    int p;
    for(;;){
        if(end_flag){
            return;
        }
        delay(25);
        p=0;
        screen_set(SCR::BLACK_WHITE);
        screen_set(SCR::CLEAR);
        cout<<get_time()<<flush;
        screen_set(SCR::DOWN);
        for(itr = str_list.begin(); itr!=str_list.end();++itr){
            if(p == i){
                cout<<"* "<<flush;
            }else{
                screen_set(SCR::RIGHT);screen_set(SCR::RIGHT);
            }
            cout<<*itr<<flush;

            screen_set(SCR::DOWN);
            p++;
        }
    }
}

string get_time(){
    stringstream str;
    struct timeval myTime;
    struct tm *time_st;
    gettimeofday(&myTime, NULL);
    time_st = localtime(&myTime.tv_sec);
    str<<time_st->tm_mon+1<<"/";
    str<<time_st->tm_mday<<" ";
    str<<time_st->tm_hour<<":";
    str<<time_st->tm_min<<":";
    str<<time_st->tm_sec;
    return str.str();
}
