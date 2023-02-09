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
#include "Luxuryvan.h"
#include "Utilities.h"

namespace sdds
{
	//Custom Constructor
	Luxuryvan::Luxuryvan(std::istream& in): Van(in)
	{
		//Calls the constructor from Van to build the subobject, 
		//and then it extracts the last field from the stream containing the consumption type for the van.

		//Each record has the following format:
		//TAG,MAKER,TYPE,PURPOSE,CONDITION,TOP_SPEED,CONSUMPTION

		std::getline(in, m_consumption);
		trimWhiteSp(m_consumption);

		if (m_consumption == "g") {
			const char* err = "Invalid record!";
			throw err;
		}

	}

	//Calls Van::display() to print the information about the car, and adds electronic van * at the end, and ignores the gas consumed van.
	void Luxuryvan::display(std::ostream& out) const
	{
		//Format should be:
		// | MAKER | TYPE | USAGE | CONDITION | TOP_SPEED | electric van *
		Van::display(out);
		out << " electric van  *";

	}

	//Returns the string value of what type of consumption is van of.
	std::string Luxuryvan::consumption() const
	{
		return m_consumption;
	}

}