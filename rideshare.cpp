#include <iostream>
#include <vector>
#include <memory> // for smart pointers
#include <iomanip> // for formatting

using namespace std;

// Base class Ride (demonstrating inheritance + polymorphism)
class Ride {
protected:
    string rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance; // in miles

public:
    Ride(string id, string pickup, string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {}

    virtual double fare() const = 0; // pure virtual function for polymorphism

    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID << endl;
        cout << "Pickup: " << pickupLocation << endl;
        cout << "Dropoff: " << dropoffLocation << endl;
        cout << "Distance: " << distance << " miles" << endl;
    }

    virtual ~Ride() {}
};

// StandardRide subclass
class StandardRide : public Ride {
public:
    StandardRide(string id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 2.0;  // $2 per mile
    }

    void rideDetails() const override {
        cout << "Standard Ride:" << endl;
        Ride::rideDetails();
        cout << "Fare: $" << fixed << setprecision(2) << fare() << endl;
    }
};

// PremiumRide subclass
class PremiumRide : public Ride {
public:
    PremiumRide(string id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 3.5;  // $3.5 per mile
    }

    void rideDetails() const override {
        cout << "Premium Ride:" << endl;
        Ride::rideDetails();
        cout << "Fare: $" << fixed << setprecision(2) << fare() << endl;
    }
};

// Driver class demonstrating encapsulation
class Driver {
private:
    string driverID;
    string name;
    double rating;
    vector<shared_ptr<Ride>> assignedRides;  // encapsulated list

public:
    Driver(string id, string n, double r) : driverID(id), name(n), rating(r) {}

    void addRide(shared_ptr<Ride> ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        cout << "\nDriver ID: " << driverID << ", Name: " << name << ", Rating: " << rating << endl;
        cout << "Assigned Rides: " << assignedRides.size() << endl;
        for (const auto& ride : assignedRides) {
            ride->rideDetails();
            cout << endl;
        }
    }
};

// Rider class demonstrating encapsulation
class Rider {
private:
    string riderID;
    string name;
    vector<shared_ptr<Ride>> requestedRides;

public:
    Rider(string id, string n) : riderID(id), name(n) {}

    void requestRide(shared_ptr<Ride> ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        cout << "\nRider ID: " << riderID << ", Name: " << name << endl;
        cout << "Requested Rides: " << requestedRides.size() << endl;
        for (const auto& ride : requestedRides) {
            ride->rideDetails();
            cout << endl;
        }
    }
};

// Main function demonstrating full functionality
int main() {
    // Create rides (using polymorphism via shared_ptr)
    shared_ptr<Ride> ride1 = make_shared<StandardRide>("R001", "Downtown", "Airport", 10);
    shared_ptr<Ride> ride2 = make_shared<PremiumRide>("R002", "Mall", "Hotel", 5);
    shared_ptr<Ride> ride3 = make_shared<StandardRide>("R003", "Office", "Home", 15);

    // Create driver and assign rides
    Driver driver1("D001", "Alice", 4.8);
    driver1.addRide(ride1);
    driver1.addRide(ride2);

    // Create rider and request rides
    Rider rider1("P001", "Bob");
    rider1.requestRide(ride1);
    rider1.requestRide(ride3);

    // Demonstrate polymorphism
    vector<shared_ptr<Ride>> allRides = {ride1, ride2, ride3};

    cout << "\n--- All Ride Details (Polymorphism Demonstration) ---\n";
    for (const auto& ride : allRides) {
        ride->rideDetails();
        cout << endl;
    }

    // Display driver and rider info
    driver1.getDriverInfo();
    rider1.viewRides();

    return 0;
}
