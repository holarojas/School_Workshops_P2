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
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include "Vehicle.h"

namespace sdds
{
	Vehicle* createInstance(std::istream& in);
	void trimWhiteSp(std::string& str);
}


#endif // !SDDS_UTILITIES_H

