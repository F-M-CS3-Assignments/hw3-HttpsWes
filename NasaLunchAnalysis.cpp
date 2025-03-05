// Author: Wesley Ihezuo
// Date: 03/1/2025
// Class: Comp Sci III
//I have read these notes

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "timecode.h"

using namespace std;

// Function to split a string using a given delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Extracts the launch time from a given CSV line and converts it into a TimeCode object
TimeCode extractTimeCode(const string& line) {
    vector<string> fields = split(line, ',');
    
    if (fields.size() <= 4) {
        return TimeCode(0, 0, 1); // Return an invalid time indicator
    }
    
    string dateTime = fields[4]; // Extract the column with date and time
    vector<string> dateParts = split(dateTime, ' ');
    
    if (dateParts.size() < 3) {
        return TimeCode(0, 0, 1); // Return invalid time if format is incorrect
    }
    
    vector<string> timeParts = split(dateParts[2], ':');
    if (timeParts.size() < 2) {
        return TimeCode(0, 0, 1);
    }
    
    unsigned int hours = stoi(timeParts[0]);
    unsigned int minutes = stoi(timeParts[1]);
    return TimeCode(hours, minutes, 0);
}

int main() {
    ifstream file("Space_Corrected.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
    
    vector<TimeCode> launchTimes;
    string line;
    getline(file, line); // Skip the header
    
    while (getline(file, line)) {
        TimeCode tc = extractTimeCode(line);
        if (!(tc.getHours() == 0 && tc.getMinutes() == 0 && tc.getSeconds() == 1)) {
            launchTimes.push_back(tc);
        }
    }
    file.close();
    
    if (launchTimes.empty()) {
        cout << "No valid launch times found." << endl;
        return 0;
    }
    
    // Compute the average launch time
    TimeCode total(0, 0, 0);
    for (const auto& time : launchTimes) {
        total = total + time;
    }
    TimeCode averageTime = total / static_cast<double>(launchTimes.size());
    
    // Output results
    cout << launchTimes.size() << " data points." << endl;
    cout << "AVERAGE: " << averageTime.ToString() << endl;
    
    return 0;
}