/*----------------------------------------------
// Workshop 5 - Functions and Error Handling
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail : mrrojas - martinez@myseneca.ca
ID : 112073218
Date : Oct. 18th, 2022
------ -
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
---------------------------------------------- */
#include <iostream>
#include <string>
#include <iomanip>
#include "Movie.h"

namespace sdds
{
	//Custom Constructor
	//Receives the movie through a reference to a string
	Movie::Movie(const std::string& strMovie)
	{
		//Removes all spaces from the beginning and end of any token in the string
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


		//Extracts the information about the movie from the string and stores the tokens in the attributes.
		//The received string always has the following format:
		//TITLE,YEAR,DESCRIPTION

		size_t pos{};
		size_t posEnd{};

		for (auto i = 0u; i < NUMCOL_MOVIES; ++i) {
			pos = posEnd + 1;
			posEnd = strMovie.find(",", pos);

			switch (i) {
			case 0:
				m_title = strMovie.substr(0, posEnd);
				trimWhiteSp(m_title);
				break;
			case 1:
				m_releaseYear = std::stoi(strMovie.substr(pos, posEnd - pos));
				break;
			default:
				std::cout << "End of row reached.\n";
			}

		}

		//Here a comma is not longer the separator it is now the end of the string
		pos = posEnd + 1;
		m_descr = strMovie.substr(pos, std::string::npos);
		trimWhiteSp(m_descr);

	}

	//Overload insertion operator to insert the content of a movie object into an ostream object
	std::ostream& operator<<(std::ostream& ostr, const Movie& movie)
	{
		ostr << std::setw(40) << movie.m_title << " | "
			<< std::setw(4) << movie.m_releaseYear << " | "
			<< movie.m_descr << std::endl;

		return ostr;
	}

}