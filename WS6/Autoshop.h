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
#ifndef SDDS_AUTOSHOP_H
#define SDDS_AUTOSHOP_H

#include "Vehicle.h"
#include <vector>
#include <list>

namespace sdds
{
	//Class that holds information about an autoshop that sells various types of vehicles.
	class Autoshop
	{
		std::vector<Vehicle*> m_vehicles; //Vector that store all the vehicles available at this autoshop

	public:
		Autoshop& operator +=(Vehicle* theVehicle);
		void display(std::ostream& out);
		~Autoshop();

		//Template Function
		template <typename T>
		void select(T test, std::list<const Vehicle*>& vehicles)
		{
			//Iterates over the vehicles stored in the m_vehicles,
			//and adds to the second parameter all vehicles for which the test is true.
			for (auto it = m_vehicles.begin(); it != m_vehicles.end(); ++it) {
				if (test(*it)) {
					vehicles.push_back(*it);
				}
			}
		}
	};
}


#endif // !SDDS_AUTOSHOP_H



