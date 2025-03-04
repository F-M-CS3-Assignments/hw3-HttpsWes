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
vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    ifstream file("Space_Corrected.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
    
    vector<string> extractedTimes;
    string line;
    getline(file, line); // Skip the header
    
    while (getline(file, line)) {
        vector<string> fields = splitString(line, ',');
        
        if (fields.size() > 4) {
            string dateTime = fields[4]; // Extract the "Datum" column
            vector<string> dateParts = splitString(dateTime, ' ');
            
            if (dateParts.size() >= 3) {
                extractedTimes.push_back(dateParts[2]); // Store extracted times
            }
        }
    }
    file.close();
    
    // Display extracted times (debugging step)
    cout << "Extracted times from CSV:" << endl;
    for (const string& time : extractedTimes) {
        cout << time << endl;
    }
    
    return 0;
}