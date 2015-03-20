/*
 * time.h
 * Header file
 * khademul haque
 */

#ifndef TIME_H_
#define TIME_H_

struct time {
 private:
  int hour;
  int minute;
  int second;
  int milisecond;
 public:
  int getHour() const {
	return hour;
 }

 void setHour(int hour) {
	this->hour = hour;
 }

 int getMilisecond() const {
	return milisecond;
 }

 void setMilisecond(int milisecond) {
	this->milisecond = milisecond;
 }

 int getMinute() const {
	return minute;
 }

 void setMinute(int minute) {
	this->minute = minute;
 }

 int getSecond() const {
	return second;
 }

 void setSecond(int second) {
	this->second = second;
 }
};

#endif /* TIME_H_ */
