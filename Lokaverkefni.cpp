// Matthías Ólafur
#include "pch.h"
#include "BookingValmynd.h"
#include "LinkedList.h"
#include <iostream>
#include <string>

enum Velja { BUS = '1', SHIP, FLIGHT, QUIT };

using namespace std;
using namespace bv;
using namespace ll;

int main() {
	const char *val = new char('0');
	string valmynd;
	while (*val != Velja::QUIT) {
		cout << "\n--------------------------------\n\n";
		cout << "\t1. Bus Booking\n";
		cout << "\t2. Ship Booking\n";
		cout << "\t3. Flight Booking\n";
		cout << "\t4. Quit\n";
		cout << "\n--------------------------------\n\n ";
		getline(cin, valmynd);
		val = valmynd.c_str();
		if (*val == Velja::BUS) {
			BookingVal *bus = new BookingVal("Bus", "buses");
			bus->valmynd(new LL_Buses()); // Kallar á valmynd function í BookingValmynd.h
			delete bus;
		}
		else if (*val == Velja::SHIP) {
			BookingVal *ship = new BookingVal("Ship", "ships");
			ship->valmynd(new LL_Ships()); // Kallar á valmynd function í BookingValmynd.h
			delete ship;
		}
		else if (*val == Velja::FLIGHT) {
			BookingVal *flight = new BookingVal("Flight", "flights");
			flight->valmynd(new LL_Flights()); // Kallar á valmynd function í BookingValmynd.h
			delete flight;
		}
		else if (*val == Velja::QUIT) {
			continue;
		}
		else {
			cout << "\n ** Invalid input, please try again **\n";
		}
	}
	return 0;
}