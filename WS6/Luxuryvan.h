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
#ifndef SDDS_LUXURYVAN_H
#define SDDS_LUXURYVAN_H
#include "Van.h"

namespace sdds
{
	//A Luxuryvan is a Van that identifies a Van that is considered luxourious and is also electric
	class Luxuryvan : public Van
	{
		std::string m_consumption{}; //Stores the value vans which can be used electronic power

	public:
		Luxuryvan(std::istream& in);
		void display(std::ostream& out) const;
		std::string consumption() const;
	};
}

#endif // !SDDS_LUXURYVAN_H
