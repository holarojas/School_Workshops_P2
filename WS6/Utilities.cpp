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
#include <sstream>
#include <string>
#include "Utilities.h"
#include "Racecar.h"
#include "Luxuryvan.h"
#include "Car.h"
#include "Van.h"

namespace sdds
{
	//Function that creates instances on the Vehicle hierarchy
	Vehicle* createInstance(std::istream& in)
	{
		//Should extract data from the parameter;
		//If the first non-blank character is "c" or "C", "v" or "V":
		//This function should dynamically create an instance of type Car or Van passing the stream to the constructor, and return it to the client.

		Vehicle* pObj{ nullptr };
		std::string alph{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
		std::string temp{};
		std::string firstChar{};


		std::getline(in, temp, ',');
		//Matching to the whole alphabet to have a value stored in firstChar even if the char value is not accepted by the program. We need the value to throw it in the error.
		size_t pos = temp.find_first_of(alph);
		//Only store the value in firstChar if a letter is found
		if (pos != std::string::npos) {
			firstChar = temp[pos];
		}

		//Returns the character(s) to the stream for further processing in the constructors
		for (auto i = 0u; i < temp.size() + 1; ++i) {
			in.unget(); 
		}
		
		//Checkpoint to know if we have reached the end of the stream
		if (!in.fail()) {
			if (firstChar == "c" || firstChar == "C") {
				pObj = new Car(in);
			}
			else if (firstChar == "v" || firstChar == "V") {
				pObj = new Van(in);
			}
			else if (firstChar == "r" || firstChar == "R") {
				pObj = new Racecar(in);
			}
			else if (firstChar == "l" || firstChar == "L") {
				pObj = new Luxuryvan(in);
			}
			else {
				//Ignore the rest of data in this record
				in.ignore(256, '\n'); 
				std::out_of_range err_oor("Unrecognized record type: [" + firstChar + "]");
				throw err_oor;
			}
		}


		return pObj;
	}

	//Function that removes whitespaces to the left and to the right of the token
	void trimWhiteSp(std::string& str) 
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

}