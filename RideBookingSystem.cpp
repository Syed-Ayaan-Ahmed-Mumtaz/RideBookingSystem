#include<iostream>
#include<string>
#define MAX_RIDES 100   //used in BookingSystem logic
using namespace std;
// Base Level Classes -> Vehicle, Car, Bike, Profile
// ================== VEHICLE ==================
class Vehicle{
    protected:
    string vehicleNumber[3];
    string model[3];
    string type[3];
    bool available[3];
public:
    Vehicle() {
        vehicleNumber[0] = "BRF 147"; model[0] = "Suzuki Alto - White"; type[0] = "Car"; // Car Suzuki Alto
        vehicleNumber[1] = "AFR 776"; model[1] = "Honda CD 70"; type[1] = "Bike"; // Bike Honda CD70
        vehicleNumber[2] = "RFT 104"; model[2] = "Honda 125"; type[2] = "Bike"; // Bike Honda 125
        for (int i = 0; i < 3; i++) { available[i] = true; }
    }
    // Assign first available vehicle based on availability and vehicleType
    bool assignVehicle(string vType, string& outModel, string& outPlate) {
        for (int i = 0; i < 3; i++) {
            if(type[i]==vType && available[i]) {
                outModel = model[i];
                outPlate = vehicleNumber[i];
                available[i] = false;
                return true;
            }
        }
        return false;
    } 
    //Making vehicle available after use
    void releaseVehicle(string plate) {
        for (int i = 0; i < 3; i++) {
            if(vehicleNumber[i]==plate) {
                available[i] = true;
                break;
            }
        }
    } 
};
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

// ================ PROFILE ==================
class Profile{
  static int Ride_id; 
  static int Delivery_id;  
  int RideNo[100] = {0};
  int Fare[100] = {0};
  int DistanceCovered[100] = {0};
  string PickupLocation[100];
  string DropLocation[100];
  bool RideStatus[100] = {false};

 public:
  // Placeholder for further implementation
};
int Profile::Ride_id = 0;
int Profile::Delivery_id = 0;

// Mid Level Classes: Ride, BookingSystem
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
        //assigning a vehicle when ride requested
        bool assigned = assignVehicle(vehicleType, modelAssigned, plateAssigned);
        if(!assigned) {
            cout << "No " << vType << " available at the moment.\n";
            status = "Failed!";
            return;
        }
        calculateFare(distance);
    }
    int getRideID() const { return rideNumber; } 
    string getStatus() const { return status; }
    //getters useful for BookingSystem logic
    void calculateFare(float distance) {
    //distance in km, this way without using maps ride fares are calculated dynamically
        if(vehicleType=="Car") {
            baseRate = 0.8;     
            ratePerKm = 0.5;
            //amounts in USD
        }
        else if(vehicleType=="Bike") {
            baseRate = 0.5;
            ratePerKm = 0.3;
        }
        fare = baseRate + ratePerKm * distance;
    }
    void updateStatus(string newStatus) {
        status = newStatus;
    } 
    void completeRide() {
        status = "Completed!";
        releaseVehicle(plateAssigned);
    }
    void displayRideDetails() {
        cout << "Ride ID: " << rideNumber
             << "\nVehicle Type: " << vehicleType
             << "\nFare: " << fare << "$ "
             << "\nStatus: " << status << endl;
    }   
};
int Ride::rideID = 0;
class BookingSystem {
    private:
        Ride *rides[MAX_RIDES];
        int rideCount;
    public:
    BookingSystem() {
        rideCount = 0;
        for (int i = 0; i < MAX_RIDES; i++) rides[i] = nullptr;
    }
    void bookRide(string vehicleType, float distance) {
        if(rideCount>=MAX_RIDES) {
            cout << "Maximum number of rides reached! \n";
            return;
        }
        rides[rideCount] = new Ride(vehicleType, distance);
        if(rides[rideCount] -> getStatus()!="Failed!") {
            cout << "Ride booked successfully!\n";
        }
        rideCount++;
    }
    void completeRide(int rideID) {
        for (int i = 0; i < rideCount; i++) {
            if(rides[i]!=nullptr && rides[i]->getRideID()==rideID) {
                rides[i]->completeRide();
                cout << "Ride Marked as Complete!\n";
                return;
            }
        }
        cout << "RideID not found!";
    }
    void viewAllRides() {
        for (int i = 0; i < rideCount; i++) {
            if (rides[i] != nullptr) {
                rides[i]->displayRideDetails();
                cout << "----------------------\n";
            }
        }
    }
    ~BookingSystem() {
        for (int i = 0; i < rideCount; i++) {
            delete rides[i];
        }
    }
};

// =============== USER ===================
class User : public Profile, public Vehicle{
 public:
 User(){
  int choice;  
   cout << "You have Successfully Logged in as User!" << endl;
   cout << "Enter\n1. To Book Your Ride Online!\n2. To Deliver Your Product to Any Other Location!" << endl;
   cin >> choice;
  while((choice <= 0) || (choice > 2)){
   cout << "Invalid Value Entered!\nEnter Again:";
   cin >> choice; 
  }
 if(choice == 1){
   cout << "Redirecting to Ride Booking Module..." << endl;
 }
 else if(choice == 2){
   cout << "Redirecting to Delivery Module..." << endl;
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

// ================= ADMIN ==================
class Admin{
 public:
  Admin(){
   int choice; 
    cout << "You have Successfully Logged in as Admin!" << endl;
    cout << "Enter\n1. To View Past Online Riding Details\n2. To View Past Delivery Locations\n";
    cin >> choice;
  while((choice <= 0) || (choice > 2)){
   cout << "Invalid Value Entered!\nEnter Again:";
   cin >> choice; 
 }
   if(choice == 1){
     cout << "Displaying All Past Rides..." << endl;
   }
   else if(choice == 2){
     cout << "Displaying All Past Deliveries..." << endl;
   }      
 }  
};

// ============= MAIN ======================
int main(){
  int choice;      
    cout << "   <--Welcome to Online Ride Booking System!-->   " << endl << endl;
    cout << "Following are the Rules for Online Ride Booking System:" << endl;
    cout << "* User can Book his Ride and Deliver some Product to Another Location!" << endl;
    cout << "* A Driver can Pick up and Drop only one Ride at one Time!" << endl;
    cout << "* Admin has the Option to Access all Past Online Ride Details and Delivery Details!" << endl << endl;

do{
    cout << "1. To Login in as Admin!\n2. To Login as User!\n3. To Login as Driver!\n4. To Exit!\n";
    cin >> choice;
   while((choice <= 0) || (choice > 4)){
    cout << "Invalid Value Entered!\nEnter Again:";
    cin >> choice;
   }
 if(choice == 1){
  Admin ad;  
 }
 else if(choice == 2){
  Passenger ps;
  ps.requestRide();
 }
 else if(choice == 3){
  RideDriver dr;
  string pickup = "Model Town", drop = "Johar Town";
  dr.acceptRide(pickup, drop);
  dr.completeRide();
 }
 else if(choice == 4){
  cout << "Exiting the System!..." << endl;
  return 0;
 }   
}while(choice != 4);  
 
    return 0;
}
