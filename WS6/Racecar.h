/*----------------------------------------------
// Workshop 6 - STL Containers
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas - martinez@myseneca.ca
ID:		112073218
Date:	Nov 6th, 2022
------ -
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
---------------------------------------------- */
#ifndef SDDS_RACECAR_H
#define SDDS_RACECAR_H
#include "Car.h"

namespace sdds
{
	//A Racecar is a Car that for a short period of time can boost its speed by a certain percent
	class Racecar : public Car
	{
		double m_booster{}; //Percentage (stored as a number between 0 and 1) by which this Racecar can boost its top speed

	public:
		Racecar(std::istream& in);
		void display(std::ostream& out) const;
		double topSpeed() const;
	};
}

#endif // !SDDS_RACECAR_H

