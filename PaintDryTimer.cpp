// Author: Wesley Ihezuo
// Date: 03/1/2025
// Class: Comp Sci III
// I Have read the notes

#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "timecode.h" // for timecode's (duh)

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
   

    // get_time_remaining
    
    // Small drying time
    {
        DryingSnapShot dss;
        dss.startTime = time(0);
        TimeCode tc = TimeCode(0, 0, 7);  // 7 seconds drying time
        dss.timeToDry = &tc;
        long long int ans = get_time_remaining(dss);
        assert(ans > 6 && ans < 8); // Should be between 6-8 seconds
    }

    // Large drying time
    {
        DryingSnapShot dss;
        dss.startTime = time(0);
        TimeCode tc = TimeCode(2, 45, 30); // 2 hours, 45 minutes, 30 seconds
        dss.timeToDry = &tc;
        long long int ans = get_time_remaining(dss);
        assert(ans > 9900 && ans < 9960); // Around 9930 seconds
    }

    // get_sphere_sa 

    // Normal radius
    {
        double sa = get_sphere_sa(2.0);
        assert(50.2654 < sa && sa < 50.2655);
    }
    // Large radius
    {
        double sa = get_sphere_sa(10.0);
        assert(1256.63 < sa && sa < 1256.65);
    }
    // Tiny radius
    {
        double sa = get_sphere_sa(0.1);
        assert(0.12 < sa && sa < 0.13);
    }
    // Extremely large radius
    {
        double sa = get_sphere_sa(250.0);
        assert(785398.0 < sa && sa < 785399.0);
    }

    // compute_time_code 

    // Small drying time 
    {
        TimeCode* tc = compute_time_code(1.0);
        assert(tc->GetTimeCodeAsSeconds() == 1);
        delete tc;
    }
    // Medium drying time
    {
        TimeCode* tc = compute_time_code(500.0);
        assert(tc->GetTimeCodeAsSeconds() == 500);
        delete tc;
    }
    // Tiny drying time
    {
        TimeCode* tc = compute_time_code(0.5);
        assert(tc->GetTimeCodeAsSeconds() == 0);
        delete tc;
    }
    // Extremely large drying time
    {
        TimeCode* tc = compute_time_code(90000.0);
        assert(tc->GetTimeCodeAsSeconds() == 90000);
        delete tc;
    }
    // drying_snap_shot_to_string 

    // Regular drying snapshot
    {
        DryingSnapShot dss;
        dss.name = "Batch-Test";
        dss.startTime = time(0);
        TimeCode tc = TimeCode(1, 15, 0);  // 1 hour, 15 minutes
        dss.timeToDry = &tc;

        string result = drying_snap_shot_to_string(dss);
        assert(result.find("Batch-Test") != string::npos);
        assert(result.find("1:15:0") != string::npos);
    }

    // Long drying snapshot
    {
        DryingSnapShot dss;
        dss.name = "MegaDry";
        dss.startTime = time(0);
        TimeCode tc = TimeCode(10, 5, 30);  // 10 hours, 5 minutes, 30 seconds
        dss.timeToDry = &tc;

        string result = drying_snap_shot_to_string(dss);
        assert(result.find("MegaDry") != string::npos);
        assert(result.find("10:5:30") != string::npos);
    }

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
    } while (choice != 'Q' && choice != 'q');//Exit program and clear batches

    // Clean up allocated memory
    for (auto& batch : batches) {
        delete batch.timeToDry;
    }
    
    return 0;
}

