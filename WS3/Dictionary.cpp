/*----------------------------------------------
// Workshop 3 - Templates
// 2022/06/22 - This code was made by Nathan.
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas-martinez@myseneca.ca
ID:		112073218
Date:	Oct. 2nd, 2022
-------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
----------------------------------------------*/

#include <iostream>
#include <iomanip>
#include "Dictionary.h"

namespace sdds
{
	//Copy Constructor
	Dictionary::Dictionary(const Dictionary& other)
	{
		*this = other;
	}

	//Copy Assignment Operator
	Dictionary& Dictionary::operator=(const Dictionary& other)
	{
		//STEP 1. CHECK FOR SELF ASSIGNMENT
		if (this != &other) {
			//STEP 2. CLEANUP - no dynamic memory alloc
			//STEP 3. SHALLOW COPY
			m_term = other.m_term;
			m_definition = other.m_definition;
			//STEP 4. DEEP COPY - no dynamic memory alloc
		}
		return *this;
	}

	//Operator << overload
	std::ostream& operator<<(std::ostream& os, const Dictionary& dict)
	{
		os << std::setw(20) << std::right << dict.getTerm() << ": " << 
			 std::left << dict.getDefinition();
		return os;
	}

	//Comparison operator overload
	bool operator==(const Dictionary& item, const Dictionary& other)
	{
		return ((item.getTerm() == other.getTerm()) && item.getDefinition() == other.getDefinition());

	}
}