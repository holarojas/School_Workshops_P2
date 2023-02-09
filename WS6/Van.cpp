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
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <sstream>
#include "Van.h"
#include "Utilities.h"

namespace sdds
{
	//Custom Constructor
	Van::Van(std::istream& input)
	{
		//Read a single record from the stream,
		//extract all the information about a single van,
		//and store it in the attributes.

		//Each record has the following format:
		//TAG,MAKER,TYPE,PURPOSE,CONDITION,TOP_SPEED
		
		std::string tag{};
		std::string validChars{ "cCvVlLrR" };
		std::string temp{};
		
		std::getline(input, tag, ',');
		size_t pos = tag.find_first_of(validChars);
		tag = tag[pos];
		trimWhiteSp(tag);

		std::getline(input, m_maker, ',');
		trimWhiteSp(m_maker);

		std::getline(input, m_type, ',');
		trimWhiteSp(m_type);
		//EXCHAND: If the type of the van is diff than p, m, or c
		//generate an exception to inform the client that this record is invalid
		if (m_type.find("p") == std::string::npos
			&& m_type.find("m") == std::string::npos
			&& m_type.find("c") == std::string::npos) {
			const char* err = "EXC: Type in this record is INVALID";
			throw err;
		}
		
		std::getline(input, m_purpose, ',');
		trimWhiteSp(m_purpose);
		//EXCHAND: If the purpose of the van is diff character than d, p, or c
		//generate an exception to inform the client that this record is invalid
		if (m_purpose.find("d") == std::string::npos
			&& m_purpose.find("p") == std::string::npos
			&& m_purpose.find("c") == std::string::npos) {
			const char* err = "EXC: Purpose in this record is INVALID";
			throw err;
		}
		
		std::getline(input, m_condition, ',');
		trimWhiteSp(m_condition);
		//EXCHAND: If condition is empty, consider that the car is new
		if (m_condition.empty()) {
			m_condition = "n";
		}
		//EXCHAND: If condition is a diff character than n, u, or b
		//generate an exception to inform the client that this record is invalid
		else if (m_condition.find("n") == std::string::npos
			&& m_condition.find("u") == std::string::npos
			&& m_condition.find("b") == std::string::npos) {
			const char* err = "EXC: Condition in this record is INVALID";
			throw err;
		}

		// Creating a stringstream to know if there is a comma separating values or not
		std::string line;
		std::stringstream iss;
		//Getting the final part of the record
		std::getline(input, line); 
		//Copying it into a stringstream
		iss << line; 

		//Returns the character(s) to the original stream for further processing in the LuxuryVan constructor
		for (auto i = 0u; i < line.size() + 1; ++i) {
			input.unget();
		}
		//---------------

		// Logic to know if we need to extract an additional value apart from the top speed or not
		//Search for a comma in the line
		if (line.find(',') != std::string::npos) {
			//Extract the value in the temp string
			std::getline(iss, temp, ',');
			trimWhiteSp(temp);
			//If the record is a normal van, then we need to get rid of the rest of the line
			//We don't care about values after the top speed in these cases
			if (tag == "v" || tag == "V") {
				input.ignore(256, '\n');
			}
			//If the record is something else (LuxuryVan), then only get rid of the top speed value.
			//We need to mantain the rest in the stream because the LuxuryVan constructor needs to read it
			else {
				input.ignore(256, ',');
			}
		}
		//If there is not a comma in the line, then capture until the new line
		else {
			std::getline(iss, temp);
			trimWhiteSp(temp);
			//Get rid of the characters in the original input stream
			input.ignore(256, '\n');
		}

		m_topSpeed = std::stod(temp);
	}

	//Query that returns new, used or broken, representing the condition of the van
	std::string Van::condition() const
	{
		std::string result{};

		if (m_condition == "n") {
			result = "new";
		}
		else if (m_condition == "u") {
			result = "used";
		}
		else if (m_condition == "b") {
			result = "broken";
		}

		return result;
	}

	//Query that returns the top speed
	double Van::topSpeed() const
	{
		return m_topSpeed;
	}

	//Query that returns pickup, mini-bus or camper, representing the type of van
	std::string Van::type() const
	{
		std::string result{};

		if (m_type == "p") {
			result = "pickup";
		}
		else if (m_type == "m") {
			result = "mini-bus";
		}
		else if (m_type == "c") {
			result = "camper";
		}

		return result;
	}

	//Query that returns delivery, passenger ot camping, representing the usage of the van
	std::string Van::usage() const
	{
		std::string result{};

		if (m_purpose == "d") {
			result = "delivery";
		}
		else if (m_purpose == "p") {
			result = "passenger";
		}
		else if (m_purpose == "c") {
			result = "camping";
		}

		return result;
	}

	//Query that inserts in the first parameter the content of the van object.
	void Van::display(std::ostream& ostr) const
	{
		//Format should be:
		// | MAKER | TYPE | USAGE | CONDITION | TOP_SPEED |

		ostr << "| " << std::setw(8) << std::right << m_maker << " | "
			<< std::setw(12) << std::left << type() << " | "
			<< std::setw(12) << std::left << usage() << " | "
			<< std::setw(6) << std::left << condition() << " | "
			<< std::setw(6) << std::setprecision(2) << topSpeed() << " |";
	}

}