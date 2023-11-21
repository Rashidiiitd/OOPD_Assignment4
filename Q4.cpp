#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Challenge {
private:
    struct Evidence {
        string date;
        string issue;
        string punishments;
        string vehicle_number;  
        string type;           
        string location;        
    };

    struct Person {
        string fname = " ";
        string lname = " ";
        int age;
        int cases;  // New attribute
        vector<Evidence> evidenceList;
    };

    struct ChallengeCase {
        int id;
        vector<string> witnesses;
        Evidence violationDetails;
        string responseText;
        string priorInfo;
    };

public:
    vector<Person> persons;
    vector<ChallengeCase> challengeCases;

    void find(string fname, string lname) {
        for (int i = 0; i < persons.size(); i++) {
            if ((persons[i].fname == fname) && (persons[i].lname == lname)) {
                Evidence newEvidence;
                cout << "Issue happened date  : ";
                cin >> newEvidence.date;
                cout << "Issue happened : ";
                cin >> newEvidence.issue;
                cout << "Action performed : ";
                cin >> newEvidence.punishments;
                cout << "Enter vehicle number: ";
                cin >> newEvidence.vehicle_number;
                cout << "Enter type of violation: ";
                cin >> newEvidence.type;
                cout << "Enter location of violation: ";
                cin.ignore();
                getline(cin, newEvidence.location);

                persons[i].evidenceList.push_back(newEvidence);
                persons[i].cases++;  // Increment the number of cases against the person

                return;
            }
        }
        cout << "Evidence is not present " << endl;
        insert(fname, lname);
    }

    void insert(string fname, string lname) {
        Person newPerson;
        newPerson.fname = fname;
        newPerson.lname = lname;

        cout << "Age of the performer : ";
        cin >> newPerson.age;

        Evidence newEvidence;
        cout << "Issue happened date  : ";
        cin >> newEvidence.date;
        cout << "Issue happened : ";
        cin >> newEvidence.issue;
        cout << "Action performed : ";
        cin >> newEvidence.punishments;
        cout << "Enter vehicle number: ";
        cin >> newEvidence.vehicle_number;
        cout << "Enter type of violation: ";
        cin >> newEvidence.type;
        cout << "Enter location of violation: ";
        cin.ignore();
        getline(cin, newEvidence.location);

        newPerson.evidenceList.push_back(newEvidence);
        newPerson.cases = 1;  // Initialize the number of cases to 1 for the new person

        persons.push_back(newPerson);
    }

    void print() {
        if (persons.empty()) {
            cout << "Evidence is not present ";
        } else {
            for (int i = 0; i < persons.size(); i++) {
                cout << i + 1 << ". First name is : " << persons[i].fname << endl;
                cout << i + 1 << ". Last name is : " << persons[i].lname << endl;
                cout << i + 1 << ". Age is : " << persons[i].age << endl;
                cout << i + 1 << ". Number of cases : " << persons[i].cases << endl;

                for (int j = 0; j < persons[i].evidenceList.size(); j++) {
                    cout << "\t\t" << j + 1 << ". Case Date : " << persons[i].evidenceList[j].date << endl;
                    cout << "\t\t" << j + 1 << ". Issue Happened : " << persons[i].evidenceList[j].issue << endl;
                    cout << "\t\t" << j + 1 << ". Action Done : " << persons[i].evidenceList[j].punishments << endl;
                    cout << "\t\t" << j + 1 << ". Vehicle number: " << persons[i].evidenceList[j].vehicle_number << endl;
                    cout << "\t\t" << j + 1 << ". Type of violation: " << persons[i].evidenceList[j].type << endl;
                    cout << "\t\t" << j + 1 << ". Location of violation: " << persons[i].evidenceList[j].location << endl;
                }
            }
        }
    }

    void addChallengeCase() {
        ChallengeCase newChallengeCase;
        newChallengeCase.id = challengeCases.size() + 1;

        cout << "Enter the number of witnesses for the challenge case: ";
        int numWitnesses;
        cin >> numWitnesses;
        cin.ignore();

        for (int i = 0; i < numWitnesses; ++i) {
            string witnessName;
            cout << "Enter witness name: ";
            getline(cin, witnessName);
            newChallengeCase.witnesses.push_back(witnessName);
        }

        cout << "Enter challenge case details:\n";
        cout << "Enter date: ";
        cin >> newChallengeCase.violationDetails.date;
        cout << "Enter issue: ";
        cin.ignore();
        getline(cin, newChallengeCase.violationDetails.issue);
        cout << "Enter punishments: ";
        getline(cin, newChallengeCase.violationDetails.punishments);
        cout << "Enter vehicle number: ";
        cin >> newChallengeCase.violationDetails.vehicle_number;
        cout << "Enter type of violation: ";
        cin >> newChallengeCase.violationDetails.type;
        cout << "Enter location of violation: ";
        cin.ignore();
        getline(cin, newChallengeCase.violationDetails.location);
        cout << "Enter response text: ";
        getline(cin, newChallengeCase.responseText);
        cout << "Enter prior information: ";
        getline(cin, newChallengeCase.priorInfo);

        challengeCases.push_back(newChallengeCase);
    }

    void displayCriminalRecord(const ChallengeCase& challengeCase) {
        cout << "\n***** Criminal Record *****\n";
        cout << "Case ID: " << challengeCase.id << endl;
        cout << "Witnesses:\n";
        for (const string& witness : challengeCase.witnesses) {
            cout << "\t- " << witness << endl;
        }
        cout << "Violation Details:\n";
        cout << "\t- Date: " << challengeCase.violationDetails.date << endl;
        cout << "\t- Issue: " << challengeCase.violationDetails.issue << endl;
        cout << "\t- Punishments: " << challengeCase.violationDetails.punishments << endl;
        cout << "\t- Vehicle number: " << challengeCase.violationDetails.vehicle_number << endl;
        cout << "\t- Type of violation: " << challengeCase.violationDetails.type << endl;
        cout << "\t- Location of violation: " << challengeCase.violationDetails.location << endl;
        cout << "Response Text: " << challengeCase.responseText << endl;
        cout << "Prior Information: " << challengeCase.priorInfo << endl;
    }
};

