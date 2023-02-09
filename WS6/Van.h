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
#ifndef SDDS_VAN_H
#define SDDS_VAN_H

#include "Vehicle.h"

namespace sdds{

	//Class that holds information about a single van
	class Van : public Vehicle
	{
		std::string m_maker{}; //Name of the company that makes the car
		std::string m_type{}; //Can be of type p = pickup, m = minibus, or c = camper
		std::string m_condition{}; //Can be n = new, u = used or b = broken in need of repairs
		std::string m_purpose{}; //Can be used for a purpose of d = delivery, p = passenger or c = camping
		double m_topSpeed{};

	public:
		Van() {	};
		Van(std::istream& input);
		std::string condition() const;
		double topSpeed() const;
		std::string type() const;
		std::string usage() const;
		void display(std::ostream&) const;
		~Van() { };

	};
}

#endif // !SDDS_VAN_H

