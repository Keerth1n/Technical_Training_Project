/*Airline Seat Reservation System
 *Airline Seat Reservation System is based on the concept of reserving airline seats for the passengers.
 *Here the user has to select the seat class whether to choose Business or Economy class.
 *Then the system displays available seats, and the user has to enter that particular seat number in order to reserve 
 *it and has to enter their details like name, age, phone number, Departure city, arrival city and journey dates.
 *After reserving a seat, that particular seat won’t be available anymore for other users.
 *Features:
 *1. Book tickets
 *2. Modify tickets
 *3. View the booked ticket by ticket id
 *4. Modify Airline record
 *5. Check airline status
Embraer E190-E2 reference airplane for seat configuration*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SEATS 100
#define MAX_LENGTH 25

struct Passenger {
    char name[MAX_LENGTH];
    int age;
    char phone[MAX_LENGTH];
    char departureCity[MAX_LENGTH];
    char arrivalCity[MAX_LENGTH];
    char journeyDate[MAX_LENGTH];
    bool reserved;
    int classType;
};

struct Passenger seats[MAX_SEATS];

void setSeatColor(int classType, bool reserved) {
    if (reserved) {
        printf("\033[31m"); // Red color for reserved seats
    }
    else {
        switch (classType) {
            case 1:
                    printf("\033[34m"); // Blue color for First Class
                    break;
            case 2:
                    printf("\033[35m"); // Magenta color for Business Class
                    break;
            case 3:
                    printf("\033[32m"); // Green color for Economy Class
                    break;
            case 0: default:
                    printf("\033[0m"); // Default color (white) for invalid classType
        }
    }
}

int getColumnSpacing(const char *data, int maxColumnWidth) {
    int maxLength = maxColumnWidth; // Minimum column width

    int length = strlen(data);
    if (length > maxLength) {
        maxLength = length;
    }

    return maxLength + 2; // Adding 2 for padding
}

void saveDataToFile() {
    FILE *file = fopen("seats_data.txt", "w");

    if (file != NULL) {
        // Calculate maximum column widths
        int maxSeatNumberWidth = getColumnSpacing("Seat Number", MAX_LENGTH);
        int maxNameWidth = getColumnSpacing("Name", MAX_LENGTH);
        int maxAgeWidth = getColumnSpacing("Age", MAX_LENGTH);
        int maxPhoneWidth = getColumnSpacing("Phone Number", MAX_LENGTH);
        int maxDepartureWidth = getColumnSpacing("Departure City", MAX_LENGTH);
        int maxArrivalWidth = getColumnSpacing("Arrival City", MAX_LENGTH);
        int maxJourneyWidth = getColumnSpacing("Journey Date", MAX_LENGTH);

        // Header row
        fprintf(file, "%-*s %-*s %-*s %-*s %-*s %-*s %-*s\n",
                maxSeatNumberWidth, "Seat Number", maxNameWidth, "Name",
                maxAgeWidth, "Age", maxPhoneWidth, "Phone Number",
                maxDepartureWidth, "Departure City", maxArrivalWidth, "Arrival City",
                maxJourneyWidth, "Journey Date");

        // First Class data
        fprintf(file, "\nFirst Class:\n");
        for (int i = 0; i < 10; i++) {
            int seatNumber = i;
            fprintf(file, "%-*d ", maxSeatNumberWidth, seatNumber + 1);
            fprintf(file, "%-*s ", maxNameWidth, seats[seatNumber].name);
            fprintf(file, "%-*d ", maxAgeWidth, seats[seatNumber].age);
            fprintf(file, "%-*s ", maxPhoneWidth, seats[seatNumber].phone);
            fprintf(file, "%-*s ", maxDepartureWidth, seats[seatNumber].departureCity);
            fprintf(file, "%-*s ", maxArrivalWidth, seats[seatNumber].arrivalCity);
            fprintf(file, "%-*s\n", maxJourneyWidth, seats[seatNumber].journeyDate);
        }

        // Business Class data
        fprintf(file, "\nBusiness Class:\n");
        for (int i = 10; i < 40; i++) {
            int seatNumber = i;
            fprintf(file, "%-*d ", maxSeatNumberWidth, seatNumber + 1);
            fprintf(file, "%-*s ", maxNameWidth, seats[seatNumber].name);
            fprintf(file, "%-*d ", maxAgeWidth, seats[seatNumber].age);
            fprintf(file, "%-*s ", maxPhoneWidth, seats[seatNumber].phone);
            fprintf(file, "%-*s ", maxDepartureWidth, seats[seatNumber].departureCity);
            fprintf(file, "%-*s ", maxArrivalWidth, seats[seatNumber].arrivalCity);
            fprintf(file, "%-*s\n", maxJourneyWidth, seats[seatNumber].journeyDate);
        }

        // Economy Class data
        fprintf(file, "\nEconomy Class:\n");
        for (int i = 40; i < MAX_SEATS; i++) {
            int seatNumber = i;
            fprintf(file, "%-*d ", maxSeatNumberWidth, seatNumber + 1);
            fprintf(file, "%-*s ", maxNameWidth, seats[seatNumber].name);
            fprintf(file, "%-*d ", maxAgeWidth, seats[seatNumber].age);
            fprintf(file, "%-*s ", maxPhoneWidth, seats[seatNumber].phone);
            fprintf(file, "%-*s ", maxDepartureWidth, seats[seatNumber].departureCity);
            fprintf(file, "%-*s ", maxArrivalWidth, seats[seatNumber].arrivalCity);
            fprintf(file, "%-*s\n", maxJourneyWidth, seats[seatNumber].journeyDate);
        }

        fclose(file);
    } else {
        printf("Error saving data to file.\n");
    }
}

void initializeSeats() {
    for (int i = 0; i < MAX_SEATS; i++) {
        seats[i].reserved = false;
        strcpy(seats[i].name, "");
        seats[i].age = 0;
        strcpy(seats[i].phone, "");
        strcpy(seats[i].departureCity, "");
        strcpy(seats[i].arrivalCity, "");
        strcpy(seats[i].journeyDate, "");
    }
}

void loadDataFromFile() {
    FILE *file = fopen("seats_data.txt", "r");

    if (file != NULL) {
        for (int i = 0; i < MAX_SEATS; i++) {
            int reservedStatus;
            fscanf(file, "%d %s %d %s %s %s %s\n", &reservedStatus, seats[i].name, &seats[i].age,
                   seats[i].phone, seats[i].departureCity, seats[i].arrivalCity, seats[i].journeyDate);
            seats[i].reserved = (reservedStatus == 1) ? true : false;
        }

        fclose(file);
    }
    else {
        printf("\nCreating a new file. Initializing with default values.\n");
        initializeSeats();
        saveDataToFile();
    }
}

void displayMenu() {
    printf("\nAirline Seat Reservation System\n");
    printf("-------------------------------\n");
    printf("1. Book tickets\n");
    printf("2. Modify tickets\n");
    printf("3. View the booked ticket by ticket id\n");
    printf("4. Modify Airline record\n");
    printf("5. Check airline status\n");
    printf("6. Cancel Ticket\n");
    printf("7. Exit\n");
}

void bookTicket() {
    int seatNumber;
    int classChoice;

    printf("Select seat class:\n");
    printf("1. First Class\n");
    printf("2. Business Class\n");
    printf("3. Economy Class\n");
    printf("Enter choice: ");
    scanf("%d", &classChoice);

    if (classChoice < 1 || classChoice > 3) {
        printf("Invalid choice! Please try again.\n");
        return;
    }

    printf("\t\t\tAvailable Seats\n");
    setSeatColor(1, false); // Available seats (reset color)
    printf("First Class:    ");
    for (int i = 0; i < 10; i++) {
        int seatNumber = i;
        setSeatColor(1, seats[seatNumber].reserved);
        if (seats[seatNumber].reserved) {
            printf(" X   "); // Reserved seat
        } else {
            printf("%-4d ", seatNumber + 1); // Available seat number
        }
    }
    printf("\n");

    setSeatColor(2, false);
    printf("Business Class: ");
    for (int i = 10; i < 40; i++) {
        int seatNumber = i;
        setSeatColor(2, seats[seatNumber].reserved);
        if (seats[seatNumber].reserved) {
            printf(" X   "); // Reserved seat
        } else {
            printf("%-4d ", seatNumber + 1); // Available seat number
        }
        if (i == 19 || i == 29) {
            printf("\n                ");
        }
    }
    printf("\n");

    setSeatColor(3, false);
    printf("Economy Class:  ");
    for (int i = 40; i < 100; i++) {
        int seatNumber = i;
        setSeatColor(3, seats[seatNumber].reserved);
        if (seats[seatNumber].reserved) {
            printf(" X   "); // Reserved seat
        }
        else {
            printf("%-4d ", seatNumber + 1); // Available seat number
        }
        if (i == 49 || i == 59 || i == 69 || i == 79 || i == 89 || i == 99) {
            printf("\n                ");
        }
    }
    printf("\n");

    // Reset color back to default (white)
    printf("\033[0m");

    printf("Enter the seat number you want to reserve: ");
    scanf("%d", &seatNumber);
    seatNumber--;

    if (seatNumber < 0 || seatNumber >= MAX_SEATS) {
        printf("Invalid seat number! Please try again.\n");
        return;
    }

    // Check if the selected seat number is within the valid range for the chosen class
    if ((classChoice == 1 && seatNumber >= 0 && seatNumber < 10) ||
        (classChoice == 2 && seatNumber >= 10 && seatNumber < 40) ||
        (classChoice == 3 && seatNumber >= 40 && seatNumber < 100)) {

        if (seats[seatNumber].reserved) {
            printf("Seat %d is already reserved. Please choose another seat.\n", seatNumber + 1);
            return;
        }

        seats[seatNumber].reserved = true;
        seats[seatNumber].classType = classChoice;

        printf("Enter passenger name: ");
        scanf(" %[^\n]s", seats[seatNumber].name);

        printf("Enter passenger age: ");
        scanf("%d", &seats[seatNumber].age);

        printf("Enter passenger phone number: ");
        scanf(" %[^\n]s", seats[seatNumber].phone);

        printf("Enter departure city: ");
        scanf(" %[^\n]s", seats[seatNumber].departureCity);

        printf("Enter arrival city: ");
        scanf(" %[^\n]s", seats[seatNumber].arrivalCity);

        printf("Enter journey date: ");
        scanf(" %[^\n]s", seats[seatNumber].journeyDate);

        printf("Ticket booked successfully!\n");

        saveDataToFile();
    }
    else {
        printf("Invalid seat number for the selected class! Please try again.\n");
    }
}

void modifyTicket() {
    int ticketId;

    printf("Enter the ticket ID to modify: ");
    scanf("%d", &ticketId);
    ticketId--;

    if (ticketId < 0 || ticketId >= MAX_SEATS) {
        printf("Invalid ticket ID! Please try again.\n");
        return;
    }

    if (!seats[ticketId].reserved) {
        printf("Ticket ID %d is not reserved yet.\n", ticketId + 1);
        return;
    }

    printf("Enter new passenger name: ");
    scanf(" %[^\n]s", seats[ticketId].name);

    printf("Enter new passenger age: ");
    scanf("%d", &seats[ticketId].age);

    printf("Enter new passenger phone number: ");
    scanf(" %[^\n]s", seats[ticketId].phone);

    printf("Enter new departure city: ");
    scanf(" %[^\n]s", seats[ticketId].departureCity);

    printf("Enter new arrival city: ");
    scanf(" %[^\n]s", seats[ticketId].arrivalCity);

    printf("Enter new journey date: ");
    scanf(" %[^\n]s", seats[ticketId].journeyDate);

    printf("Ticket ID %d modified successfully!\n", ticketId + 1);

    saveDataToFile();
}

void viewBookedTicket() {
    int ticketId;

    printf("Enter the ticket ID to view: ");
    scanf("%d", &ticketId);
    ticketId--;

    if (ticketId < 0 || ticketId >= MAX_SEATS) {
        printf("Invalid ticket ID! Please try again.\n");
        return;
    }

    if (!seats[ticketId].reserved) {
        printf("Ticket ID %d is not reserved yet.\n", ticketId + 1);
        return;
    }

    printf("Ticket ID: %d\n", ticketId + 1);
    printf("Name: %s\n", seats[ticketId].name);
    printf("Age: %d\n", seats[ticketId].age);
    printf("Phone: %s\n", seats[ticketId].phone);
    printf("Departure City: %s\n", seats[ticketId].departureCity);
    printf("Arrival City: %s\n", seats[ticketId].arrivalCity);
    printf("Journey Date: %s\n", seats[ticketId].journeyDate);
}

void modifyAirlineRecord() {
    int ticketId;

    printf("Enter the ticket ID to modify: ");
    scanf("%d", &ticketId);
    ticketId--;

    if (ticketId < 0 || ticketId >= MAX_SEATS) {
        printf("Invalid ticket ID! Please try again.\n");
        return;
    }

    if (!seats[ticketId].reserved) {
        printf("Ticket ID %d is not reserved yet.\n", ticketId + 1);
        return;
    }

    printf("What do you want to modify?\n");
    printf("1. Passenger Name\n");
    printf("2. Passenger Age\n");
    printf("3. Phone Number\n");
    printf("4. Departure City\n");
    printf("5. Arrival City\n");
    printf("6. Journey Date\n");
    printf("Enter choice: ");
    int modifyChoice;
    scanf("%d", &modifyChoice);

    switch (modifyChoice) {
        case 1:
                printf("Enter new passenger name: ");
                scanf(" %[^\n]s", seats[ticketId].name);
                break;
        case 2:
                printf("Enter new passenger age: ");
                scanf("%d", &seats[ticketId].age);
                break;
        case 3:
                printf("Enter new passenger phone number: ");
                scanf(" %[^\n]s", seats[ticketId].phone);
                break;
        case 4:
                printf("Enter new departure city: ");
                scanf(" %[^\n]s", seats[ticketId].departureCity);
                break;
        case 5:
                printf("Enter new arrival city: ");
                scanf(" %[^\n]s", seats[ticketId].arrivalCity);
                break;
        case 6:
                printf("Enter new journey date: ");
                scanf(" %[^\n]s", seats[ticketId].journeyDate);
                break;
        default:
                printf("Invalid choice! No modifications made.\n");
                return;
    }

    printf("Ticket ID %d modified successfully!\n", ticketId + 1);

    saveDataToFile();
}

void checkAirlineStatus() {
    int totalFirstClassReservedSeats = 0;
    int totalFirstClassAvailableSeats = 0;
    int totalBusinessClassReservedSeats = 0;
    int totalBusinessClassAvailableSeats = 0;
    int totalEconomyClassReservedSeats = 0;
    int totalEconomyClassAvailableSeats = 0;

    printf("\t\t\tAvailable Seats\n");
    setSeatColor(1, false); // Available seats (reset color)
    printf("First Class:    ");
    for (int i = 0; i < 10; i++) {
        int seatNumber = i;
        setSeatColor(1, seats[seatNumber].reserved);
        if (seats[seatNumber].reserved) {
            printf(" X   "); // Reserved seat
            totalFirstClassReservedSeats++;
        } else {
            printf("%-4d ", seatNumber + 1); // Available seat number
            totalFirstClassAvailableSeats++;
        }
    }
    printf("\n");

    setSeatColor(2, false);
    printf("Business Class: ");
    for (int i = 10; i < 40; i++) {
        int seatNumber = i;
        setSeatColor(2, seats[seatNumber].reserved);
        if (seats[seatNumber].reserved) {
            printf(" X   "); // Reserved seat
            totalBusinessClassReservedSeats++;
        }
        else {
            printf("%-4d ", seatNumber + 1); // Available seat number
            totalBusinessClassAvailableSeats++;
        }
        if (i == 19 || i == 29) {
            printf("\n                ");
        }
    }
    printf("\n");

    setSeatColor(3, false);
    printf("Economy Class:  ");
    for (int i = 40; i < 100; i++) {
        int seatNumber = i;
        setSeatColor(3, seats[seatNumber].reserved);
        if (seats[seatNumber].reserved) {
            printf(" X   "); // Reserved seat
            totalEconomyClassReservedSeats++;
        }
        else {
            printf("%-4d ", seatNumber + 1); // Available seat number
            totalEconomyClassAvailableSeats++;
        }
        if (i == 49 || i == 59 || i == 69 || i == 79 || i == 89 || i == 99) {
            printf("\n                ");
        }
    }
    printf("\n");

    // Reset color back to default (white)
    printf("\033[0m");

    printf("\nAirline Status:\n");
    printf("First Class - Reserved Seats: %d, Available Seats: %d\n", totalFirstClassReservedSeats, totalFirstClassAvailableSeats);
    printf("Business Class - Reserved Seats: %d, Available Seats: %d\n", totalBusinessClassReservedSeats, totalBusinessClassAvailableSeats);
    printf("Economy Class - Reserved Seats: %d, Available Seats: %d\n", totalEconomyClassReservedSeats, totalEconomyClassAvailableSeats);
}

void cancelTicket() {
    int ticketId;

    printf("Enter the ticket ID to cancel: ");
    scanf("%d", &ticketId);
    ticketId--;

    if (ticketId < 0 || ticketId >= MAX_SEATS) {
        printf("Invalid ticket ID! Please try again.\n");
        return;
    }

    if (!seats[ticketId].reserved) {
        printf("Ticket ID %d is not reserved yet.\n", ticketId + 1);
        return;
    }

    seats[ticketId].reserved = false;
    seats[ticketId].classType = 0;
    strcpy(seats[ticketId].name, "");
    seats[ticketId].age = 0;
    strcpy(seats[ticketId].phone, "");
    strcpy(seats[ticketId].departureCity, "");
    strcpy(seats[ticketId].arrivalCity, "");
    strcpy(seats[ticketId].journeyDate, "");

    printf("Ticket ID %d has been canceled.\n", ticketId + 1);

    saveDataToFile();
}

int main() {
    int choice;

    loadDataFromFile();

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                    bookTicket();
                    break;
            case 2:
                    modifyTicket();
                    break;
            case 3:
                    viewBookedTicket();
                    break;
            case 4:
                    modifyAirlineRecord();
                    break;
            case 5:
                    checkAirlineStatus();
                    break;
            case 6:
                    cancelTicket();
                    break;
            case 7:
                    printf("Exiting the program.\n");
                    return 0;
            default:
                    printf("Invalid choice! Please try again.\n");
        }
    } while (true);

    return 0;
}