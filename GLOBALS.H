#ifndef GLOBALS_H
#define GLOBALS_H
const double PI = 3.1415926535897932384626433;

//const long MID_X = 150, MID_Y = ; 
extern int viewdegree;
extern double global_y_ratio;
extern int viewangle;
extern double zoom_factor;

class EventScheduler;

extern EventScheduler* scheduler;

// as allowed by the fire marshal; the management of course wants to keep the park full
// all the time
const int MAX_PARK_OCCUPANCY = 100;
const int FONT_SIZE = 12;

// avg interval between visitor arrival (in ticks)
const int AVG_VISITOR_INTERVAL = 30;

// generate a random char from 'a' to 'z'
char generateRandomChar();

// generate a random number between avg-avg/2 and avg+avg/2
int generateRandomNumber(int avg);


// generate a random boolean value with a given probability of true
bool generateRandomBool(double probOfTrue);

#endif