
#include "park.h"
#include "globals.h"

// this can't be defined in .h file (would cause multiple definition linker error)
EventScheduler* scheduler;

int main() {

	Park park;

	park.open();

	return 0;
}

// generate a random char from 'a' to 'z'
char generateRandomChar() {
	return 'a' + rand() % 26;
}

// generate a random number between avg-avg/2 and avg+avg/2
int generateRandomNumber(int avg) {
	return avg/2 + rand() % avg;
}

// generate a random boolean value with a given probability of true
bool generateRandomBool(double probOfTrue) {
	double t = ((double) rand()) / RAND_MAX;
	return t < probOfTrue;
}