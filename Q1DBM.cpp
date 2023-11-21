#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Vehicle {
public:
    string vehicle_number; // Combined value of the first two columns
    string owner_first_name;
    string owner_last_name;
    int owner_age;
    string owner_gender;
    string owner_address;

    // Constructor to initialize the Vehicle object
    Vehicle( string& v_number,  string& o_first_name,  string& o_last_name, int o_age, string& o_gender, string& o_address)
        : vehicle_number(v_number), owner_first_name(o_first_name), owner_last_name(o_last_name), owner_age(o_age), owner_gender(o_gender), owner_address(o_address) {}

    // Display information about the vehicle and its owner
    void display_info() const {
        cout << "Vehicle Number: " << vehicle_number << "\n";
        cout << "Owner Name: " << owner_first_name << " " << owner_last_name << "\n";
        cout << "Age: " << owner_age << "\n";
        cout << "Gender: " << owner_gender << "\n";
        cout << "Address: " << owner_address << "\n\n";
    }

    // Modify owner information
    void modify_owner_info(string& new_first_name, string& new_last_name, string& new_gender,  string& new_address) {
        owner_first_name = new_first_name;
        owner_last_name = new_last_name;
        owner_gender = new_gender;
        owner_address = new_address;
    }
};

class TrafficDepartment {
public:
    vector<Vehicle> vehicles;

    // Add a vehicle to the traffic department's list
    void add_vehicle( Vehicle& vehicle) {
        vehicles.push_back(vehicle);
    }

    // Display information about all vehicles in the traffic department
    void print_all_vehicles() const {
        int count = 0;
        for ( auto& vehicle : vehicles) {
            vehicle.display_info();
            count++;
            if (count >= 10) {
                break;
            }
        }
    }

    // Filter vehicles based on age
    vector<Vehicle> filter_vehicles_by_age(int min_age, int max_age) const {
        vector<Vehicle> filtered_vehicles;
        for ( auto& vehicle : vehicles) {
            if (vehicle.owner_age >= min_age && vehicle.owner_age <= max_age) {
                filtered_vehicles.push_back(vehicle);
            }
        }
        return filtered_vehicles;
    }

    // Sort vehicles by age
    void sort_vehicles_by_age() {
        sort(vehicles.begin(), vehicles.end(), []( Vehicle& a,  Vehicle& b) {
            return a.owner_age < b.owner_age;
        });
    }

    // Modify owner information based on vehicle number
    void modify_owner_info(string& vehicle_number, string& new_first_name, string& new_last_name,  string& new_gender, string& new_address) {
        auto it = find_if(vehicles.begin(), vehicles.end(), [vehicle_number](const Vehicle& v) {
            return v.vehicle_number == vehicle_number;
        });

        if (it != vehicles.end()) {
            it->modify_owner_info(new_first_name, new_last_name, new_gender, new_address);
            cout << "Owner information modified successfully.\n";
        } else {
            cout << "Vehicle not found.\n";
        }
    }

    // Search for a vehicle by vehicle number
    void search_vehicle_by_number( string& vehicle_number)  {
        auto it = find_if(vehicles.begin(), vehicles.end(), [vehicle_number](const Vehicle& v) {
            return v.vehicle_number == vehicle_number;
        });

        if (it != vehicles.end()) {
            cout << "Vehicle found:\n";
            it->display_info();
        } else {
            cout << "Vehicle not found.\n";
        }
    }

    // Add a new vehicle
    void add_new_vehicle() {
        string vehicle_number, o_first_name, o_last_name, o_gender, o_address;
        int o_age;

        cout << "Enter vehicle number: ";
        cin >> vehicle_number;
        cout << "Enter owner first name: ";
        cin >> o_first_name;
        cout << "Enter owner last name: ";
        cin >> o_last_name;
        cout << "Enter owner age: ";
        cin >> o_age;
        cout << "Enter owner gender: ";
        cin >> o_gender;
        cout << "Enter owner address: ";
        cin.ignore(); // Clear the newline from the buffer
        getline(cin, o_address);

        Vehicle new_vehicle(vehicle_number, o_first_name, o_last_name, o_age, o_gender, o_address);
        add_vehicle(new_vehicle);
        cout << "New vehicle added successfully.\n";
    }

