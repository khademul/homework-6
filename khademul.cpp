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
#include "Earthquake.h"
#include "StationInfo.h"

using namespace std;

FILE *fpLog = NULL;

void printLog(char *strLog) {
	printf("%s\n", strLog);
	fprintf(fpLog, "%s\r\n", strLog);
}
int isIntegerString(char *str) {
	for(unsigned int i=0; i<strlen(str); i++) {
		if((str[i]>='0' && str[i]<='9') || str[i]=='-' || str[i]=='+') {
		} else {
			return 0;
		}
	}
	return 1;
}
int atoi_h(char *str) {
	if(!isIntegerString(str)) {
		printLog("Error: Integer Expected");
		exit(1);
	}
	return atoi(str);
}
int isFloatString(char *str) {
	for(unsigned int i=0; i<strlen(str); i++) {
		if((str[i]>='0' && str[i]<='9') || str[i]=='.' || str[i]=='-' || str[i]=='+') {

		} else {
			return 0;
		}
	}
	return 1;
}
float atof_h(char *str) {
	if(!isFloatString(str)) {
		printLog("Error: Real Number Expected");
		printLog(str);
		exit(1);
	}
	return atof(str);
}
int isEqual(char *s1, char *s2) {
	return strcmp(s1,s2)==0;
}
int isEqualCI(char *s1, char *s2) {
	if(strlen(s1)!=strlen(s2)) {
		return 0;
	}
	for(unsigned int i=0; i<strlen(s1); i++) {
		if(tolower(s1[i])!=tolower(s2[i])) {
			return 0;
		}
	}
	return 1;
}
void trimLastNewLines(char *str) {
	for(int i=strlen(str)-1; i>=0; i++) {
		if(str[i]=='\r' || str[i]=='\n') {
			str[i] = 0;
		} else {
			break;
		}
	}
}
// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}
// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}
// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}
FILE* openFileWriteMode(char *filePath) {
	FILE *fp = fopen(filePath, "w");
	if(fp==NULL) {
		printf("Unable to open %s. Check permission\n", filePath);
		exit(1);
	}
	return fp;
}

int main() {
string line;
char strTmp[256];
char inputFilePath[1024];
printf("Input File: ");
std::cin>>inputFilePath;
fpLog = openFileWriteMode("earthquake.log");
sprintf(strTmp, "Opening file:%s",inputFilePath);
printLog(strTmp);
std::ifstream fp(inputFilePath);
if (!fp.is_open()) {
	printLog("Input file not exist");
	exit(1);
}
Earthquake earthquake;
Date date;
Time time;
printLog("Processing input...");
string eventId;
if(!getline(fp, eventId)) {
	printLog("Error in Header File: No Event ID");
	return 0;
}
eventId = trim(eventId);
earthquake.setId(eventId);
if(!getline(fp, line)) {
	printLog("Error in Header File: Date Time Row Missing");
	return 0;
}
line = trim(line);
char *dateStr = strtok((char *)line.c_str(), " \r\n");
if (dateStr == NULL) {
	printLog("Error in Header File: Date Error");
	return 0;
}
char *timeStr = strtok(NULL, " \r\n");
if (timeStr == NULL) {
	printLog("Error in Header File: Time Error");
	exit(1);
}
char *timezoneStr = strtok(NULL, " \r\n");
string timezone;
if (timezoneStr == NULL) {
	printLog("Error in Header File: Timezone Error");
	exit(1);
}
if(strlen(timezoneStr)!=3) {
	printLog("Error in Header File: Timezone Format Error");
	exit(1);
}
timezone = timezoneStr;
earthquake.setTimezone(timezone);

//int year,month,day,hour,minute,second,milisecond;
if ((dateStr[2]=='/' && dateStr[5]=='/') || (dateStr[2]=='-' && dateStr[5]=='-')) {
	if(!date.setMonth( atoi_h(strtok(dateStr,"/-")) ) ) {
		printLog("Invalid Month");
		exit(1);
	}
	date.setDay( atoi_h(strtok(NULL,"/-")) );
	date.setYear( atoi_h(strtok(NULL,"/-")) );
} else {
	printLog("Error in Header File: Date format error");
	exit(1);
}
if (timeStr[2]==':' && timeStr[5]==':' && timeStr[8]=='.') {
	time.setHour( atoi_h(strtok(timeStr,":.")) );
	time.setMinute( atoi_h(strtok(NULL,":.")) );
	time.setSecond( atoi_h(strtok(NULL,":.")) );
	time.setMilisecond( atoi_h(strtok(NULL,":.")) );
} else {
	printLog("Error in Header File: Time format error");
	exit(1);
}
if(!date.isValidDate()) {
	printLog("Error in Header File: Invalid date");
	exit(1);
}
earthquake.setDate(date);
earthquake.setTime(time);

string earthquakeName;
if(!getline(fp,earthquakeName)) {
	printLog("Error in Header File: Earthquake Name Missing");
	exit(1);
}
earthquakeName = trim(earthquakeName);
earthquake.setEarthquakeName(earthquakeName);

if(!getline(fp,line)) {
	printLog("Error in Header File: Latitude Longitude Line Missing");
	exit(1);
}
line = trim(line);
Epicenter epicenter;
epicenter.setLongitude( atof_h(strtok((char *)line.c_str()," \r\n")) );
epicenter.setLatitude( atof_h(strtok(NULL," \r\n")) );
epicenter.setDepth( atof_h(strtok(NULL," \r\n")) );

earthquake.setEpicenter(epicenter);

char *magnitudeType = strtok(NULL," \r\n");
earthquake.setMagnitudeSize( atof_h(strtok(NULL," \r\n")) );

