/*----------------------------------------------
// Workshop 5 - Functions and Error Handling
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas-martinez@myseneca.ca
ID:		112073218
Date:	Oct. 18th, 2022
-------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
----------------------------------------------*/
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <string>

namespace sdds
{
	unsigned int const NUMCOL = 5; //Number of columns separated by comma in data entry
	unsigned int const TOP_BOOKS = 4; //Number of books to load into Collection

	//This module holds information about a single book
	class Book
	{
		friend std::ostream& operator<<(std::ostream& ostr, const Book& book);

		std::string m_author{};
		std::string m_title{};
		std::string m_publCountry{};
		size_t m_publYear{};
		double m_price{};
		std::string m_descr{}; //Short summary of the book
		

	public:
		Book()	{ }; //Default Cnstructor
		Book(const std::string& strBook);

		const std::string& title() const {	return m_title;	};	//Query that returns the title of the book
		const std::string& country() const	{ return m_publCountry;	};	//Query that returns the publication country
		const size_t& year() const	{ return m_publYear; };	//Query that returns the publication year
		double& price() { double& ref = m_price; return ref; };		//Function that returns the price by reference, allowing the client code to update the price

		//Templated Function
		//Assumptions:
		//- Type T must have an overloaded operator() that accepts a string as a parameter
		template <typename T>
		void fixSpelling(T& spellChecker)
		{
			//Calls the overloaded operator() on the instance SpellChecker. Passing to it the book descr.
			spellChecker(m_descr);
		}

	};

}


#endif // !SDDS_BOOK_H
