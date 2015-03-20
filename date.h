/* date.h
 * Header file
 * khademul haque
 * 
 */

#ifndef DATE_H_
#define DATE_H_

enum Month {January, February, March, April, May, June, July, August, September, October, November, December};

struct Date {
private:
	int day;
	Month month;
	int year;
public:

bool isValidDate() {
	return true;
}
bool isLeapYear() {
	if (year%400 == 0) {
		return true;
	} else if ( year%100 == 0) {
		return false;
	} else if ( year%4 == 0 ) {
		return true;
	}
	return false;
}
int getDay() const {
	return day;
}
void setDay(int day) {
	this->day = day;
}

Month getMonth() const {
	return month;
}
void setMonth(Month month) {
	this->month = month;
}
bool setMonth(int month) {
	switch (month) {
		case 1:
			this->month = January;
			break;
		case 2:
			this->month = February;
			break;
		case 3:
			this->month = March;
			break;
		case 4:
			this->month = April;
			break;
		case 5:
			this->month = May;
			break;
		case 6:
			this->month = June;
			break;
		case 7:
			this->month = July;
			break;
		case 8:
			this->month = August;
			break;
		case 9:
			this->month = September;
			break;
		case 10:
			this->month = October;
			break;
		case 11:
			this->month = November;
			break;
		case 12:
			this->month = December;
			break;
		default:
			return false;
	}
	return true;
}
int getYear() const {
	return year;
}
void setYear(int year) {
	this->year = year;
}
};
#endif /* DATE_H_ */
