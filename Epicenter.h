/*
 * Epicenter.h
 * Header file
 * khademul haque
 */

#ifndef EPICENTER_H_
#define EPICENTER_H_

struct Epicenter {
private:
 double latitude;
 double longitude;
 double depth;
public:
 double getDepth() const {
	return depth;
 }

 void setDepth(double depth) {
	this->depth = depth;
 }

 double getLatitude() const {
	return latitude;
 }

 void setLatitude(double latitude) {
	this->latitude = latitude;
 }

 double getLongitude() const {
	return longitude;
 }

 void setLongitude(double longitude) {
	this->longitude = longitude;
 }
};
#endif /* EPICENTER_H_ */
