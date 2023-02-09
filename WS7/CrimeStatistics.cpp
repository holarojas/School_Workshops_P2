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
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include "CrimeStatistics.h"

size_t COL = 6; //Number of columns in file

namespace sdds
{
	//Custom Constructor
	CrimeStatistics::CrimeStatistics(const char* filename)
	{
		//Receives as a parameter the name of the file containing the information about the crime details of various district to be added to the collection
		std::ifstream file(filename);
		if (!file) {
			//If the filename is incorrect, this constructor should throw an exception
			throw "ERROR: Cannot open file.";
		}


		//The fields are not separated by delimiters; each field has a fixed size:
		//PROVINCE, DISTRICT and CRIME have exactly 25 characters.
		//YEAR, CASES and RESOLVED have exactly 5 characters.
		while (file.peek() != EOF) {

			//Each line from the file contains crime information about a single district in the following format:
			//PROVINCE DISTRICT CRIME YEAR CASES RESOLVED
			file >> m_aCrime.m_province;
			file >> m_aCrime.m_district;
			file >> m_aCrime.m_crime;
			file >> m_aCrime.m_year;
			file >> m_aCrime.m_noOfCases;
			file >> m_aCrime.m_resolved;
			
			m_crimes.push_back(m_aCrime);
		}

		file.close();
	}

	//Receives as a parameter the name of the field used to sort the collection of crimes in ascending order.
	void CrimeStatistics::sort(const char* fieldName)
	{
		
		if (strcmp(fieldName, "Province") == 0) {
			std::sort(m_crimes.begin(), m_crimes.end(), [](const Crime& lhs, const Crime& rhs) {
				return lhs.m_province < rhs.m_province;
				});
		} else if (strcmp(fieldName, "Crime") == 0) {
			std::sort(m_crimes.begin(), m_crimes.end(), [](const Crime& lhs, const Crime& rhs) {
				return lhs.m_crime < rhs.m_crime;
				});
		} else if (strcmp(fieldName, "Cases") == 0) {
			std::sort(m_crimes.begin(), m_crimes.end(), [](const Crime& lhs, const Crime& rhs) {
				return lhs.m_noOfCases < rhs.m_noOfCases;
				});
		} else if (strcmp(fieldName, "Resolved") == 0) {
			std::sort(m_crimes.begin(), m_crimes.end(), [](const Crime& lhs, const Crime& rhs) {
				return lhs.m_resolved < rhs.m_resolved;
				});
		}
			
	}
	
	//Removes the token [None] from the crime field of the crimes that do not have a valid crime.
	void CrimeStatistics::cleanList()
	{
		//Temporary object to use as replacement value if the search for the string m_crime is true
		Crime replacement{};
		
		std::replace_if(m_crimes.begin(), m_crimes.end(), [&replacement](const Crime& elem) -> bool {
			bool result = false;
			if (elem.m_crime == "[None]") {
				//Copy the original object's value to the temporary object
				replacement = elem;
				//Modify the string for the attribute m_crime
				replacement.m_crime = "";
				result = true;
			}
			return result;				 
			},  replacement);
	}
	
	//Receives the name of a crime as a parameter, and returns true if the collection contains any record with that crime
	bool CrimeStatistics::inCollection(const char* crimeName) const
	{
		return std::any_of(m_crimes.begin(), m_crimes.end(), [&crimeName](const Crime& elem) {
			return crimeName == elem.m_crime;
		});
	}
	
	//Receives the name of a province as a parameter, and returns the list of crimes of that province available in the collection
	std::list<Crime> CrimeStatistics::getListForProvince(const char* provinceName) const
	{
		auto isProvinceMatch = [&provinceName](const Crime& elem) {
			return elem.m_province == provinceName;
		};

		//Count the number of matches to have an exact size for the list
		auto cnt = std::count_if(m_crimes.begin(), m_crimes.end(), isProvinceMatch);
		//Create a list of an exact size for the matches
		std::list<Crime> newContainer(cnt);

		//Copy the matches to the list
		std::copy_if(m_crimes.begin(), m_crimes.end(), newContainer.begin(), isProvinceMatch);

		return newContainer;
	}
	
	//Print the content of the collection into the parameter
	void CrimeStatistics::display(std::ostream& out) const
	{
		size_t totCrimes{};
		size_t totResolved{};

		//One district details per line)
		//DO NOT USE MANUAL LOOPS!
		std::for_each(m_crimes.begin(), m_crimes.end(), [&](const Crime& elem) {
			std::cout << elem << std::endl;
			totCrimes += elem.m_noOfCases;
			totResolved += elem.m_resolved;
			}
		);

		out << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ');
		out << "|" << std::setw(79) << std::right << "Total Crimes: " << std::setw(6) << totCrimes << " |" << std::endl;
		out << "|" << std::setw(79) << std::right << "Total Resolved Cases: " << std::setw(6) << totResolved << " |" << std::endl;
	}

	//Inserts one Crime into the first parameter
	std::ostream& operator<<(std::ostream& out, const Crime& theCrime)
	{
		//Using the following format:
		//| PROVINCE(21) | DISTRICT(15) | CRIME(20) | YEAR(6) | CASES(4) | RESOLVED(3) |
		out << "| " << std::setw(21) << std::left << theCrime.m_province << " | "
			<< std::setw(15) << std::left << theCrime.m_district << " | "
			<< std::setw(20) << std::left << theCrime.m_crime << " | "
			<< std::setw(6) << std::right << theCrime.m_year << " | "
			<< std::setw(4) << std::right << theCrime.m_noOfCases << " | "
			<< std::setw(3) << std::right << theCrime.m_resolved << " |";

		return out;
	}



}