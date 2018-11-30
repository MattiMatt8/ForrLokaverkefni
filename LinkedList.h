// Matthías Ólafur
#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "BookingSystem.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
using namespace bs;

namespace ll {
	// LinkedList it keeps objects of the type Booking
	class LinkedList {
	protected:
		class Field {
		public:
			Booking *booking;
			Field *next;
			Field(Booking *booking = new Booking(), Field *next = nullptr) {
				this->booking = booking;
				this->next = next;
			}
			~Field() {
				delete booking;
			}
		};
		Field *head;
		Field *tail;
		bool asc;
		string skjal;
	public:
		LinkedList(bool asc = true, string skjal = "booking") {
			this->head = nullptr;
			this->tail = nullptr;
			this->asc = asc;
			skjal += ".csv";
			this->skjal = skjal;
		}
		~LinkedList() {
			if (head && tail) {
				Field *tmp = head;
				Field *tmp2;
				while (tmp) {
					tmp2 = tmp;
					tmp = tmp->next;
					delete tmp2;
				}
			}
		}
		void setAsc(bool asc) {
			this->asc = asc;
		}
		void setSkjal(string skjal) {
			skjal += ".csv";
			this->skjal = skjal;
		}
		void prenta() {
			if (head) {
				cout << endl;
				Field *tmp = head;
				while (tmp) {
					tmp->booking->printStatus();
					tmp = tmp->next;
				}
				cout << endl;
			}
			else {
				cout << "\n No bookings in the system\n\n";
			}
		}
		bool virtual create(int id, int n) {
			return create(new Booking(id,n));
		}
		bool create(Booking *booking) {
			int id = booking->getID();
			if (asc) {
				if (!head && !tail) {
					head = new Field(booking);
					tail = head;
				}
				else if (tail->booking->getID() < id) {
					Field *tmp = tail->next;
					tail->next = new Field(booking);
					tail = tail->next;
				}
				else if (head->booking->getID() > id) {
					Field *tmp = head;
					head = new Field(booking, tmp);
				}
				else {
					Field *tmp = head;
					Field *prev = head;
					bool found = false;
					while (tmp) {
						if (tmp->booking->getID() == id) {
							found = true;
							break;
						}
						if (tmp->booking->getID() > id) {
							break;
						}
						prev = tmp;
						tmp = tmp->next;
					}
					if (found) {
						delete booking;
						return false;
					}
					tmp = prev->next;
					prev->next = new Field(booking, tmp);
				}
				return true;
			}
			else {
				if (!head && !tail) {
					head = new Field(booking);
					tail = head;
				}
				else if (tail->booking->getID() > id) {
					Field *tmp = tail->next;
					tail->next = new Field(booking);
					tail = tail->next;
					delete tmp;
				}
				else if (head->booking->getID() < id) {
					Field *tmp = head;
					head = new Field(booking, tmp);
				}
				else {
					Field *tmp = head;
					Field *prev = head;
					bool found = false;
					while (tmp) {
						if (tmp->booking->getID() == id) {
							found = true;
							break;
						}
						if (tmp->booking->getID() < id) {
							break;
						}
						prev = tmp;
						tmp = tmp->next;
					}
					if (found) {
						delete booking;
						return false;
					}
					tmp = prev->next;
					prev->next = new Field(booking, tmp);
				}
				return true;
			}
		}
		void create(int id, int reservation, int capacity) {
			create(id, capacity);
			add(id, reservation);
		}
		bool del(int id) {
			if (!head && !tail) {
				return false;
			}
			else if (!head->next && head->booking->getID() == id) {
				Field *tmp = head;
				head = nullptr;
				tail = nullptr;
				delete tmp;
				return true;
			}
			else if (head->booking->getID() == id) {
				Field *tmp = head;
				head = head->next;
				delete tmp;
				return true;
			}
			Field *tmp = head;
			Field *prev = head;
			bool found = false;
			while (tmp) {
				if (tmp->booking->getID() == id) {
					found = true;
					break;
				}
				else if (tmp->booking->getID() > id && asc) {
					return false;
				}
				else if (tmp->booking->getID() < id && !asc) {
					return false;
				}
				prev = tmp;
				tmp = tmp->next;
			}
			if (found) {
				if (!tmp->next) {
					tail = prev;
				}
				prev->next = tmp->next;
				delete tmp;
				return true;
			}
			return false;
		}
		bool del(int s_id, int l_id) {
			if (s_id > l_id) {
				int tmp = s_id;
				s_id = l_id;
				l_id = tmp;
			}
			bool worked = false;
			for (int id = s_id; id <= l_id; id++) {
				if (del(id)) {
					worked = true;
				}
			}
			return worked;
		}
		bool add(int id, int reservation) {
			if (!head && !tail) {
				return false;
			}
			Field *tmp = head;
			Field *prev = head;
			bool found = false;
			while (tmp) {
				if (tmp->booking->getID() == id) {
					found = true;
					break;
				}
				else if (tmp->booking->getID() > id && asc) {
					return false;
				}
				else if (tmp->booking->getID() < id && !asc) {
					return false;
				}
				prev = tmp;
				tmp = tmp->next;
			}
			if (found) {
				bool worked = tmp->booking->reserveSeats(reservation);
				if (!worked) {
					return false;
				}
				return true;
			}
			return false;
		}
		bool cancel(int id, int reservation) {
			if (!head && !tail) {
				return false;
			}
			Field *tmp = head;
			Field *prev = head;
			bool found = false;
			while (tmp) {
				if (tmp->booking->getID() == id) {
					found = true;
					break;
				}
				else if (tmp->booking->getID() > id && asc) {
					return false;
				}
				else if (tmp->booking->getID() < id && !asc) {
					return false;
				}
				prev = tmp;
				tmp = tmp->next;
			}
			if (found) {
				bool worked = tmp->booking->cancelReservations(reservation);
				if (!worked) {
					return false;
				}
				return true;
			}
			return false;
		}
		bool move(int from_id, int to_id) {
			Booking *from = getBooking(from_id);
			Booking *to = getBooking(to_id);
			int f_reserved = from->getReserved();
			int t_reserved = to->getReserved();
			bool worked = to->reserveSeats(f_reserved);
			if (worked) {
				int t_reserved_a = to->getReserved();
				int mismunur = t_reserved_a - t_reserved;
				from->cancelReservations(mismunur);
				cout << "\n -- Moved " << mismunur << " reservations from " << from_id << " to " << to_id << endl;
				return true;
			}
			return false;
		}
		Booking *getBooking(int bookingID) {
			if (head) {
				Field *tmp = head;
				while (tmp) {
					if (tmp->booking->getID() == bookingID) {
						return tmp->booking;
					}
					tmp = tmp->next;
				}
				return tmp->booking;
			}
		}
		void lesa() {
			int x;
			string lina;
			string tala;
			ifstream skjal(this->skjal);
			if (skjal.is_open()) {
				int listi[3];
				while (getline(skjal, lina)) {
					stringstream splitta(lina);
					x = 0;
					while (getline(splitta, tala, ';')) {
						listi[x] = stoi(tala);
						x++;
					}
					create(listi[0], listi[1], listi[2]);
				}
				skjal.close();
			}
		}
		void vista() {
			ofstream skjal(this->skjal);
			if (skjal.is_open()) {
				Field *tmp = head;
				while (tmp) {
					skjal << tmp->booking->getID() << ";" << tmp->booking->getReserved() << ";" << tmp->booking->getCapacity() << "\n";
					tmp = tmp->next;
				}
			}
		}
	};
	// LL_Buses is a subclass of LinkedList and keeps objects of the type BusBooking
	class LL_Buses : public LinkedList {
	public:
		LL_Buses(bool asc = true, string skjal = "buses") : LinkedList(asc, skjal) {};
		bool create(int id, int n) {
			bool worked = LinkedList::create(new BusBooking(id, n));
			return worked;
		}
	};
	// LL_Ships is a subclass of LinkedList and keeps objects of the type ShipBooking
	class LL_Ships : public LinkedList {
	public:
		LL_Ships(bool asc = true, string skjal = "ships") : LinkedList(asc, skjal) {};
		bool create(int id, int n) {
			bool worked = LinkedList::create(new ShipBooking(id, n));
			return worked;
		}
	};
	// LL_Flights is a subclass of LinkedList and keeps objects of the type FlightBooking
	class LL_Flights : public LinkedList {
	public:
		LL_Flights(bool asc = true, string skjal = "flights") : LinkedList(asc, skjal) {};
		bool create(int id, int n) {
			bool worked = LinkedList::create(new FlightBooking(id, n));
			return worked;
		}
	};
}

#endif