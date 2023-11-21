#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

struct Vehicle12 {
    string vehicle_number;
    string owner_first_name;
    string owner_last_name;
    int owner_age;
    string owner_gender;
    string owner_address;
};

class Derived_class {
public:
    vector<Vehicle12> DB;

    Derived_class() {
        ifstream file("Q1.csv");
        if (!file.is_open()) {
            cerr << "Error opening file.\n";
            // Handle the error appropriately (e.g., throw an exception)
            return;
        }
        Vehicle12 temp;
        string line;
        getline(file, line); // skip header row

        while (getline(file, line)) {
            stringstream ss(line);
            string code, vehicle_number, o_first_name, o_last_name, o_gender, o_address;
            int o_age;
            string cmp;
            // Read each column into separate variables
            getline(ss, code, ',');
            getline(ss, vehicle_number, ',');
            cmp = code + "_" + vehicle_number;
            cmp.erase(remove(cmp.begin(), cmp.end(), '\"'), cmp.end());
            temp.vehicle_number = cmp;
            getline(ss, o_first_name, ',');
            temp.owner_first_name = o_first_name;
            getline(ss, o_last_name, ',');
            temp.owner_last_name = o_last_name;
            ss >> o_age;
            temp.owner_age = o_age;
            ss.ignore(); // Ignore the next comma
            getline(ss, o_gender, ',');
            temp.owner_gender = o_gender;
            getline(ss, o_address, ',');
            temp.owner_address = o_address;
            DB.push_back(temp);
        }
    }
};

// int main() {
//     // Create an instance of the Vehicles class
//     Derived_class vehicles;

//     // Access the vector of vehicles
//     vector<Vehicle> vehicleData = vehicles.DB;

//     // Now you can use vehicleData for further processing or printing
//     for (const auto& vehicle : vehicleData) {
//         // Print or process each vehicle
//         cout << "Vehicle Number: " << vehicle.vehicle_number << endl;
//         // Add more fields as needed
//     }

//     return 0;
// }
