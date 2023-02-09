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
#include <iostream>
#include "Autoshop.h"


namespace sdds
{
	//Destructor
	Autoshop::~Autoshop()
	{
		//Iterate over the objects stored in the vector, and delete each one of them
		for (auto it = m_vehicles.begin(); it != m_vehicles.end(); ++it) {
			delete* it;
		}
	};

	//Adds the vehicle received as parameter into the m_vehicles vector
	Autoshop& Autoshop::operator +=(Vehicle* theVehicle)
	{
		m_vehicles.push_back(theVehicle);
		return *this;
	}

	//Iterates over the vehicles stored in m_vehicles and prints them into the parameter
	void Autoshop::display(std::ostream& out)
	{
		//Using Iterators
		for (auto it = m_vehicles.begin(); it != m_vehicles.end(); ++it) {
			(*it)->display(out);
			out << std::endl;
		}
	}
}