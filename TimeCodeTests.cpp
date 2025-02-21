#include <iostream>
#include <assert.h>
using namespace std;

#include "timecode.h"

void TestComponentsToSeconds(){
    cout << "Testing ComponentsToSeconds" << endl;
    
    // Random inputs
    long long unsigned int t = TimeCode::ComponentsToSeconds(2, 20, 50);
    assert(t == 8450);
    
    // Test case to test zero input test cases
    t = TimeCode::ComponentsToSeconds(0, 0, 0);
    assert(t == 0);
    
    // Edge case for maximum single-digit minutes and seconds
    t = TimeCode::ComponentsToSeconds(0, 58, 58);
    assert(t == 3538);
    
    // Test case for large input values
    t = TimeCode::ComponentsToSeconds(150, 0, 0);
    assert(t == 540000);
    
    
    cout << "PASSED!" << endl << endl;
}

void TestDefaultConstructor(){
    // Default constructor test
    cout << "Testing Default Constructor" << endl;
    TimeCode tc;
    assert(tc.ToString() == "0:0:0");
    
    // Additional test for newly created object
    TimeCode tc2;
    assert(tc2.ToString() == "0:0:0");
    
    cout << "PASSED!" << endl << endl;
}

void TestComponentConstructor(){
    cout << "Testing Component Constructor" << endl;
    
    // Zero values
    TimeCode tc = TimeCode(0, 0, 0);
    assert(tc.ToString() == "0:0:0");
    
    // Standard valid input
    TimeCode tc2 = TimeCode(5, 30, 30);
    assert(tc2.ToString() == "5:30:30");
    
    // Roll-over test using large amount of seconds 
    TimeCode tc3 = TimeCode(2, 90, 3661);
    assert(tc3.ToString() == "4:31:1");
    
    // Roll-over test using large values 
    TimeCode tc4 = TimeCode(88, 120, 120);
    assert(tc4.ToString() == "90:2:0");
    
    // Test case for very large roll-over values
    TimeCode tc5 = TimeCode(200, 150, 3660);
    assert(tc5.ToString() == "203:31:0");
    
    // Test case for negative inputs handling
    TimeCode tc6 = TimeCode(10, 59, 3661);
    assert(tc6.ToString() == "12:0:1");
    
    cout << "PASSED!" << endl << endl;
}

void TestGetComponents(){
    cout << "Testing GetComponents" << endl;
    unsigned int h, m, s;
    
    // Regular values
    TimeCode tc = TimeCode(6, 15, 45);
    tc.GetComponents(h, m, s);
    assert(h == 6 && m == 15 && s == 45);
    
    // Edge case for zero values
    TimeCode tc2 = TimeCode(0, 0, 0);
    tc2.GetComponents(h, m, s);
    assert(h == 0 && m == 0 && s == 0);
    
    // Large value conversion test
    TimeCode tc3 = TimeCode(10, 90, 4000);
    tc3.GetComponents(h, m, s);
    assert(h == 12 && m == 36 && s == 40);
    
    // Testing roll-over conversion
    TimeCode tc4 = TimeCode(3, 75, 3661);
    tc4.GetComponents(h, m, s);
    assert(h == 5 && m == 16 && s == 1);
    
    cout << "PASSED!" << endl << endl;
}

void TestSubtract(){
    cout << "Testing Subtract" << endl;
    
    // Test case subtracting 50 minutes from 1 hour
    TimeCode tc1 = TimeCode(1, 0, 0);
    TimeCode tc2 = TimeCode(0, 50, 0);
    TimeCode tc3 = tc1 - tc2;
    assert(tc3.ToString() == "0:10:0");
    
    // Test case subtracting 1 hour 20 minutes and 1 seconds from 3 hours
    TimeCode tc6 = TimeCode(3, 40, 30);
    TimeCode tc7 = TimeCode(1, 20, 15);
    TimeCode tc8 = tc6 - tc7;
    assert(tc8.ToString() == "2:20:15");
    
    // Test case subtracting exact hours
    TimeCode tc9 = TimeCode(6, 0, 0);
    TimeCode tc10 = TimeCode(2, 0, 0);
    TimeCode tc11 = tc9 - tc10;
    assert(tc11.ToString() == "4:0:0");
    
    cout << "PASSED!" << endl << endl;
}

void TestSetMinutes(){
    cout << "Testing SetMinutes" << endl;
    
    // Changing values 
    TimeCode tc = TimeCode(9, 10, 20);
    tc.SetMinutes(25);
    assert(tc.ToString() == "9:25:20");
    
    // Edge case setting minutes to 0
    tc.SetMinutes(0);
    assert(tc.ToString() == "9:0:20");
    
    cout << "PASSED!" << endl << endl;
}

int main(){
    TestComponentsToSeconds();
    TestDefaultConstructor();
    TestComponentConstructor();
    TestGetComponents();
    TestSubtract();
    TestSetMinutes();
    
    cout << "PASSED ALL TESTS!!!" << endl;
    return 0;
}
