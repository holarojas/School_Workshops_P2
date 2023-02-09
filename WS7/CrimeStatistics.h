/*----------------------------------------------
// Workshop 7 - STL Algorithms
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas - martinez@myseneca.ca
ID:		112073218
Date:	Nov 13th, 2022
------ -
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
---------------------------------------------- */
#ifndef SDDS_CRIMESTATISTICS_H
#define SDDS_CRIMESTATISTICS_H

#include <vector>
#include <list>

namespace sdds
{
	//Structure capable of storing information about a crime
	struct Crime
	{
		std::string m_province{};
		std::string m_district{};
		std::string m_crime{};
		unsigned int m_year{};
		size_t m_noOfCases{};
		size_t m_resolved{};

	};

	//Class that manages a collection of objects of type Crime
	class CrimeStatistics
	{
		Crime m_aCrime{};
		std::vector<Crime> m_crimes;

	public:
		CrimeStatistics(const char* filename);
		void display(std::ostream& out) const;
		void sort(const char* fieldName);
		void cleanList();
		bool inCollection(const char* crimeName) const;
		std::list<Crime> getListForProvince(const char* provinceName) const;
		
	};

	//Helper Functions
	std::ostream& operator<<(std::ostream& out, const Crime& theCrime);
}


#endif // SDDS_CRIMESTATISTICS_H !