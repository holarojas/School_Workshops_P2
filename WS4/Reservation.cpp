/*----------------------------------------------
// Workshop 4 - Containers
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas-martinez@myseneca.ca
ID:		112073218
Date:	Oct. 11th, 2022
-------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
-------
I got help from this site:
https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/#:~:text=We%20can%20use%20a%20combination,functions%20to%20trim%20the%20string.
for removing the leading and trailing whitespaces
----------------------------------------------*/
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "Reservation.h"

namespace sdds
{
	//Remove leading and trailing whitespaces
	//Got some of this logic from a website. See top commented line for more info.
	void Reservation::trimWhites(std::string& str)
	{
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
	}

	//Constructor
	//Receives the reservation as a string.
	//Responsible for extracting information about the reservation from the string and storing the tokens in the instance's attributes.
	Reservation::Reservation(const std::string& res)
	{
		//The string will always have the following format
		//ID:NAME,EMAIL,PARTY_SIZE,DAY,HOUR
		//Remove all leading and trailing spaces from the beginning and end of any token extracted from the string.

		std::string tempStr = res;
		size_t pos{}; 
		size_t posFind{};


		posFind = tempStr.find(":");
		m_resId = tempStr.substr(0, posFind);
		trimWhites(m_resId);

		for (auto i = 0u; i < NUMCOL; ++i) {
			pos = posFind + 1;
			posFind = tempStr.find(",", pos);

			switch (i) {
			case 0:
				m_name = tempStr.substr(pos, posFind - pos);
				trimWhites(m_name);
				break;
			case 1:
				m_email = tempStr.substr(pos, posFind - pos);
				trimWhites(m_email);
				break;
			case 2:
				m_pplQty = stoi(tempStr.substr(pos, posFind - pos));
				break;
			case 3:
				m_day = stoi(tempStr.substr(pos, posFind - pos));
				break;
			case 4:
				m_hour = stoi(tempStr.substr(pos, posFind - pos));
				break;
			default:
				std::cout << "End of row\n";
			}
		}
		
	}

	//Modifier that receives as parameters a new day and time for the reservation
	//and updates the attributes with received values
	//Don't require validation
	void Reservation::update(int day, int time)
	{
		m_day = day;
		m_hour = time;
	}

	std::ostream& operator<<(std::ostream& ostr, const Reservation& res)
	{
		std::string kwKitchen;
		std::string kwPeople;

		
		//Decision about keyword for Kitchen Hours
		if (res.m_hour >= 6 && res.m_hour <= 9) {
			kwKitchen = "Breakfast";
		}
		else if (res.m_hour >= 11 && res.m_hour <= 15) {
			kwKitchen = "Lunch";
		}
		else if (res.m_hour >= 17 && res.m_hour <= 21) {
			kwKitchen = "Dinner";
		}
		else {
			kwKitchen = "Drinks";
		}

		//Decision about keyword for People
		if (res.m_pplQty > 1) {
			kwPeople = " people.";
		}
		else {
			kwPeople = " person.";
		}

		ostr << "Reservation " << std::setw(10) << std::right << res.m_resId << ": "
			<< std::setw(20) << res.m_name << "  "
			<< std::left << std::setw(19) << "<" + res.m_email + ">"
			<< "     " << kwKitchen << " on day " << res.m_day << " @ " << res.m_hour << ":00 for " << res.m_pplQty << kwPeople << std::endl;
		
		return ostr;
	}

}
