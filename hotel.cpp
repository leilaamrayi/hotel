#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Structure to represent a reservation
struct Reservation {
    string guestName;
    string roomType;
    string checkInDate;
    string checkOutDate;
};

// Function to display available reservations
void displayReservations(const vector<Reservation>& reservations) {
    cout << "Available Reservations:\n";
    if (reservations.empty()) {
        cout << "No reservations available.\n";
        return;
    }
    // Display each reservation
    for (const auto& reservation : reservations) {
        cout << "Guest: " << reservation.guestName << " | Room Type: " << reservation.roomType
                  << " | Check-in: " << reservation.checkInDate << " | Check-out: " << reservation.checkOutDate << "\n";
    }
}

// Function to book a new reservation
void bookReservation(vector<Reservation>& reservations) {
    Reservation newReservation;
    // Gather information for the new reservation
    cout << "Enter Guest Name: ";
    cin >> newReservation.guestName;
    cout << "Enter Room Type: ";
    cin >> newReservation.roomType;
    cout << "Enter Check-in Date: ";
    cin >> newReservation.checkInDate;
    cout << "Enter Check-out Date: ";
    cin >> newReservation.checkOutDate;

    // Add the new reservation to the list
    reservations.push_back(newReservation);

    // Write the new reservation to the file
    ofstream outFile("reservations.txt", ios::app);
    if (outFile.is_open()) {
        outFile << newReservation.guestName << "," << newReservation.roomType << ","
                << newReservation.checkInDate << "," << newReservation.checkOutDate << "\n";
        outFile.close();
        cout << "Reservation successfully booked!\n";
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

// Function to load reservations from file
void loadReservations(vector<Reservation>& reservations) {
    // Read reservations from the file
    ifstream inFile("reservations.txt");
    if (inFile.is_open()) {
        Reservation temp;
        // Read each line as a reservation and add it to the list
        while (getline(inFile, temp.guestName, ',') &&
               getline(inFile, temp.roomType, ',') &&
               getline(inFile, temp.checkInDate, ',') &&
               getline(inFile, temp.checkOutDate)) {
            reservations.push_back(temp);
        }
        inFile.close();
    } else {
        cout << "Unable to open file for reading.\n";
    }
}

// Main function
int main() {
    vector<Reservation> reservations;
    // Load existing reservations from file
    loadReservations(reservations);

    int choice;
    do {
        // Display menu options
        cout << "\nXandicLifehub - Hotel Management System\n";
        cout << "1. Display available reservations\n";
        cout << "2. Book a new reservation\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayReservations(reservations);
                break;
            case 2:
                bookReservation(reservations);
                break;
            case 3:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 3);

    return 0;
}
