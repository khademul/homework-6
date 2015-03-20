/*
 * Earthquake.h
 * Header file
 * khademul haque
 *   
 */

#ifndef EARTHQUAKE_H_
#define EARTHQUAKE_H_

#include "Epicenter.h"
#include "Date.h"
#include "Time.h"

enum MagnitudeType {Ml, Ms, Mb, Mw};

struct Earthquake {
 private:
  std::string id;
  Date date;
  Time time;
  std::string timezone;
  std::string earthquakeName;
  Epicenter epicenter;
  MagnitudeType magnitudeType;
  double magnitudeSize;
 public:
  const Date& getDate() const {
  	return date;
 }

void setDate(const Date& date) {
	this->date = date;
 }

const std::string& getEarthquakeName() const {
	return earthquakeName;
 }

void setEarthquakeName(const std::string& earthquakeName) {
	this->earthquakeName = earthquakeName;
 }

const Epicenter& getEpicenter() const {
	return epicenter;
 }

void setEpicenter(const Epicenter& epicenter) {
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

const Time& getTime() const {
	return time;
 }

void setTime(const Time& time) {
	this->time = time;
 }

const std::string& getTimezone() const {
	return timezone;
 }

void setTimezone(const std::string& timezone) {
	this->timezone = timezone;
 }
};

#endif /* EARTHQUAKE_H_ */
