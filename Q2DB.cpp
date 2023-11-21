#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class TrafficViolation {
public:
    string car_number;
    string type_of_report;
    string report_location;

    TrafficViolation(string car_num, string report_type, string location)
        : car_number(move(car_num)), type_of_report(move(report_type)), report_location(move(location)) {}

    void display_info() const {
        cout << "Car Number: " << car_number << "\n";
        cout << "Type of Report: " << type_of_report << "\n";
        cout << "Report Location: " << report_location << "\n\n";
    }
};

class TrafficViolationManager {
public:
    vector<TrafficViolation> violations;

    void add_violation(const TrafficViolation& violation) {
        violations.push_back(violation);
    }

    void print_all_violations() const {
        for (const auto& violation : violations) {
            violation.display_info();
        }
    }
};

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
        string car_number, type_of_report, report_location;
        string code;

        // Read the entire car number including commas
        getline(ss, code, ',');
        getline(ss, car_number, ',');
        string cmp = code + " " + car_number;
        getline(ss, type_of_report, ',');
        getline(ss, report_location);

        TrafficViolation violation(cmp, type_of_report, report_location);
        violation_manager.add_violation(violation);
    }

    // Display information about all traffic violations
    violation_manager.print_all_violations();

    return 0;
}
