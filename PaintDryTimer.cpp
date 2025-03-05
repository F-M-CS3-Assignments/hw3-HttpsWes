// Author: Wesley Ihezuo
// Date: 03/1/2025
// Class: Comp Sci III
// I Have read the notes

#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "timecode.h"

using namespace std;

// Structure to store drying snapshot details
struct DryingSnapShot {
    string name;       // Name of the batch
    time_t startTime;  // Start time of drying
    TimeCode* timeToDry; // Time required for drying
};

// Get remaining drying time in seconds
long long int get_time_remaining(DryingSnapShot dss) {
    time_t elapsed = time(0) - dss.startTime;
    long long int remaining = dss.timeToDry->GetTimeCodeAsSeconds() - elapsed;
    return (remaining > 0) ? remaining : 0;
}

// Convert drying snapshot details into a readable string
string drying_snap_shot_to_string(DryingSnapShot dss) {
    long long int remaining = get_time_remaining(dss);
    TimeCode remainingTime(0, 0, remaining); // Convert remaining seconds to TimeCode

    return dss.name + " (takes " + dss.timeToDry->ToString() + " to dry) time remaining: " + remainingTime.ToString();
}

// Compute the surface area of a sphere given its radius
double get_sphere_sa(double radius) {
    return 4 * M_PI * radius * radius;
}

// Compute the drying time based on surface area
TimeCode* compute_time_code(double surfaceArea) {
    return new TimeCode(0, 0, static_cast<long long unsigned int>(surfaceArea));
}

// Unit tests
void tests() {
    // Test get_time_remaining
    DryingSnapShot dss;
    dss.startTime = time(0);
    TimeCode tc = TimeCode(0, 0, 7);
    dss.timeToDry = &tc;
    long long int ans = get_time_remaining(dss);
    assert(ans > 6 && ans < 8);

    // Test get_sphere_sa
    double sa = get_sphere_sa(2.0);
    assert(50.2654 < sa && sa < 50.2655);

    // Test compute_time_code
    TimeCode* tc2 = compute_time_code(1.0);
    assert(tc2->GetTimeCodeAsSeconds() == 1);
    delete tc2;

    cout << "ALL TESTS PASSED!" << endl;
}

int main() {
    vector<DryingSnapShot> batches;  // Stores drying snapshots
    char choice;
    tests();  // Run unit tests

    do {
        cout << "Choose (A)dd, (V)iew, (Q)uit: ";
        cin >> choice;

        if (choice == 'A' || choice == 'a') {  // Add a new batch
            double radius;
            cout << "Enter radius: ";
            cin >> radius;

            double surfaceArea = get_sphere_sa(radius);
            TimeCode* dryingTime = compute_time_code(surfaceArea);

            batches.push_back({"Batch-" + to_string(rand()), time(0), dryingTime});
        } 
        else if (choice == 'V' || choice == 'v') {  // View batches
            for (size_t i = 0; i < batches.size(); i++) {
                cout << drying_snap_shot_to_string(batches[i]) << endl;

                // Remove dried batches
                if (get_time_remaining(batches[i]) == 0) {
                    delete batches[i].timeToDry;
                    batches.erase(batches.begin() + i);
                    i--;
                }
            }
            cout << "Tracking " << batches.size() << " batches." << endl;
        }
    } while (choice != 'Q' && choice != 'q');

    // Clean up allocated memory
    for (auto& batch : batches) {
        delete batch.timeToDry;
    }
    
    return 0;
}

