// Author: Wesley Ihezuo
// Date: 02/15/2025
// Class: Comp Sci III


#include "timecode.h" //Implmented timecode.h which is needed for me to declare my functions in a seperate file
#include <iomanip>
#include <sstream>
#include <assert.h>


// Constructor: Initializes TimeCode with hours, minutes, and seconds
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {
    t = ComponentsToSeconds(hr, min, sec);
}

// Copy Constructor
TimeCode::TimeCode(const TimeCode& tc) {
    t = tc.t;
}

// Setter Functions
void TimeCode::SetHours(unsigned int hours) {
    t = ComponentsToSeconds(hours, getMinutes(), getSeconds()); //setting hours
}

void TimeCode::SetMinutes(unsigned int minutes) {
    t = ComponentsToSeconds(getHours(), minutes, getSeconds()); //setting minutes
}

void TimeCode::SetSeconds(unsigned int seconds) {
    t = ComponentsToSeconds(getHours(), getMinutes(), seconds);//setting seconds
}

// Reset function
void TimeCode::reset() { 
    t = 0; //reset time to 0
}

// Getter Functions
unsigned int TimeCode::getHours() const {
    return t / 3600; // 3600 seconds equals one hour 
}

unsigned int TimeCode::getMinutes() const {
    return (t % 3600) / 60;  // used % module to get remainder of seconds than divide by 60 to get minutes
}

unsigned int TimeCode::getSeconds() const {
    return t % 60; //use % module to calculate the remainding seconds for given t value
 
}

// Convert hours, minutes, and seconds into total seconds
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, long long unsigned int sec) {
    return hr * 3600 + min * 60 + sec;
}


// Extracts hours, minutes, and seconds
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
    hr = getHours();
    min = getMinutes();
    sec = getSeconds();
}

// Converts time to a formatted string
std::string TimeCode::ToString() const {
    std::stringstream ss;
    ss << getHours() << ":" << getMinutes() << ":" << getSeconds();   // should look something like this "00:00:00"
    return ss.str();
}


// Arithmetic Operators
TimeCode TimeCode::operator+(const TimeCode& other) const {
    return TimeCode(0, 0, t + other.t); 
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
    if (t < other.t) {
        throw std::underflow_error("Subtraction would result in a negative number");
    }
    return TimeCode(0, 0, t - other.t);
}

TimeCode TimeCode::operator*(double a) const {
    if (a < 0) {
        throw std::invalid_argument("Multiplication value must be postive");
    }
    return TimeCode(0, 0, static_cast<long long unsigned int>(t * a));
}

TimeCode TimeCode::operator/(double a) const {
    if (a == 0) {
        throw std::domain_error("Division by zero is not accepted");
    }
    return TimeCode(0, 0, static_cast<long long unsigned int>(t / a));
}


// Comparison Operators
bool TimeCode::operator==(const TimeCode& other) const {
    return t == other.t;
}

bool TimeCode::operator!=(const TimeCode& other) const {
    return t != other.t;
}

bool TimeCode::operator<(const TimeCode& other) const {
    return t < other.t;
}

bool TimeCode::operator<=(const TimeCode& other) const {
    return t <= other.t;
}

bool TimeCode::operator>(const TimeCode& other) const {
    return t > other.t;
}

bool TimeCode::operator>=(const TimeCode& other) const {
    return t >= other.t;
}