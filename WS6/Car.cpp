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
#include "Car.h"
#include "Utilities.h"

namespace sdds
{
	//Custom Constructor
	Car::Car(std::istream& input)
	{
		//Should be able to read a single record from the stream,
		//extract all the information about a single car and
		//store it in the attributes.

		//Each record has the following format:
		//TAG,MAKER,CONDITION,TOP_SPEED
		std::string tag{};
		std::string validChars{ "cCvVlLrR" };
		std::string temp{};

		std::getline(input, tag, ',');
		size_t pos = tag.find_first_of(validChars);
		tag = tag[pos];
		trimWhiteSp(tag);

		std::getline(input, m_maker, ',');
		trimWhiteSp(m_maker);
		
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
			//Ignore the rest of data in this record
			input.ignore(256, '\n'); 
			const char* err = "Invalid record!";
			throw err;
		}

		if (tag == "c" || tag == "C") {
			std::getline(input, temp);
			trimWhiteSp(temp);
		}
		else {
			std::getline(input, temp, ',');
			trimWhiteSp(temp);
		}

		
		//EXCHAND: If top speed is not a number, 
		//generate an exeption to inform the client that this record is invalid
		if (temp.find_first_not_of("0123456789") != std::string::npos) {
			//Ignore the rest of data in this record
			input.ignore(256, '\n'); 
			const char* err = "Invalid record!";
			throw err;
		}
		m_topSpeed = std::stod(temp);

	}


	//Query that returns new, used or broken, representing the condition of the car.
	std::string Car::condition() const
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
	double Car::topSpeed() const
	{
		return m_topSpeed;
	}

	//Query that inserts in the first parameter the content of the car object.
	void Car::display(std::ostream& ostr) const
	{
		//Format should be:
		// | MAKER | CONDITION | TOP_SPEED |
		ostr << "| " << std::setw(10) << std::right << m_maker << " | "
			<< std::setw(6) << std::left << condition() << " | "
			<< std::setw(6) << std::setprecision(2) << std::fixed << topSpeed() << " |";
	}


}