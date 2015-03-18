/* Homework 6
   CIVL 8903
   Khademul Haque
   URL:https://github.com/khademul/homework-6
 */

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct StationInfo {
	char networkCode[3];
	char stationCode[6];
	enum {LongPeriod='L', ShortPeriod='B', Broadband='H'} typeOfBand;
	enum {HighGain='H', LowGain='L', Accelerometer='N'} typeOfInstrument;
	char orientation; // N, E, Z, 1, 2, 3
};