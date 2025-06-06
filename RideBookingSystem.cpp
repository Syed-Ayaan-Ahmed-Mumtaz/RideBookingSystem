#include<iostream>
#include<string>
using namespace std;

class Vehicle{
  string vehicleNumber[3];
  string model[3];
  string type[3];
 public:
 Vehicle(){
    vehicleNumber[0] = "BRF 147";  // Number Plate for Suzuki ALto
    vehicleNumber[1] = "AFR 776";  // Number Plate for Honda CD 70
    vehicleNumber[2] = "RFT 104";  // Number Plate for Honda 125
    model[0] = "Suzuki Alto - White";
    model[1] = "Honda CD 70";
    model[2] = "Honda 125";
    type[0] = "Car";
    type[1] = "Bike";
    type[2] = "Bike";
 } 
};

class Admin{
 public:
  Admin(){
   int choice; 
    cout<<"You have Successfully Logged in as Admin!"<<endl;
    cout<<"Enter\n1. To View Past Online Riding Details\n2. To View Past Delivery Locations\n";
    cin>>choice;
  while((choice <= 0) || (choice > 2)){
   cout<<"Invalid Value Entered!\nEnter Again:";
   cin>>choice; 
 }
   if(choice == 1){
     // Implement Logic to Print Details of all Past Rides Booked!
   }
   else if(choice == 2){
    // Implement Logic to Print Details of all Past Deliveries! 
   }      
 }  
};

// Every time a Ride is Booked, Increment Ride_id by 1
// Every time a Delivery is Booked, Increment Delivery_id by 1
class Profile{
  static int Ride_id; // To keep track that how Rides have been Booked!
  static int Delivery_id;  // To keep track that how many Products have been Delivered!  
  int RideNo[100] = {0};
  int Fare[100] = {0};
  int DistanceCovered[100] = {0};
  string PickupLocation[100];
  string DropLocation[100];
  bool RideStatus[100] = {false};

 public:
  
  // Implement Functions for Pickup, and Drop Ride, Calculations for Fare Depending upon Distance Covered
  // and all other stuff etc.
};
int Profile::Ride_id = 0;
int Profile::Delivery_id = 0;


class User : public Profile, public Vehicle{
 public:
 User(){
  int choice;  
   cout<<"You have Successfully Logged in as User!"<<endl;
   cout<<"Enter\n1. To Book Your Ride Online!\n2. To Deliver Your Product to Any Other Location!"<<endl;
   cin>>choice;
  while((choice <= 0) || (choice > 2)){
   cout<<"Invalid Value Entered!\nEnter Again:";
   cin>>choice; 
  }
 if(choice == 1){
 // Implement Your Logic for Booking Your Online! 
 }
 else if(choice == 2){
 // Implement Your Logic for Delivering Your Product to Any Other Location!  
 }      
 }

};

class Driver : public Profile, public Vehicle{
 public:
  Driver(){
    cout<<"You have Successfully Logged in as Driver!"<<endl;
    // Implement Further Logic for Picking up and Dropping Rides and Checking Current Status!
  }
};

int main(){
  int choice;      
    cout<<"   <--Welcome to Online Ride Booking System!-->   "<<endl<<endl;
    cout<<"Following are the Rules for Online Ride Booking System:"<<endl;
    cout<<"* User can Book his Ride and Deliver some Product to Another Location!"<<endl;
    cout<<"* A Driver can Pick up and Drop only one Ride at one Time!"<<endl;
    cout<<"Admin has the Option to Access all Past Online Ride Details and Delivery Details!"<<endl<<endl;

 do{
    cout<<"1. To Login in as Admin!\n2. To Login as User!\n3. To Login as Driver!\n4. To Exit!\n";
    cin>>choice;
   while((choice <= 0) || (choice > 4)){
    cout<<"Invalid Value Entered!\nEnter Again:";
    cin>>choice;
   }
 if(choice == 1){
  Admin ad;  
  // Create an Object of Admin Class so that its constructor is called!
 }
 else if(choice == 2){
  User us;  
  // Create an Object of User Class so that its constructor is called!
 }
 else if(choice == 3){
  Driver dr;  
 // Create an Object of Driver Class so that its constructor is called!
 }
 else if(choice == 4){
  cout<<"Exiting the System!....";
  return 0;
 }   
}while(choice != 4);  
 
    return 0;
}
