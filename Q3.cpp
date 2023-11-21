#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "Q1DB.h"  // Include necessary headers
#include "CSV3Db.h"
using namespace std;

// Helper function to trim leading and trailing whitespaces
string trim(const string &str) {
    auto start = find_if_not(str.begin(), str.end(), [](unsigned char c) {
        return isspace(c);
    });

    auto end = find_if_not(str.rbegin(), str.rend(), [](unsigned char c) {
        return isspace(c);
    }).base();

    return (start < end ? string(start, end) : string());
}

struct TrafficViolation {
    string car_number;
    string type_of_report;
    string report_location;

    TrafficViolation(const string &car_num, const string &report_type, const string &location)
        : car_number(car_num), type_of_report(report_type), report_location(location) {}

    void display_info() const {
        cout << "Car Number: " << car_number << "\n";
        cout << "Type of Report: " << type_of_report << "\n";
        cout << "Report Location: " << report_location << "\n\n";
    }
};

class TrafficViolationManager : public Derived_class, public Derived_class1 {
public:
    vector<TrafficViolation> violations;

    void add_violation(const TrafficViolation &violation) {
        violations.push_back(violation);
    }

   void search_car(string car_number) {
        bool found = false;
        for (auto &violation : DB) {
            if (violation.vehicle_number == car_number) {
                cout << "***   Previous Details    ***" << endl;
                cout << "Vehicle Number ->  ";
                cout << violation.vehicle_number << endl;
                cout << "Owner_First_Name ->  ";
                string A = violation.owner_first_name;
                cout << violation.owner_first_name << endl;
                cout << "Owner_Last_Name -> ";
                string B = violation.owner_last_name;
                cout << violation.owner_last_name << endl;
                cout << "Owner_Age ->  ";
                cout << violation.owner_age << endl;
                cout << "Owner_Gender -> ";
                cout << violation.owner_gender << endl;
                cout << "Owner_Address ->  ";
                cout << violation.owner_address << endl;
                cout << "U got respond from Victim Press 1 if get otherwise 0" << endl;
                int n;
                cin >> n;
                if (n == 1) {
                    cout << "Victim got responded so no need for a new address " << endl;
                    found = true;
                    break;
                }
                if (n == 0) {
                    cout << "  -- Wait Searching for New address -->> " << endl;
                    for (auto &violation1 : DB1) {
                        if (violation1.owner_first_name == A && violation1.owner_last_name == B) {
                            cout << "***   NEW ADDRESS is   ->   ***" << endl;
                            cout << violation1.owner_address << endl;
                            found = true;
                            break; // Stop searching after finding the first match
                        }
                    }
                }
            }
        }

        if (!found) {
            cout << "Record not found for Car Number: " << car_number << endl;
        } else {
            cout << "  -- Address Search Complete -->> " << endl;
        }
    };



    void print_all_violations() const {
        int count = 0;
        for (const auto &violation : violations) {
            violation.display_info();
            ++count;
            if (count == 10) {
                break; // Stop printing after the first 10 violations
            }
        }
    }
};

class Vehicle {
public:
    string vehicle_number; // Combined value of the first two columns
    string owner_first_name;
    string owner_last_name;
    int owner_age;
    string owner_gender;
    string owner_address;

    // Constructor to initialize the Vehicle object
    Vehicle(const string &v_number, const string &o_first_name, const string &o_last_name, int o_age, const string &o_gender, const string &o_address)
        : vehicle_number(v_number), owner_first_name(o_first_name), owner_last_name(o_last_name), owner_age(o_age), owner_gender(o_gender), owner_address(o_address) {}

    // Display information about the vehicle and its owner
    void display_info() const {
        cout << "Vehicle Number: " << vehicle_number << "\n";
        cout << "Owner Name: " << owner_first_name << " " << owner_last_name << "\n";
        cout << "Age: " << owner_age << "\n";
        cout << "Gender: " << owner_gender << "\n";
        cout << "Address: " << owner_address << "\n\n";
    }
};

void displayMenu() {
    cout << "Menu:\n";
    cout << "1. Display all violations\n";
    cout << "2. Search for a violation by car number\n";
    cout << "3. Exit\n";
}

int main() {
    TrafficViolationManager violation_manager;

    ifstream file("Evidence_report.csv");
    if (!file.is_open()) {
        cerr << "Error opening file.\n";
        return 1;
    }

    string line;
    getline(file, line); // skip header row

    while (getline(file, line)) {
        stringstream ss(line);
        string code, car_number, type_of_report, report_location;

        // Read the entire car number including commas
        getline(ss, code, ',');
        getline(ss, car_number, ',');

        // Remove double quotes and leading/trailing whitespaces from car_number
        car_number = trim(car_number);

        getline(ss, type_of_report, ',');
        getline(ss, report_location);

        string cmp = code + "_" + car_number;
        cmp.erase(std::remove(cmp.begin(), cmp.end(), '\"'), cmp.end());
        TrafficViolation violation(cmp, type_of_report, report_location);
        violation_manager.add_violation(violation);
    }

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            violation_manager.print_all_violations();
            break;
        case 2: {
            string target_car_number;
            cout << "Enter car number to search: ";
            cin >> target_car_number;
            violation_manager.search_car(target_car_number);
            break;
        }
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}
