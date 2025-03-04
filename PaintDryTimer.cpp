// Author: Wesley Ihezuo
// Date: 02/28/2025
// Class: Comp Sci III

#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

struct DryingSnapShot {
    string name;
    time_t startTime;
    double dryingTimeInSeconds;
};

double get_sphere_sa(double rad) {
    return 4 * M_PI * rad * rad;
}

int main() {
    vector<DryingSnapShot> dryingBatches;
    char option;
    do {
        cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
        cin >> option;
        if (option == 'A' || option == 'a') {
            double radius;
            cout << "radius: ";
            cin >> radius;
            double surfaceArea = get_sphere_sa(radius);
            dryingBatches.push_back({"Batch-" + to_string(rand()), time(0), surfaceArea});
        } else if (option == 'V' || option == 'v') {
            for (const auto& batch : dryingBatches) {
                cout << batch.name << " (takes " << batch.dryingTimeInSeconds << " seconds to dry)" << endl;
            }
            cout << dryingBatches.size() << " batches being tracked." << endl;
        }
    } while (option != 'Q' && option != 'q');

    return 0;
}

