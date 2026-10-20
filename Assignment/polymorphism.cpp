// Runtime Polymorphism
// Real-world example: transport fare calculator
// Parent: TransportMode (virtual calculateFare)
// Derived: BodaBoda, MinibusTaxi, Bus (each overrides calculateFare)

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Parent class
class TransportMode {
protected:
    // Data members
    string name;

public:
    // Member functions
    TransportMode(string n) : name(n) {}

    virtual double calculateFare(double km, int passengers) const {
        return km * 1000 * passengers;
    }

    virtual string description() const {
        return "Generic transport";
    }

    string getName() const { return name; }

    virtual ~TransportMode() {}
};

// Derived class 1
class BodaBoda : public TransportMode {
private:
    // Data members
    double baseFee;
    double ratePerKm;

public:
    // Member functions
    BodaBoda() : TransportMode("Boda-boda"), baseFee(2000), ratePerKm(1500) {}

    double calculateFare(double km, int passengers) const override {
        (void)passengers;   // a boda-boda carries one passenger
        return baseFee + km * ratePerKm;
    }

    string description() const override {
        return "1 passenger, base fee plus per km";
    }
};

// Derived class 2
class MinibusTaxi : public TransportMode {
private:
    // Data members
    double ratePerKm;

public:
    // Member functions
    MinibusTaxi() : TransportMode("Minibus taxi"), ratePerKm(600) {}

    double calculateFare(double km, int passengers) const override {
        return km * ratePerKm * passengers;
    }

    string description() const override {
        return "shared ride, per passenger per km";
    }
};

// Derived class 3
class Bus : public TransportMode {
private:
    // Data members
    double ratePerKm;
    double groupDiscount;

public:
    // Member functions
    Bus() : TransportMode("Long-distance bus"), ratePerKm(250), groupDiscount(0.1) {}

    double calculateFare(double km, int passengers) const override {
        double total = km * ratePerKm * passengers;
        if (passengers >= 5) total -= total * groupDiscount;
        return total;
    }

    string description() const override {
        return "cheapest per km, discount for 5 or more";
    }
};

// Works with any TransportMode through a base-class reference
void printQuote(const TransportMode &t, double km, int passengers) {
    cout << "  " << t.getName() << " (" << t.description() << ")\n"
         << "    Fare for " << km << " km, " << passengers
         << " passenger(s): UGX " << t.calculateFare(km, passengers) << endl;
}

int main() {
    cout << "RUNTIME POLYMORPHISM: Transport Fare Calculator\n\n";

    // Base-class pointers to derived objects
    TransportMode *ride1 = new BodaBoda();
    TransportMode *ride2 = new MinibusTaxi();
    TransportMode *ride3 = new Bus();

    cout << "1) Same call through base-class pointers (10 km, 1 passenger):" << endl;
    cout << "  " << ride1->getName() << ": " << ride1->calculateFare(10, 1) << endl;
    cout << "  " << ride2->getName() << ": " << ride2->calculateFare(10, 1) << endl;
    cout << "  " << ride3->getName() << ": " << ride3->calculateFare(10, 1) << endl;

    // Base-class reference
    cout << "\n2) Through a base-class reference (80 km, 6 passengers):" << endl;
    BodaBoda boda;
    MinibusTaxi taxi;
    Bus bus;
    printQuote(boda, 80, 6);
    printQuote(taxi, 80, 6);
    printQuote(bus, 80, 6);

    // Vector of base-class pointers
    cout << "\n3) Looping over a vector of base-class pointers (25 km, 3 passengers):" << endl;
    vector<TransportMode *> options = {ride1, ride2, ride3};
    for (TransportMode *t : options) {
        cout << "  " << t->getName() << " -> UGX " << t->calculateFare(25, 3) << endl;
    }

    for (TransportMode *t : options) delete t;
    return 0;
}
