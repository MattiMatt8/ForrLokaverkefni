// Matthías Ólafur
#pragma once
#ifndef BOOKINGVALMYND_H
#define BOOKINGVALMYND_H
#include "BookingSystem.h"
#include "LinkedList.h"
#include <iostream>
#include <string>

using namespace std;
using namespace bs;
using namespace ll;

namespace bv {
	class BookingVal {
	private:
		string ord;   // t.d. Booking eða Flight
		string ord2;  // t.d. bookings eða flights
	public:
		BookingVal(string ord = "Booking" , string ord2 = "bookings") {
			this->ord = ord;
			this->ord2 = ord2;
		}
		void valmynd(LinkedList *booking) {
			cout << "\t" << ord << " Booking\n";
			string svar;
			cout << "\n Sort linkedlist by ascending order (yes/no): ";
			getline(cin, svar);
			if (svar == "no") {
				booking->setAsc(false);
			}
			string skjal;
			cout << "\n Use default " << ord2 << ".csv file to read/write (yes/no): ";
			getline(cin, svar);
			if (svar == "no") {
				cout << "\n File name: ";
				getline(cin, svar);
				skjal = svar;
				booking->setSkjal(skjal);
			}
			booking->lesa();
			string strengur, command;
			bool running = true;
			int id, n;
			while (running) {
				booking->prenta();
				cout << " Type in a command (create [id][cap], delete [id], deleteR [s_ID][l_ID], add [id][n], cancel [id][n], compare [id][id2], move [fromID][toID] or quit):\n\n ";
				getline(cin, strengur);
				stringstream ss(strengur);
				ss >> command >> id >> n;
				if (command == "create") { // "create [id][cap]"
					bool worked = booking->create(id, n);
					if (!worked) {
						cout << "\n ** " << ord << " already exists **\n";
					}
				}
				else if (command == "delete") { //  "delete [id]"
					bool worked = booking->del(id);
					if (!worked) {
						cout << "\n ** Operation failed, please try again **\n";
					}
				}
				else if (command == "deleteR") { //  "delete [s_id][l_id]"
					bool worked = booking->del(id, n);
					if (!worked) {
						cout << "\n ** Operation failed, please try again **\n";
					}
				}
				else if (command == "add") { // "add [id][n]"
					bool worked = booking->add(id, n);
					if (!worked) {
						cout << "\n ** Operation failed, please try again **\n";
					}
				}
				else if (command == "cancel") { // "cancel [id][n]"
					bool worked = booking->cancel(id, n);
					if (!worked) {
						cout << "\n ** Operation failed, please try again **\n";
					}
				}
				else if (command == "compare") { // "compare [id][id2]"
					Booking *booking1 = booking->getBooking(id);
					Booking *booking2 = booking->getBooking(n);
					if (booking1 != 0 && booking2 != 0) {
						cout << "\n---------- Comparison ----------\n";
						if (*booking1 > *booking2) {
							*booking1 << "more";
							*booking2 << "less";
						}
						else if (*booking1 < *booking2) {
							*booking2 << "more";
							*booking1 << "less";
						}
						else {
							*booking1 << "equally";
							*booking2 << "equally";
						}
						cout << "\n\n--------------------------------\n";
					}
					else {
						cout << "\n---------- Error ----------\n";
					}
				}
				else if (command == "move") { //  "move [fromID][toID]"
					bool worked = booking->move(id, n);
					if (!worked) {
						cout << "\n ** Operation failed, please try again **\n";
					}
				}
				else if (command == "quit") {
					booking->vista();
					delete booking;
					running = false;
				}
				else {
					cout << " ** Command not found, please try again **\n";
				}
			}
		}
	};
}

#endif