int main() {
    Challenge c1;
    int choice;

    while (1) {
        cout << "\n***** Police Record System *****\n";
        cout << "Enter 1 for inserting the information\n";
        cout << "Enter 2 for printing the information\n";
        cout << "Enter 3 for adding a challenge case\n";
        cout << "Enter 4 for displaying criminal record by Person name\n";
        cout << "Enter 5 for displaying criminal record by Person ID\n";
        cout << "Enter any number to exit\n";
        cout << "Enter the choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nEnter the information:\n";
                string fname = "", lname = "";
                cout << "Enter the first name of the person: ";
                cin >> fname;
                cout << "Enter the last name of the person: ";
                cin >> lname;
                c1.find(fname, lname);
                break;
            }
            case 2: {
                cout << "\nThe existing data is:\n";
                c1.print();
                break;
            }
            case 3: {
                cout << "\nAdding a challenge case:\n";
                c1.addChallengeCase();
                break;
            }
            case 4: {
                cout << "\nEnter the person name to display criminal record: ";
                string fname, lname;
                cout << "Enter the first name of the person: ";
                cin >> fname;
                cout << "Enter the last name of the person: ";
                cin >> lname;
                bool found = false;
                for (const auto& person : c1.persons) {
                    if (person.fname == fname && person.lname == lname) {
                        for (const auto& evidence : person.evidenceList) {
                            cout << "\n***** Criminal Record *****\n";
                            cout << "Issue happened date: " << evidence.date << endl;
                            cout << "Issue happened: " << evidence.issue << endl;
                            cout << "Action performed: " << evidence.punishments << endl;
                            cout << "Vehicle number: " << evidence.vehicle_number << endl;
                            cout << "Type of violation: " << evidence.type << endl;
                            cout << "Location of violation: " << evidence.location << endl;
                            found = true;
                        }
                        break;
                    }
                }
                if (!found) {
                    cout << "Criminal record not found for the person.\n";
                }
                break;
            }
            case 5: {
                cout << "\nEnter the person ID to display criminal record: ";
                int personID;
                cin >> personID;
                if (personID > 0 && personID <= c1.persons.size()) {
                    const auto& person = c1.persons[personID - 1];
                    for (const auto& evidence : person.evidenceList) {
                        cout << "\n***** Criminal Record *****\n";
                        cout << "Issue happened date: " << evidence.date << endl;
                        cout << "Issue happened: " << evidence.issue << endl;
                        cout << "Action performed: " << evidence.punishments << endl;
                        cout << "Vehicle number: " << evidence.vehicle_number << endl;
                        cout << "Type of violation: " << evidence.type << endl;
                        cout << "Location of violation: " << evidence.location << endl;
                    }
                } else {
                    cout << "Invalid person ID.\n";
                }
                break;
            }
            default: {
                cout << "Exiting the Police Record System.\n";
                exit(0);
            }
        }
    }

    return 0;
}
