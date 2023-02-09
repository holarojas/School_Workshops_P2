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
#include <iostream>
#include <string>
#include <iomanip>
#include "Book.h"

namespace sdds
{
	//Custom Constructor
	//Receives a reference to an unmodifiable string that contains information about the book
	Book::Book(const std::string& strBook)
	{
		//Lambda expression that removes whitespaces to the left and to the right of the token
		auto trimWhiteSp = [](std::string& str) {
			const std::string WHITESPACE = " \n\r\t\f\v";

			size_t start = str.find_first_not_of(WHITESPACE);
			if (start == std::string::npos) {
				str = "";
			}
			else {
				str = str.substr(start);
			}

			size_t end = str.find_last_not_of(WHITESPACE);
			if (end == std::string::npos) {
				str = "";
			}
			else {
				str = str.substr(0, end + 1);
			}
		};
		
		//Extracts the information about the book from the string by parsing it and stores the tokens in the object's attributes. 
		//The string always has the following format:
			//AUTHOR, TITLE, COUNTRY, PRICE, YEAR, DESCRIPTION
		size_t pos{};
		size_t posEnd{};

		for (auto i = 0u; i < NUMCOL; ++i) {
			pos = posEnd + 1;
			posEnd = strBook.find(",", pos);

			switch (i) {
			case 0:
				m_author = strBook.substr(0, posEnd);
				trimWhiteSp(m_author);
				break;
			case 1:
				m_title = strBook.substr(pos, posEnd - pos);
				trimWhiteSp(m_title);
				break;
			case 2:
				m_publCountry = strBook.substr(pos, posEnd - pos);
				trimWhiteSp(m_publCountry);
				break;
			case 3:
				m_price = std::stod(strBook.substr(pos, posEnd - pos));
				break;
			case 4:
				m_publYear = std::stoi(strBook.substr(pos, posEnd - pos));
				break;
			default:
				std::cout << "End of row reached.\n";
			}

		}

		//Here a comma is not longer the separator it is now the end of the string
		pos = posEnd + 1;
		m_descr = strBook.substr(pos, std::string::npos);
		trimWhiteSp(m_descr);

	}


	//Insertion Operator Overload
	//Insert the content of a book into  an ostream object
	std::ostream& operator<<(std::ostream& ostr, const Book& book)
	{
		ostr << std::setw(20) << book.m_author << " | "
			<< std::setw(22) << book.m_title << " | "
			<< std::setw(5) << book.m_publCountry << " | "
			<< std::setw(4) << book.m_publYear << " | "
			<< std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | "
			<< book.m_descr << std::endl;;

		return ostr;
	}

}
