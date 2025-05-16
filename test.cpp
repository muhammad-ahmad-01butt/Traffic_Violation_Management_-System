#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int MAX_RECORDS = 100;
struct Violation {
    string personID;
    string violationType;
    long long fineAmount;
    string violationDate;
    string location;
};
Violation violations[MAX_RECORDS];
int violationCount = 0;
const string ADMIN_USERNAME = "Muhammad Ahmad";
const string ADMIN_PASSWORD = "123456";

bool adminLogin() {
    string username, password;
    cin.ignore(); 
    cout << "Enter Admin Username: ";
    getline(cin, username);
    cout << "Enter Admin Password: ";
    getline(cin, password);
    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        cout << "Login successful! Welcome Muhammad Ahmad.\n";
        return true;
    } else {
        cout << "Invalid credentials! Access denied.\n";
        return false;
    }
}
void saveToFile() {
    ofstream myfile("violations.txt", ios::app); 
    if (!myfile) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }
    myfile << violations[violationCount - 1].personID << endl
           << violations[violationCount - 1].violationType << endl
           << violations[violationCount - 1].fineAmount << endl
           << violations[violationCount - 1].violationDate << endl
           << violations[violationCount - 1].location << endl;
    myfile.close();
}
void loadFromFile() {
    ifstream myfile("violations.txt");
    if (!myfile) {
        cout << "No previous records found.\n";
        return;
    }
    while (getline(myfile, violations[violationCount].personID)) {
        getline(myfile, violations[violationCount].violationType);
        myfile >> violations[violationCount].fineAmount;
        myfile.ignore();
        getline(myfile, violations[violationCount].violationDate);
        getline(myfile, violations[violationCount].location);
        violationCount++;
    }
    myfile.close();
}

void addViolation(string id, string violation, long long fine, string date, string location) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        cout << "Error: Date must be in the format YYYY-MM-DD.\n";
        return;
    }

    if (violationCount < MAX_RECORDS) {
        violations[violationCount].personID = id;
        violations[violationCount].violationType = violation;
        violations[violationCount].fineAmount = fine;
        violations[violationCount].violationDate = date;
        violations[violationCount].location = location;
        violationCount++;
        saveToFile();
        cout << "Violation record added successfully.\n";
    } else {
        cout << "Record limit reached. Cannot add more violations.\n";
    }
}
void displayViolations(string id) {
    int count = 0;
    cout << "Violations for Person ID: " << id << endl;
    for (int i = 0; i < violationCount; i++) {
        if (violations[i].personID == id) {
            cout << "|Violation Type|: |" << violations[i].violationType << "|  "
                 << "|Fine Amount|: |" << violations[i].fineAmount << "|  "
                 << "|Location|: |" << violations[i].location << "|  "
                 << "|Violation Date|: |" << violations[i].violationDate << "|  " << endl;
            cout << endl;
            count++;
        }
    }
    if (count == 0) {
        cout << "No violations found for Person ID: " << id << endl;
    } else {
        cout << "Total violations for Person ID " << id << ": " << count << endl;
    }
}
void calculateTotalFine(string id) {
    long long totalFine = 0;
    int count = 0;
    for (int i = 0; i < violationCount; i++) {
        if (violations[i].personID == id) {
            totalFine += violations[i].fineAmount;
            count++;
        }
    }
    if (count > 0) {
        cout << "Total fine for Person ID " << id << " is: " << totalFine << endl;
    } else {
        cout << "No violations found for Person ID: " << id << endl;
    }
}
int main() {
    loadFromFile();
    cout << "****************************************************PUNJAB TRAFFIC POLICE"
         << "***********************************************" << endl
         << endl;
    int choice;
    bool isAdmin = false;
    do {
        cout << "*****************************************TRAFFIC VIOLATION MANAGEMENT SYSTEM"
             << "**************************************" << endl
             << endl;
        if (!isAdmin) {
            cout << "1. Admin Login\n";
        }
        cout << "2. Display Violations for a Person\n";
        cout << "3. Calculate Total Fine for a Person\n";
        if (isAdmin) {
            cout << "4. Add Violation Record (Admin Only)\n";
        }
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (!isAdmin) {
                    isAdmin = adminLogin();
                } else {
                    cout << "You are already logged in as Admin.\n";
                }
                break;
            case 2: {
                string id;
                cout << "Enter Person ID: ";
                cin >> id;
                displayViolations(id);
                break;
            }
            case 3: {
                string id;
                cout << "Enter Person ID: ";
                cin >> id;
                calculateTotalFine(id);
                break;
            }
            case 4:
                if (isAdmin) {
                    string id, violation, date, location;
                    long long fine;
                    cout << "Enter Person ID: ";
                    cin >> id;
                    cin.ignore();
                    cout << "Enter Violation Type: ";
                    getline(cin, violation);
                    cout << "Enter Fine Amount: ";
                    cin >> fine;
                    cin.ignore();
                    cout << "Enter Violation Date (YYYY-MM-DD): ";
                    getline(cin, date);
                    cout << "Enter Location: ";
                    getline(cin, location);
                    addViolation(id, violation, fine, date, location);
                } else {
                    cout << "Admin access required to add violation records.\n";
                }
                break;
            case 5:
                cout << "Exiting the system...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
    return 0;
}