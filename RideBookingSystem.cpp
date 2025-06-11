#include<iostream>
#include<string>
#define MAX_RIDES 100
using namespace std;

// =============== VEHICLE ====================
class Vehicle {
protected:
    string vehicleNumber[3];
    string model[3];
    string type[3];
    bool available[3];
public:
    Vehicle() {
        vehicleNumber[0] = "BRF 147"; model[0] = "Suzuki Alto - White"; type[0] = "Car";
        vehicleNumber[1] = "AFR 776"; model[1] = "Honda CD 70"; type[1] = "Bike";
        vehicleNumber[2] = "RFT 104"; model[2] = "Honda 125"; type[2] = "Bike";
        for (int i = 0; i < 3; i++) available[i] = true;
    }

    bool assignVehicle(string vType, string& outModel, string& outPlate) {
        for (int i = 0; i < 3; i++) {
            if (type[i] == vType && available[i]) {
                outModel = model[i];
                outPlate = vehicleNumber[i];
                available[i] = false;
                return true;
            }
        }
        return false;
    }

    void releaseVehicle(string plate) {
        for (int i = 0; i < 3; i++) {
            if (vehicleNumber[i] == plate) {
                available[i] = true;
                break;
            }
        }
    }
};

// =============== PROFILE ====================
class Profile {
    static int Ride_id;
    static int Delivery_id;
public:
    Profile() {}
};
int Profile::Ride_id = 0;
int Profile::Delivery_id = 0;

// =============== RIDE ====================
class Ride : public Vehicle {
private:
    static int rideID;
    int rideNumber;
    string vehicleType, status;
    float fare, baseRate, ratePerKm;
    string modelAssigned, plateAssigned;
public:
    Ride(string vType, float distance) {
        vehicleType = vType;
        rideID++;
        rideNumber = rideID;
        status = "Ride Requested";

        bool assigned = assignVehicle(vehicleType, modelAssigned, plateAssigned);
        if (!assigned) {
            cout << "No " << vType << " available at the moment.\n";
            status = "Failed!";
            return;
        }
        calculateFare(distance);
    }

    int getRideID() const { return rideNumber; }
    string getStatus() const { return status; }

    void calculateFare(float distance) {
        if (vehicleType == "Car") {
            baseRate = 0.8;
            ratePerKm = 0.5;
        } else if (vehicleType == "Bike") {
            baseRate = 0.5;
            ratePerKm = 0.3;
        }
        fare = baseRate + ratePerKm * distance;
    }

    void completeRide() {
        status = "Completed!";
        releaseVehicle(plateAssigned);
    }

    void displayRideDetails() {
        cout << "Ride ID: " << rideNumber
             << "\nVehicle Type: " << vehicleType
             << "\nFare: " << fare << "$"
             << "\nStatus: " << status << endl;
    }
};
int Ride::rideID = 0;

// =============== BOOKING SYSTEM ==============
class BookingSystem {
private:
    Ride* rides[MAX_RIDES];
    int rideCount;
public:
    BookingSystem() {
        rideCount = 0;
        for (int i = 0; i < MAX_RIDES; i++) rides[i] = NULL;
    }

    int bookRide(string vehicleType, float distance) {
        if (rideCount >= MAX_RIDES) {
            cout << "Maximum number of rides reached!\n";
            return -1;
        }
        rides[rideCount] = new Ride(vehicleType, distance);
        if (rides[rideCount]->getStatus() != "Failed!") {
            cout << "Ride booked successfully!\n";
            cout << "Your Ride ID is: " << rides[rideCount]->getRideID() << endl;
        }
        return rideCount++;
    }

    void completeRide(int rideID) {
        for (int i = 0; i < rideCount; i++) {
            if (rides[i] != NULL && rides[i]->getRideID() == rideID) {
                rides[i]->completeRide();
                cout << "Ride Marked as Complete!\n";
                return;
            }
        }
        cout << "RideID not found!\n";
    }

    void viewAllRides() {
        for (int i = 0; i < rideCount; i++) {
            if (rides[i] != NULL) {
                rides[i]->displayRideDetails();
                cout << "----------------------\n";
            }
        }
    }

    ~BookingSystem() {
        for (int i = 0; i < rideCount; i++) delete rides[i];
    }
};

// =============== USER ====================
class User : public Profile, public Vehicle {
public:
    User() {} // No prompts inside class
};

// =============== PASSENGER ================
class Passenger : public User {
public:
    Passenger() {
        cout << "Passenger Account Created Successfully!\n";
    }
};

// =============== DRIVER ==================
class RideDriver : public User {
    bool isBusy;
public:
    RideDriver() : isBusy(false) {
        cout << "Driver Account Created Successfully!\n";
    }

    void acceptRide(string pickup, string drop) {
        if (!isBusy) {
            cout << "Ride Accepted from " << pickup << " to " << drop << ".\n";
            isBusy = true;
        } else {
            cout << "Driver is currently busy!\n";
        }
    }

    void completeRide() {
        if (isBusy) {
            cout << "Ride Completed Successfully!\n";
            isBusy = false;
        } else {
            cout << "No active ride to complete.\n";
        }
    }
};

// =============== ADMIN ==================
class Admin {
public:
    Admin(BookingSystem& system) {
        int choice;
        cout << "You have Successfully Logged in as Admin!\n";
        cout << "Enter\n1. To View Past Rides\n2. To View Past Deliveries\n";
        cin >> choice;
        while (choice < 1 || choice > 2) {
            cout << "Invalid Input! Enter Again: ";
            cin >> choice;
        }
        if (choice == 1) {
            cout << "\n--- Ride History ---\n";
            system.viewAllRides();
        } else {
            cout << "Displaying All Past Deliveries...\n";
        }
    }
};

// =============== MAIN ==================
int main() {
    BookingSystem system;
    Passenger passenger;
    RideDriver driver;
    int choice;

    do {
        cout << "\n Welcome to the Ride Booking System \n";
        cout << "----------------------------------------\n";
        cout << "Rules:\n";
        cout << "- Users can book rides or deliveries.\n";
        cout << "- A driver can only handle one ride at a time.\n";
        cout << "- Admin can view previous data.\n";

        cout << "\nMain Menu:\n";
        cout << "1. Login as Admin\n";
        cout << "2. Login as User (Passenger)\n";
        cout << "3. Login as Driver\n";
        cout << "4. Book a Ride\n";
        cout << "5. Complete a Ride\n";
        cout << "6. View All Rides\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        while (choice < 1 || choice > 7) {
            cout << "Invalid input! Try again: ";
            cin >> choice;
        }

        switch (choice) {
            case 1: {
                Admin admin(system);
                break;
            }
            case 2: {
                passenger = Passenger();
                break;
            }
            case 3: {
                driver = RideDriver();
                break;
            }
            case 4: {
                string vType;
                float distance;
                cout << "Enter Vehicle Type (Car/Bike): ";
                cin >> vType;
                cout << "Enter Distance in KM: ";
                cin >> distance;
                system.bookRide(vType, distance);
                break;
            }
            case 5: {
                int rideID;
                cout << "Enter Ride ID to Complete: ";
                cin >> rideID;
                system.completeRide(rideID);
                break;
            }
            case 6: {
                system.viewAllRides();
                break;
            }
            case 7: {
                cout << "Thank you for using the Ride Booking System. Goodbye!\n";
                break;
            }
        }

    } while (choice != 7);

    return 0;
}

