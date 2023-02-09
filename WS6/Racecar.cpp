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
#include <iostream>
#include "Racecar.h"

namespace sdds
{
	//Custom Constructor
	Racecar::Racecar(std::istream& in) : Car(in)
	{
		//Calls the constructor from Car to build the subobject,
		//and then it extracts the last field from the stream containing the booster bonus

		//Each record has the following format:
		//TAG,MAKER,CONDITION,TOP_SPEED,BOOSTER

		std::string temp{};

		std::getline(in, temp);
		m_booster = std::stod(temp);
	}

	//Calls Car::display() to print the information about the Car, and adds * at the end
	void Racecar::display(std::ostream& out) const
	{
		//Format should be:
		//| MAKER | CONDITION | TOP_SPEED |*
		Car::display(out);
		out << "*";
	}

	//Returns the top speed of the Car, including any booster effects
	double Racecar::topSpeed() const
	{
		return (Car::topSpeed() * m_booster) + Car::topSpeed();
	}



}