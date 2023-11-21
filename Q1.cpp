#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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
    Vehicle(const string& v_number, const string& o_first_name, const string& o_last_name, int o_age, const string& o_gender, const string& o_address)
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

class TrafficDepartment {
public:
    vector<Vehicle> vehicles;

    // Add a vehicle to the traffic department's list
    void add_vehicle(const Vehicle& vehicle) {
        vehicles.push_back(vehicle);
    }

    // Display information about all vehicles in the traffic department
    void print_all_vehicles() const {
    int count = 0;
    for (const auto& vehicle : vehicles) {
        vehicle.display_info();
        count++;
        if (count >= 10) {
            break;
        }
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

    while (getline(file, line)) {
    stringstream ss(line);
    string code, vehicle_number, o_first_name, o_last_name, o_gender, o_address;
    int o_age;
    string cmp;
    // Read each column into separate variables
    getline(ss, code, ',');
   // cout<<code<<endl;
    getline(ss, vehicle_number, ',');
    //cout<<vehicle_number<<endl;
    cmp= code + " " + vehicle_number;
   // cout<<cmp<<endl;
    getline(ss, o_first_name, ',');
    //cout<<o_first_name<<endl;
    getline(ss, o_last_name, ',');
    //cout<<o_last_name<<endl;
    ss >> o_age;
   // cout<<o_age<<endl;
    ss.ignore(); // Ignore the next comma
    getline(ss, o_gender, ',');
    //cout<<o_gender<<endl;
    getline(ss, o_address, ',');
   // cout<<o_address<<endl;

    // Create a Vehicle object and add it to the traffic department
    Vehicle vehicle(cmp, o_first_name, o_last_name, o_age, o_gender, o_address);
    traffic_department.add_vehicle(vehicle);
}

    // Display information about all vehicles in the traffic department
   traffic_department.print_all_vehicles();

    return 0;
}

