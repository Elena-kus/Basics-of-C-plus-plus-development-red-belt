#include "airline_ticket.h"
#include "test_runner.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>

using namespace std;

bool operator<(const Date &left, const Date &right) {

	return tie(left.year, left.month, left.day) < tie(right.year, right.month, right.day);	
}

bool operator<(const Time &left, const Time &right) {

	return tie(left.hours, left.minutes) < tie(right.hours, right.minutes);
}

ostream& operator<<(ostream &stream, const Date& d) {

	stream << d.day << "." << d.day << "." << d.year << endl;
	return stream;
}

ostream& operator<<(ostream &stream, const Time& t) {

	stream << setw(2) << setfill('0');
	stream << t.hours << ":" <<t.minutes << endl;
	return stream;
}

bool operator==(const Date &left, const Date &right) {

	return (left.year == right.year) && (left.month == right.month) && (left.day == right.day);
}

bool operator==(const Time &left, const Time &right) {

	return (left.hours == right.hours) && (left.minutes == right.minutes);
}

istream& operator>>(istream& stream, Date& d) {

	if (stream) {
	  stream >> d.year;
	  stream.ignore(1);
	  stream >> d.month;
	  stream.ignore(1);
	  stream >> d.day;
	}

	return stream;
}

istream& operator>>(istream& stream, Time& t) {

	if (stream) {
	  stream >> t.hours;
	  stream.ignore(1);
	  stream >> t.minutes;
	}
	
	return stream;
}

#define UPDATE_FIELD(ticket, field, values) { map<string, string>::const_iterator it; \
                                              it = values.find(#field); \
                                              if (it != values.end()) { \
                                              istringstream is(it->second); \
                                              is >> ticket.field; }
                                              }\
											
void TestUpdate() {
	AirlineTicket t;
	t.price = 0;

	const map<string, string> updates1 = {
	  {"departure_date", "2018-2-28"},
	  {"departure_time", "17:40"},
	};

	UPDATE_FIELD(t, departure_date, updates1);
	UPDATE_FIELD(t, departure_time, updates1);
	UPDATE_FIELD(t, price, updates1);

	ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
	ASSERT_EQUAL(t.price, 0);

	const map<string, string> updates2 = {
	  {"price", "12550"},
	  {"arrival_time", "20:33"},
	};
  
	UPDATE_FIELD(t, departure_date, updates2);
	UPDATE_FIELD(t, departure_time, updates2);
	UPDATE_FIELD(t, arrival_time, updates2);
	UPDATE_FIELD(t, price, updates2);

	ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
	ASSERT_EQUAL(t.price, 12550);
	ASSERT_EQUAL(t.arrival_time, (Time{ 20, 33 }));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestUpdate);
}
