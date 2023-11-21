#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class TrafficViolation {
public:
    string car_number;
    string type_of_report;
    string report_location;

    TrafficViolation(string car_num, string report_type, string location)
        : car_number(move(car_num)), type_of_report(move(report_type)), report_location(move(location)) {}

    void display_info() {
        cout << "Car Number: " << car_number << "\n";
        cout << "Type of Report: " << type_of_report << "\n";
        cout << "Report Location: " << report_location << "\n\n";
    }

    void modifyCarNumber(string new_car_number) {
        car_number = move(new_car_number);
    }

    void modifyTypeOfReport(string new_type_of_report) {
        type_of_report = move(new_type_of_report);
    }

    void modifyReportLocation(string new_report_location) {
        report_location = move(new_report_location);
    }
};

class TrafficViolationManager {
public:
    vector<TrafficViolation> violations;

    void addViolation(TrafficViolation violation) {
        violations.push_back(move(violation));
    }

    void deleteViolation(string car_number) {
        auto it = remove_if(violations.begin(), violations.end(), [car_number](const TrafficViolation& v) {
            return v.car_number == car_number;
        });

        violations.erase(it, violations.end());
    }

    void printAllViolations() {
        for (auto& violation : violations) {
            violation.display_info();
        }
    }

    TrafficViolation& findViolationByCombinedVariable(string combined_variable) {
        auto it = find_if(violations.begin(), violations.end(), [combined_variable](TrafficViolation& v) {
            return v.car_number == combined_variable;
        });

        if (it != violations.end()) {
            return *it;
        } else {
            cerr << "Violation not found.\n";
            // Returning a reference to the first violation (dummy violation) for simplicity
            return violations[0];
        }
    }

    void showViolationReportByCarNumber(string car_number) {
        auto it = find_if(violations.begin(), violations.end(), [car_number](const TrafficViolation& v) {
            return v.car_number == car_number;
        });

        if (it != violations.end()) {
            it->display_info();
        } else {
            cerr << "Violation report not found for the given car number.\n";
        }
    }
};

void displayMenu() {
    cout << "1. Display all violations\n";
    cout << "2. Add a new violation\n";
    cout << "3. Delete a violation by car number\n";
    cout << "4. Modify car number\n";
    cout << "5. Modify type of report\n";
    cout << "6. Modify report location\n";
    cout << "7. Show violation report by combined variable\n";
    cout << "8. Show violation report by car number\n";
    cout << "9. Exit\n";
}

int main() {
    TrafficViolationManager violationManager;

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
        string cmp = code + car_number;
        getline(ss, type_of_report, ',');
        getline(ss, report_location);

        TrafficViolation violation(move(car_number), move(type_of_report), move(report_location));
        violationManager.addViolation(move(violation));
    }

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                violationManager.printAllViolations();
                break;
            case 2: {
                string car_number, type_of_report, report_location;
                cout << "Enter car number: ";
                cin >> car_number;
                cout << "Enter type of report: ";
                cin >> type_of_report;
                cout << "Enter report location: ";
                cin >> report_location;

                TrafficViolation newViolation(move(car_number), move(type_of_report), move(report_location));
                violationManager.addViolation(move(newViolation));
                break;
            }
            case 3: {
                string target_car_number;
                cout << "Enter car number to delete: ";
                cin >> target_car_number;
                violationManager.deleteViolation(move(target_car_number));
                break;
            }
            case 4: {
                string target_combined_variable, new_car_number;
                cout << "Enter combined variable to modify: ";
                cin >> target_combined_variable;
                TrafficViolation& targetViolation = violationManager.findViolationByCombinedVariable(move(target_combined_variable));
                cout << "Enter new car number: ";
                cin >> new_car_number;
                targetViolation.modifyCarNumber(move(new_car_number));
                break;
            }
            case 5: {
                string target_combined_variable, new_type_of_report;
                cout << "Enter combined variable to modify: ";
                cin >> target_combined_variable;
                TrafficViolation& targetViolation = violationManager.findViolationByCombinedVariable(move(target_combined_variable));
                cout << "Enter new type of report: ";
                cin >> new_type_of_report;
                targetViolation.modifyTypeOfReport(move(new_type_of_report));
                break;
            }
            case 6: {
                string target_combined_variable, new_report_location;
                cout << "Enter combined variable to modify: ";
                cin >> target_combined_variable;
                TrafficViolation& targetViolation = violationManager.findViolationByCombinedVariable(move(target_combined_variable));
                cout << "Enter new report location: ";
                cin >> new_report_location;
                targetViolation.modifyReportLocation(move(new_report_location));
                break;
            }
            case 7: {
                string target_combined_variable;
                cout << "Enter combined variable to show report: ";
                cin >> target_combined_variable;
                TrafficViolation& targetViolation = violationManager.findViolationByCombinedVariable(move(target_combined_variable));
                targetViolation.display_info();
                break;
            }
            case 8: {
                string target_car_number;
                cout << "Enter car number to show report: ";
                cin >> target_car_number;
                violationManager.showViolationReportByCarNumber(move(target_car_number));
                cout<<"Successfully Show the report";
                break;
            }
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 9);

    return 0;
}
