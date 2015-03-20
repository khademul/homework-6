/*
 * earthquake.h
 * Header file
 * khademul haque
 *   
 */

#ifndef EARTHQUAKE_H_
#define EARTHQUAKE_H_

#include "epicenter.h"
#include "date.h"
#include "time.h"

enum MagnitudeType {Ml, Ms, Mb, Mw};

struct earthquake {
 private:
  std::string id;
  date date;
  time time;
  std::string timezone;
  std::string earthquakeName;
  epicenter epicenter;
  MagnitudeType magnitudeType;
  double magnitudeSize;
 public:
  const date& getdate() const {
  	return date;
 }

void setdate(const date& date) {
	this->date = date;
 }

const std::string& getearthquakeName() const {
	return earthquakeName;
 }

void setearthquakeName(const std::string& earthquakeName) {
	this->earthquakeName = earthquakeName;
 }

const epicenter& getepicenter() const {
	return epicenter;
 }

void setepicenter(const epicenter& epicenter) {
	this->epicenter = epicenter;
 }

const std::string& getId() const {
	return id;
 }

void setId(const std::string& id) {
	this->id = id;
 }

double getMagnitudeSize() const {
	return magnitudeSize;
 }

void setMagnitudeSize(double magnitudeSize) {
	this->magnitudeSize = magnitudeSize;
 }

MagnitudeType getMagnitudeType() const {
	return magnitudeType;
 }

const char *getMagnitudeTypeString() const {
	switch(this->magnitudeType) {
	case Ml:
		return "Ml";
		break;
	case Ms:
		return "Ms";
		break;
	case Mb:
		return "Mb";
		break;
	case Mw:
		return "Mw";
		break;
	}
	return "";
 }

void setMagnitudeType(MagnitudeType magnitudeType) {
	this->magnitudeType = magnitudeType;
 }

const time& gettime() const {
	return time;
 }

void settime(const time& time) {
	this->time = time;
 }

const std::string& gettimezone() const {
	return timezone;
 }

void settimezone(const std::string& timezone) {
	this->timezone = timezone;
 }
};

#endif /* EARTHQUAKE_H_ */
