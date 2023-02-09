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
#ifndef SDDS_CAR_H
#define SDDS_CAR_H

#include "Vehicle.h"

namespace sdds
{
	//Holds information about a single car
	class Car : public Vehicle
	{
		std::string m_maker{}; //Name of the company that makes the car
		std::string m_condition{}; //n = New, u = Used, b = Broken
		double m_topSpeed{};

	public:
		Car() {	};
		Car(std::istream& input);
		std::string condition() const;
		double topSpeed() const;
		void display(std::ostream&) const;
		~Car() { };
	};


}

#endif // !SDDS_CAR_H