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
#include "earthquake.h"
#include "stationinfo.h"

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
printf("Enter Input File name: ");
std::cin>>inputFilePath;
fpLog = openFileWriteMode("khademul.log");
sprintf(strTmp, "Opening file:%s",inputFilePath);
printLog(strTmp);
std::ifstream fp(inputFilePath);
if (!fp.is_open()) {
	printLog("Input file not exist");
	exit(1);
}
earthquake earthquake;
date date;
time time;
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
earthquake.settimezone(timezone);

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
if(!date.isValiddate()) {
	printLog("Error in Header File: Invalid date");
	exit(1);
}
earthquake.setdate(date);
earthquake.settime(time);

string earthquakeName;
if(!getline(fp,earthquakeName)) {
	printLog("Error in Header File: Earthquake Name Missing");
	exit(1);
}
earthquakeName = trim(earthquakeName);
earthquake.setearthquakeName(earthquakeName);

if(!getline(fp,line)) {
	printLog("Error in Header File: Latitude Longitude Line Missing");
	exit(1);
}
line = trim(line);
epicenter epicenter;
epicenter.setLongitude( atof_h(strtok((char *)line.c_str()," \r\n")) );
epicenter.setLatitude( atof_h(strtok(NULL," \r\n")) );
epicenter.setDepth( atof_h(strtok(NULL," \r\n")) );

earthquake.setepicenter(epicenter);

char *magnitudeType = strtok(NULL," \r\n");
earthquake.setMagnitudeSize( atof_h(strtok(NULL," \r\n")) );

if(isEqualCI(magnitudeType,"ml") || isEqualCI(magnitudeType,"ms") || isEqualCI(magnitudeType,"mb") || isEqualCI(magnitudeType,"mw")) {
	magnitudeType[0] = toupper(magnitudeType[0]);
	magnitudeType[1] = tolower(magnitudeType[1]);
	if(isEqualCI(magnitudeType,"ml")) {
		earthquake.setMagnitudeType(Ml);
	}
	else if(isEqualCI(magnitudeType,"ms")) {
		earthquake.setMagnitudeType(Ms);
	}
	else if(isEqualCI(magnitudeType,"mb")) {
		earthquake.setMagnitudeType(Mb);
	}
	else if(isEqualCI(magnitudeType,"mw")) {
		earthquake.setMagnitudeType(Mw);
	}
} else {
	printLog("Error in Header File: magnitude type error");
	return 0;
}
if(earthquake.getMagnitudeSize()<0) {
	printLog("Error in Header File: magnitude size should be positive number");
	return 0;
}
printLog("Header read correctly!");
FILE *fpOut = openFileWriteMode("khademul.out");

const char* months[12] =
{   "January","February","March","April","May","June",
    "July","August","September","October","November","December"
};
fprintf(fpOut, "# %.2d %s %d %.2d:%.2d:%.2d.%.3d %s %s %.1f %s [%s] (%.2f, %.2f, %.1f)\n",
	earthquake.getdate().getDay(),months[earthquake.getdate().getMonth()],earthquake.getdate().getYear(),
	earthquake.gettime().getHour(), earthquake.gettime().getMinute() , earthquake.gettime().getSecond() , earthquake.gettime().getMilisecond(),
	earthquake.gettimezone().c_str(),
	earthquake.getMagnitudeTypeString(), earthquake.getMagnitudeSize(),
	earthquake.getearthquakeName().c_str(), earthquake.getId().c_str(),
	earthquake.getepicenter().getLongitude(), earthquake.getepicenter().getLatitude(), earthquake.getepicenter().getDepth());

stationinfo stationinfos[300];