    // Delete a vehicle based on vehicle number
    void delete_vehicle(const string& vehicle_number) {
        auto it = find_if(vehicles.begin(), vehicles.end(), [vehicle_number](const Vehicle& v) {
            return v.vehicle_number == vehicle_number;
        });

        if (it != vehicles.end()) {
            vehicles.erase(it);
            cout << "Vehicle deleted successfully.\n";
        } else {
            cout << "Vehicle not found.\n";
        }
    }
};

int main() {
    TrafficDepartment traffic_department;

    ifstream file("Q1.csv");
    if (!file.is_open()) {
        cerr << "Error opening file.\n";
        return 1;
    }

    string line;
    getline(file, line); // skip header row
    string cmp;
    while (getline(file, line)) {
        stringstream ss(line);
        string code, vehicle_number, o_first_name, o_last_name, o_gender, o_address;
        int o_age;

        // Read each column into separate variables
        getline(ss, code, ',');
        getline(ss, vehicle_number, ',');
        cmp = code + "_" + vehicle_number;
        getline(ss, o_first_name, ',');
        getline(ss, o_last_name, ',');
        ss >> o_age;
        ss.ignore(); // Ignore the next comma
        getline(ss, o_gender, ',');
        getline(ss, o_address, ',');

        // Create a Vehicle object and add it to the traffic department
        Vehicle vehicle(cmp, o_first_name, o_last_name, o_age, o_gender, o_address);
        traffic_department.add_vehicle(vehicle);
    }

    int choice;
    do {
        cout << "1. Display all vehicles\n";
        cout << "2. Filter vehicles by age\n";
        cout << "3. Sort vehicles by age\n";
        cout << "4. Modify owner information\n";
        cout << "5. Search vehicle by number\n";
        cout << "6. Add new vehicle\n";
        cout << "7. Delete vehicle\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                traffic_department.print_all_vehicles();
                break;
            case 2: {
                int min_age, max_age;
                cout << "Enter minimum age: ";
                cin >> min_age;
                cout << "Enter maximum age: ";
                cin >> max_age;
                vector<Vehicle> filtered_vehicles = traffic_department.filter_vehicles_by_age(min_age, max_age);
                cout << "Filtered vehicles:\n";
                for (const auto& vehicle : filtered_vehicles) {
                    vehicle.display_info();
                }
                break;
            }
            case 3:
                traffic_department.sort_vehicles_by_age();
                cout << "Vehicles sorted by age:\n";
                traffic_department.print_all_vehicles();
                break;
            case 4: {
                string vehicle_number, new_first_name, new_last_name, new_gender, new_address;
                cout << "Enter vehicle number to modify: ";
                cin >> vehicle_number;
                cout << "Enter new first name: ";
                cin >> new_first_name;
                cout << "Enter new last name: ";
                cin >> new_last_name;
                cout << "Enter new gender: ";
                cin >> new_gender;
                cout << "Enter new address: ";
                cin.ignore(); // Clear the newline from the buffer
                getline(cin, new_address);
                traffic_department.modify_owner_info(vehicle_number, new_first_name, new_last_name, new_gender, new_address);
                break;
            }
            case 5: {
                string vehicle_number;
                cout << "Enter vehicle number to search: ";
                cin >> vehicle_number;
                traffic_department.search_vehicle_by_number(vehicle_number);
                break;
            }
            case 6:
                traffic_department.add_new_vehicle();
                break;
            case 7: {
                string vehicle_number;
                cout << "Enter vehicle number to delete: ";
                cin >> vehicle_number;
                traffic_department.delete_vehicle(vehicle_number);
                break;
            }
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 8);

    return 0;
}
