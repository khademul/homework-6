/*
 * stationinfo.h
 * Header file
 * khademul haque
 */

#ifndef STATIONINFO_H_
#define STATIONINFO_H_

enum NetworkCode {CE, CI, FA, NP, WR};
enum TypeOfBand {LongPeriod='L', ShortPeriod='B', Broadband='H'};
enum TypeOfInstrument {HighGain='H', LowGain='L', Accelerometer='N'};

struct stationinfo {
 private:
  NetworkCode networkCode;
  std::string stationCode;
  TypeOfBand typeOfBand;
  TypeOfInstrument typeOfInstrument;
  char orientation; // N, E, Z, 1, 2, 3
 public:
 NetworkCode getNetworkCode() const {
 	return networkCode;
 }

 const char *getNetworkCodeString() const {
	switch(networkCode) {
	case CE:
		return "CE";
	case CI:
		return "CI";
	case FA:
		return "FA";
	case NP:
		return "NP";
	case WR:
		return "WR";
	}
	return NULL;
 }

 void setNetworkCode(NetworkCode networkCode) {
	this->networkCode = networkCode;
 }

 char getOrientation() const {
	return orientation;
 }

 void setOrientation(char orientation) {
	this->orientation = orientation;
 }

 std::string getStationCode() const {
	return stationCode;
 }

 void setStationCode(std::string stationCode) {
	this->stationCode = stationCode;
 }

 TypeOfBand getTypeOfBand() const {
	return typeOfBand;
 }

 void setTypeOfBand(TypeOfBand typeOfBand) {
	this->typeOfBand = typeOfBand;
 }

 TypeOfInstrument getTypeOfInstrument() const {
	return typeOfInstrument;
 }

 void setTypeOfInstrument(TypeOfInstrument typeOfInstrument) {
	this->typeOfInstrument = typeOfInstrument;
 }
};
#endif /* STATIONINFO_H_ */