int entryNumber=1;
int invalidCount=0;
int validEntryCount=0;
int totalSignalNames=0;
while(getline(fp, line)) {
	line = trim(line);
	if(validEntryCount>300) {
		continue;
	}
	int isValidRow=1;
stationinfo stationinfo;
char *networkCode = strtok((char *)line.c_str()," ");
if(isEqual(networkCode,"CE") || isEqual(networkCode,"CI") || isEqual(networkCode,"FA")
		|| isEqual(networkCode,"NP") || isEqual(networkCode,"WR")) {
	if(isEqual(networkCode,"CE")) {
		stationinfo.setNetworkCode(CE);
	} else if (isEqual(networkCode,"CI") ) {
		stationinfo.setNetworkCode(CI);
	} else if (isEqual(networkCode,"FA") ) {
		stationinfo.setNetworkCode(FA);
	} else if (isEqual(networkCode,"NP") ) {
		stationinfo.setNetworkCode(NP);
	} else if (isEqual(networkCode,"WR") ) {
		stationinfo.setNetworkCode(WR);
	}
} else {
	sprintf(strTmp, "Entry #%3d ignored. Invalid network.",entryNumber);
	printLog(strTmp);
	isValidRow=0;
}
char *stationCode = strtok(NULL," ");
int isValid=1;
if (strlen(stationCode)==3) {
	for(int i=0;i<3;i++) {
		if(stationCode[i]<'A' || stationCode[i]>'Z') {
			isValid=0;
			break;
		}
	}
} else if(strlen(stationCode)==5) {
	for(int i=0;i<5;i++) {
		if(stationCode[i]<'0' || stationCode[i]>'9') {
			isValid=0;
			break;
		}
	}
} else {
	isValid=0;
}
if(isValid==0) {
	sprintf(strTmp, "Entry #%3d ignored. Invalid station name.",entryNumber);
	printLog(strTmp);
	isValidRow=0;
}
stationinfo.setStationCode(stationCode);
char *typeOfBand = strtok(NULL," ");
if(isEqualCI(typeOfBand,"Long-period")) {
	stationinfo.setTypeOfBand(LongPeriod);
} else if(isEqualCI(typeOfBand,"Short-period")) {
	stationinfo.setTypeOfBand(ShortPeriod);
} else if(isEqualCI(typeOfBand,"Broadband")) {
	stationinfo.setTypeOfBand(Broadband);
} else {
	sprintf(strTmp, "Entry #%3d ignored. Invalid band type.",entryNumber);
	printLog(strTmp);
	//invalidCount++;
	//continue;
	isValidRow=0;
}
char *typeOfInstrument = strtok(NULL," ");
if(isEqualCI(typeOfInstrument,"High-Gain")) {
	stationinfo.setTypeOfInstrument(HighGain);
} else if(isEqualCI(typeOfInstrument,"Low-Gain")) {
	stationinfo.setTypeOfInstrument(LowGain);
} else if(isEqualCI(typeOfInstrument,"Accelerometer")) {
	stationinfo.setTypeOfInstrument(Accelerometer);
} else {
	sprintf(strTmp, "Entry #%3d ignored. Invalid type of instrument.",entryNumber);
	printLog(strTmp);
	//invalidCount++;
	//continue;
	isValidRow=0;
}
char *orientation = strtok(NULL," ");
isValid=1;
if(strlen(orientation)>3) {
	isValid=0;
} else {
	if(orientation[0]>='0' && orientation[0]<='9') {
		for(unsigned int i=0;i<strlen(orientation);i++) {
			if(orientation[i]<'0' || orientation[i]>'3') {
				isValid=0;
			}
		}
	} else {
		for(unsigned int i=0;i<strlen(orientation);i++) {
			switch(orientation[i]) {
			case 'N':
			case 'n':
			case 'E':
			case 'e':
			case 'Z':
			case 'z':
				break;
			default:
				isValid=0;
			}
		}
	}
}
if(!isValid) {
	sprintf(strTmp, "Entry #%3d ignored. Invalid orientation.",entryNumber);
	printLog(strTmp);
	//invalidCount++;
	//continue;
	isValidRow=0;
} else {
}
if(isValidRow==0){
	invalidCount++;
} else {
	for(unsigned int i=0;i<strlen(orientation);i++) {
		if(totalSignalNames>=300) {
			break;
		}
		stationinfos[totalSignalNames].setNetworkCode( stationinfo.getNetworkCode() );
		stationinfos[totalSignalNames].setStationCode( stationinfo.getStationCode() );
		stationinfos[totalSignalNames].setOrientation( orientation[i] );
		stationinfos[totalSignalNames].setTypeOfBand( stationinfo.getTypeOfBand() );
		stationinfos[totalSignalNames].setTypeOfInstrument( stationinfo.getTypeOfInstrument() );
		totalSignalNames++;
    	}
	    validEntryCount++;
    }
    entryNumber++;
}

sprintf(strTmp,"Total invalid entries ignored: %d",invalidCount);
printLog(strTmp);
sprintf(strTmp,"Total valid entries read: %d",validEntryCount);
printLog(strTmp);
sprintf(strTmp,"Total signal names produced: %d",totalSignalNames);
printLog(strTmp);

fprintf(fpOut,"%d\n",totalSignalNames);
for(int i=0;i<totalSignalNames;i++) {
	fprintf(fpOut,"%s.%s.%s.%c%c%c\n",
		earthquake.getId().c_str(),
		stationinfos[i].getNetworkCodeString(),
		stationinfos[i].getStationCode().c_str(),
		stationinfos[i].getTypeOfBand(),
		stationinfos[i].getTypeOfInstrument(),
		stationinfos[i].getOrientation()
		);
	}
fclose(fpLog);
fclose(fpOut);

return 0;
}