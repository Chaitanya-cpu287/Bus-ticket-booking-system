#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip> // Essential for formatting the box and tables

using namespace std;

// Class to handle individual Ticket logic
class Ticket {
private:
    string boarding, destination;
    float distance, fare;
    string driverID, conductorID, depot;
    string dateTime;

public:
    Ticket() : distance(0), fare(0) {}

    // Captures trip details from the user
    void inputDetails() {
        cout << "\n--- Generate New Ticket ---\n";
        cout << "Enter Boarding Point : "; cin >> boarding;
        cout << "Enter Destination    : "; cin >> destination;
        cout << "Enter Distance (km)  : "; cin >> distance;

        // Logic: Rs. 2.5 per kilometer
        fare = distance * 2.5;

        // Get current system time
        time_t now = time(0);
        char* dt = ctime(&now);
        dateTime = string(dt);
        if (!dateTime.empty()) dateTime.pop_back(); // Remove newline character
    }

    // Links the bus staff info to the specific ticket
    void setBusStaff(string dID, string cID, string dep) {
        driverID = dID;
        conductorID = cID;
        depot = dep;
    }

    float getFare() const { return fare; }

    // Displays the ticket on the console screen
    void displayOnScreen() const {
        cout << "\n[Screen Output]" << endl;
        cout << "----------------------------" << endl;
        cout << "  RTC BUS TICKET GENERATED" << endl;
        cout << "----------------------------" << endl;
        cout << "From: " << boarding << " -> To: " << destination << endl;
        cout << "Fare: Rs. " << fixed << setprecision(2) << fare << endl;
        cout << "Time: " << dateTime << endl;
        cout << "----------------------------\n" << endl;
    }

    // Prints a professional "Box" ticket to a file and logs data to CSV
    void generateFiles() const {
        // 1. Create the visual receipt in a box structure
        ofstream receipt("receipt.txt");
        if (receipt) {
            receipt << "**********************************" << endl;
            receipt << "* RTC OFFICIAL TICKET      *" << endl;
            receipt << "**********************************" << endl;
            receipt << "* From: " << left << setw(24) << boarding << " *" << endl;
            receipt << "* To:   " << left << setw(24) << destination << " *" << endl;
            receipt << "* Dist: " << left << setw(18) << distance << " km  *" << endl;
            receipt << "* Fare: Rs. " << left << setw(20) << fixed << setprecision(2) << fare << " *" << endl;
            receipt << "----------------------------------" << endl;
            receipt << "* Driver ID: " << left << setw(19) << driverID << " *" << endl;
            receipt << "* Depot:     " << left << setw(19) << depot << " *" << endl;
            receipt << "* Issued: " << left << setw(22) << dateTime << " *" << endl;
            receipt << "**********************************" << endl;
            receipt.close();
            cout << ">> Physical receipt saved to 'receipt.txt'" << endl;
        }

        // 2. Append data to a CSV for long-term record keeping
        ofstream history("ticket_history.csv", ios::app);
        if (history) {
            history << dateTime << "," << boarding << "," << destination << "," << fare << "\n";
            history.close();
            cout << ">> Data logged to 'ticket_history.csv'" << endl;
        }
    }
};

// Class to manage daily totals (The Waybill)
class Waybill {
private:
    float totalCollection;
    int totalTickets;

public:
    Waybill() : totalCollection(0), totalTickets(0) {}

    void addSale(float amount) {
        totalCollection += amount;
        totalTickets++;
    }

    void showReport() const {
        cout << "\n===================================";
        cout << "\n         DAILY WAYBILL REPORT      ";
        cout << "\n===================================";
        cout << "\n Total Tickets Issued : " << totalTickets;
        cout << "\n Total Cash Collected : Rs. " << fixed << setprecision(2) << totalCollection;
        cout << "\n===================================\n";
    }

    void resetData() {
        totalCollection = 0;
        totalTickets = 0;
        // Clear the history file
        ofstream outFile("ticket_history.csv", ios::trunc);
        outFile.close();
        cout << "\n[System] All local records have been cleared.\n";
    }
};

// ------------------- MAIN PROGRAM -------------------
int main() {
    string dID, cID, depot;
    int choice;
    Waybill myWaybill;

    cout << "=== RTC TICKETING TERMINAL ===\n";
    cout << "Staff Registration\n";
    cout << "Enter Driver ID    : "; cin >> dID;
    cout << "Enter Conductor ID : "; cin >> cID;
    cout << "Enter Depot Name   : "; cin >> depot;

    do {
        cout << "\n--- MAIN MENU ---";
        cout << "\n1. Issue New Ticket";
        cout << "\n2. View Waybill (Summary)";
        cout << "\n3. Reset System Records";
        cout << "\n4. Exit";
        cout << "\nChoose option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Ticket t;
                t.inputDetails();
                t.setBusStaff(dID, cID, depot);
                t.displayOnScreen();
                t.generateFiles();
                myWaybill.addSale(t.getFare());
                break;
            }
            case 2:
                myWaybill.showReport();
                break;
            case 3:
                myWaybill.resetData();
                break;
            case 4:
                cout << "Exiting... Drive Safely!\n";
                break;
            default:
                cout << "Invalid Option! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}