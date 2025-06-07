// Subclasses of Vehicle
class Car : public Vehicle {
public:
    Car() {
        cout << "Car Initialized: Suzuki Alto - White, Plate: BRF 147" << endl;
    }
};

class Bike : public Vehicle {
public:
    Bike(string modelName) {
        if (modelName == "CD70") {
            cout << "Bike Initialized: Honda CD 70, Plate: AFR 776" << endl;
        } else if (modelName == "125") {
            cout << "Bike Initialized: Honda 125, Plate: RFT 104" << endl;
        }
    }
};

// Subclass of User: Passenger
class Passenger : public User {
public:
    Passenger() {
        cout << "Passenger Account Created Successfully!" << endl;
    }

    void requestRide() {
        string pickup, drop;
        cout << "Enter Pickup Location: ";
        cin.ignore();
        getline(cin, pickup);
        cout << "Enter Drop Location: ";
        getline(cin, drop);
        cout << "Ride Requested from " << pickup << " to " << drop << "." << endl;
        // Here you can update the Ride_id or call a ride booking logic.
    }
};

// Subclass of User: Driver
class RideDriver : public User {
    bool isBusy;

public:
    RideDriver() : isBusy(false) {
        cout << "Driver Account Created Successfully!" << endl;
    }

    void acceptRide(string pickup, string drop) {
        if (!isBusy) {
            cout << "Ride Accepted from " << pickup << " to " << drop << "." << endl;
            isBusy = true;
        } else {
            cout << "Driver is currently busy!" << endl;
        }
    }

    void completeRide() {
        if (isBusy) {
            cout << "Ride Completed Successfully!" << endl;
            isBusy = false;
        } else {
            cout << "No active ride to complete." << endl;
        }
    }
};