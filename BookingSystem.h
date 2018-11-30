// Matthías Ólafur
#pragma once
#ifndef BOOKINGSYSTEM_H
#define BOOKINGSYSTEM_H
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

namespace bs {
	class Booking {
	protected:
		int id;
		int capacity;
		int reserved;
	public:
		Booking(int id = 0, int capacity = 0, int reserved = 0) {
			this->id = id;
			this->capacity = capacity;
			if (calculatePercentage(reserved, capacity) > 105) {
				while (calculatePercentage(reserved, capacity) > 105) {
					reserved--;
				}
			}
			if (reserved < 0) {
				this->reserved = 0;
			}
			else {
				this->reserved = reserved;
			}
		}
		int getID() {
			return id;
		}
		int getCapacity() {
			return capacity;
		}
		int getReserved() {
			return reserved;
		}
		void virtual printStatus() {
			float percentage = calculatePercentage(reserved, capacity);
			cout << " Booking " << id << "\t : \t" << reserved << "/" << capacity << " (" << percentage << "%) seats reserved\n";
		}
		bool reserveSeats(int number_ob_seats) {
			if (number_ob_seats < 0) {
				return false;
			}
			else if (calculatePercentage(this->reserved, this->capacity) == 105) {
				return false;
			}
			else if (calculatePercentage(this->reserved + number_ob_seats, this->capacity) > 105) {
				while (calculatePercentage(this->reserved + number_ob_seats, this->capacity) > 105) {
					number_ob_seats--;
				}
			}
			if (number_ob_seats == 0) {
				return false;
			}
			this->reserved += number_ob_seats;
			return true;
		}
		bool cancelReservations(int number_ob_seats) {
			if (this->reserved - number_ob_seats < 0) {
				return false;
			}
			else if (number_ob_seats < 0) {
				return false;
			}
			else {
				this->reserved -= number_ob_seats;
				return true;
			}
			return false;
		}
		float calculatePercentage() {
			return calculatePercentage(this->reserved, this->capacity);
		}
		float calculatePercentage(float reserved, float capacity) {
			return round(((float)reserved / (float)capacity) * 100.0);
		}
		bool operator<(Booking &fb) {
			float booking1 = calculatePercentage();
			float booking2 = fb.calculatePercentage();
			if (booking1 < booking2) {
				return true;
			}
			return false;
		}
		bool operator>(Booking &fb) {
			float booking1 = calculatePercentage();
			float booking2 = fb.calculatePercentage();
			if (booking1 > booking2) {
				return true;
			}
			return false;
		}
		bool operator==(Booking &fb) {
			float booking1 = calculatePercentage();
			float booking2 = fb.calculatePercentage();
			if (booking1 == booking2) {
				return true;
			}
			return false;
		}
		bool operator!=(int tala) {
			if (id != tala && capacity != tala) {
				return true;
			}
			return false;
		}
		void virtual operator<<(string texti) {
			cout << "\n Booking " << id << " is " << texti << " full: " << calculatePercentage() << "%";
		}
	};
	class BusBooking : public Booking {
	public:
		BusBooking(int id = 0, int capacity = 0, int reserved = 0) : Booking(id, capacity, reserved) {};
		void printStatus() {
			float percentage = calculatePercentage(reserved, capacity);
			cout << " Bus " << id << "\t : \t" << reserved << "/" << capacity << " (" << percentage << "%) seats reserved\n";
		}
		void operator<<(string texti) {
			cout << "\n Bus " << id << " is " << texti << " full: " << calculatePercentage() << "%";
		}
	};
	class ShipBooking : public Booking {
	public:
		ShipBooking(int id = 0, int capacity = 0, int reserved = 0) : Booking(id, capacity, reserved) {};
		void printStatus() {
			float percentage = calculatePercentage(reserved, capacity);
			cout << " Ship " << id << "\t : \t" << reserved << "/" << capacity << " (" << percentage << "%) seats reserved\n";
		}
		void operator<<(string texti) {
			cout << "\n Ship " << id << " is " << texti << " full: " << calculatePercentage() << "%";
		}
	};
	class FlightBooking : public Booking {
	public:
		FlightBooking(int id = 0, int capacity = 0, int reserved = 0) : Booking(id, capacity, reserved) {};
		void printStatus() {
			float percentage = calculatePercentage(reserved, capacity);
			cout << " Flight " << id << "\t : \t" << reserved << "/" << capacity << " (" << percentage << "%) seats reserved\n";
		}
		void operator<<(string texti) {
			cout << "\n Flight " << id << " is " << texti << " full: " << calculatePercentage() << "%";
		}
	};
}

#endif