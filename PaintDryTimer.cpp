// Author: Wesley Ihezuo
// Date: 03/1/2025
// Class: Comp Sci III
// I Have read the notes

#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "timecode.h"

using namespace std;

// Structure to store drying batch details
struct DryingBatch {
    string name;       // Name of batch
    time_t startTime;  // When drying started
    TimeCode* timeToDry; // How long it takes to dry
};

// Get remaining drying time in seconds
long long int get_time_remaining(DryingBatch batch) {
    time_t elapsed = time(0) - batch.startTime;
    long long int remaining = batch.timeToDry->GetTimeCodeAsSeconds() - elapsed;
    return (remaining > 0) ? remaining : 0;
}

// Convert batch info to a readable string
string batch_to_string(DryingBatch batch) {
    long long int remaining = get_time_remaining(batch);
    TimeCode remainingTime(0, 0, remaining); // Convert remaining seconds to TimeCode

    return batch.name + " (takes " + batch.timeToDry->ToString() + " to dry) time remaining: " + remainingTime.ToString();
}


// Get sphere surface area
double get_sphere_surface(double radius) {
    return 4 * M_PI * radius * radius;
}

// Compute drying time based on surface area
TimeCode* compute_time(double surfaceArea) {
    return new TimeCode(0, 0, static_cast<long long unsigned int>(surfaceArea));
}

int main() {
    vector<DryingBatch> batches;  // Stores drying batches
    char choice;
    
    do {
        cout << "Choose (A)dd, (V)iew, (Q)uit: ";
        cin >> choice;

        if (choice == 'A' || choice == 'a') {  // Add a new batch
            double radius;
            cout << "Enter radius: ";
            cin >> radius;

            double surfaceArea = get_sphere_surface(radius);
            TimeCode* dryingTime = compute_time(surfaceArea);

            batches.push_back({"Batch-" + to_string(rand()), time(0), dryingTime});
        } 
        else if (choice == 'V' || choice == 'v') {  // View batches
            for (size_t i = 0; i < batches.size(); i++) {
                cout << batch_to_string(batches[i]) << endl;

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
