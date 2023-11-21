#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

struct Vehicle123 {
    string owner_first_name;
    string owner_last_name;
    int owner_age;
    string owner_gender;
    string owner_address;
};

class Derived_class1 {
public:
    vector<Vehicle123> DB1;

    Derived_class1() {
        ifstream file("another.csv");
        if (!file.is_open()) {
            cerr << "Error opening file.\n";
            // Handle the error appropriately (e.g., throw an exception)
            return;
        }

        Vehicle123 temp;
        string line;
        getline(file, line); // skip header row

        while (getline(file, line)) {
            stringstream ss(line);
            string o_first_name, o_last_name, o_gender, o_address;
            int o_age;

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

            DB1.push_back(temp);
        }
    }
};
