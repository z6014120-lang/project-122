#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_RESERVATIONS = 100;

struct Reservation {
    string ticketID;
    string name;
    string fromCity;
    string toCity;
    string travelDate;
};

Reservation reservations[MAX_RESERVATIONS]; // Array to store reservations
int reservationCount = 0;

// Function declarations
string generateTicketID();
void bookFlight();
void viewReservations();
void saveReservationsToFile();
void loadReservationsFromFile();
void deleteReservation();

int main() {
    srand(time(0)); // Seed for random ticket ID generation
    loadReservationsFromFile(); // Load previous reservations from file at start

    int choice;
    do {
        cout << "\n======= Zoya Airline Reservation System =======\n";
        cout << "1. Book Flight\n2. View Reservations\n3. Delete Reservation\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
        case 1:
            bookFlight();
            break;
        case 2:
            viewReservations();
            break;
        case 3:
            deleteReservation();
            break;
        case 4:
            saveReservationsToFile(); // Save all reservations to file
            cout << "\nThank you for using Zoya Airlines! ✈️\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

// Function to generate a random ticket ID like "ZX1234"
string generateTicketID() {
    string id = "ZX";
    int num = rand() % 9000 + 1000;
    id += to_string(num);
    return id;
}

// Function to book a new flight
void bookFlight() {
    if (reservationCount >= MAX_RESERVATIONS) {
        cout << "\n Maximum reservations reached!\n";
        return;
    }

    Reservation r;
    cout << "\nEnter Passenger Name: ";
    getline(cin, r.name);
    cout << "From City: ";
    getline(cin, r.fromCity);
    cout << "To City: ";
    getline(cin, r.toCity);
    cout << "Travel Date (DD-MM-YYYY): ";
    getline(cin, r.travelDate);

    r.ticketID = generateTicketID(); // Generate a unique ticket ID
    reservations[reservationCount++] = r; // Store reservation in the array

    cout << "\n Flight Booked Successfully!\n";
    cout << "Ticket ID: " << r.ticketID << endl;
}

// Function to view all reservations
void viewReservations() {
    if (reservationCount == 0) {
        cout << "\n No reservations found.\n";
        return;
    }

    cout << "\n🛫 Booked Reservations:\n";
    cout << left << setw(12) << "Ticket ID"
        << setw(20) << "Name"
        << setw(15) << "From"
        << setw(15) << "To"
        << setw(12) << "Date" << endl;

    cout << string(74, '-') << endl;
    for (int i = 0; i < reservationCount; ++i) {
        cout << left << setw(12) << reservations[i].ticketID
            << setw(20) << reservations[i].name
            << setw(15) << reservations[i].fromCity
            << setw(15) << reservations[i].toCity
            << setw(12) << reservations[i].travelDate << endl;
    }
}

// Function to save all reservations to a file
void saveReservationsToFile() {
    ofstream outFile("reservations.txt", ios::app); // Open file in append mode
    if (!outFile) {
        cerr << "\n Error opening file for writing!\n";
        return;
    }

    for (int i = 0; i < reservationCount; ++i) {
        outFile << reservations[i].ticketID << ","
            << reservations[i].name << ","
            << reservations[i].fromCity << ","
            << reservations[i].toCity << ","
            << reservations[i].travelDate << endl;
    }

    outFile.close();
    cout << "\nReservations saved to file.\n";
}

// Function to load reservations from the file
void loadReservationsFromFile() {
    ifstream inFile("reservations.txt");
    if (!inFile) {
        cout << "\nNo existing reservations found. Starting fresh.\n";
        return;
    }

    string ticketID, name, fromCity, toCity, travelDate;
    while (getline(inFile, ticketID, ',') &&
        getline(inFile, name, ',') &&
        getline(inFile, fromCity, ',') &&
        getline(inFile, toCity, ',') &&
        getline(inFile, travelDate)) {

        Reservation r;
        r.ticketID = ticketID;
        r.name = name;
        r.fromCity = fromCity;
        r.toCity = toCity;
        r.travelDate = travelDate;

        reservations[reservationCount++] = r;
    }

    inFile.close();
    cout << "\n Reservations loaded from file.\n";
}

// Function to delete a reservation
void deleteReservation() {
    string ticketID;
    cout << "\nEnter Ticket ID to delete: ";
    cin >> ticketID;

    bool found = false;
    for (int i = 0; i < reservationCount; ++i) {
        if (reservations[i].ticketID == ticketID) {
            // Shift remaining reservations to delete the found reservation
            for (int j = i; j < reservationCount - 1; ++j) {
                reservations[j] = reservations[j + 1];
            }
            reservationCount--;
            found = true;
            cout << "\n Reservation with Ticket ID " << ticketID << " has been deleted.\n";
            break;
        }
    }

    if (!found) {
        cout << "\n❌ No reservation found with Ticket ID " << ticketID << ".\n";
    }
}

