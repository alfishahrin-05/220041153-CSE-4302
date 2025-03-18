#include <iostream>
#include <iomanip>
using namespace std;

class Time {
private:
    int hour;
    int minute;
    int second;
    void normalize() { //conversion
        if (second >= 60) {
            minute += second / 60;
            second %= 60;
        }
        if (minute >= 60) {
            hour += minute / 60;
            minute %= 60;
        }
        if (hour >= 24) {
            hour %= 24;
        }
    }

public:
    Time(int h = 0, int m = 0, int s = 0) : hour(h), minute(m), second(s) { //time class initiailize kore jodi kono value na dey taile 0 hishebe set hoy
        normalize();
    }
    int hours() const { //current value return kore
        return hour;
    }

    int minutes() const {
        return minute;
    }

    int seconds() const {
        return second;
    }
    void reset(int h, int m, int s) {
        hour = h;
        minute = m;
        second = s;
        normalize();
    }
    void advance(int h, int m, int s) {
        second += s;
        minute += m;
        hour += h;
        normalize();
    }

    void print() const {
        cout << setw(2) << setfill('0') << hour << ":"
             << setw(2) << setfill('0') << minute << ":"
             << setw(2) << setfill('0') << second << endl;
    }
};

int main() 
{
    Time t(23, 59, 58);
    t.print(); 

    t.advance(0, 0, 5);  
    t.print(); 

    t.reset(13, 45, 30); 
    t.print();  

    return 0;
}