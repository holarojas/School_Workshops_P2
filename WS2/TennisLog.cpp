/*----------------------------------------------
// Workshop 2
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas-martinez@myseneca.ca
ID:		112073218
Date:	Sept. 25th, 2022
-------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
----------------------------------------------*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "TennisLog.h"

namespace sdds
{
	//Custom Arguments Constructor
	TennisMatch::TennisMatch(std::string tId, std::string tName, unsigned int mId, std::string w, std::string l)
	{
		tournamentId = tId;
		tournamentName = tName;
		matchId = mId;
		winner = w;
		loser = l;
	};

	//To output a TennisMatch object to an output stream.
	std::ostream& TennisMatch::print(std::ostream& os) const
	{
		//If a given TennisMatch object is in an empty state print "Empty Match"
		if (tournamentId.empty() && tournamentName.empty() && matchId == 0 && winner.empty() && loser.empty()) {
			os << "Empty Match";
		}
		else {
			//otherwise insert into the stream the content of the object
			os << std::right << std::setw(20) << std::setfill('.') << "Tourney ID" <<
				" : " << std::left << std::setw(30) << std::setfill('.') << tournamentId << std::endl;
			os << std::right << std::setw(20) << std::setfill('.') << "Match ID" <<
				" : " << std::left << std::setw(30) << std::setfill('.') << matchId << std::endl;
			os << std::right << std::setw(20) << std::setfill('.') << "Tourney" <<
				" : " << std::left << std::setw(30) << std::setfill('.') << tournamentName << std::endl;
			os << std::right << std::setw(20) << std::setfill('.') << "Winner" <<
				" : " << std::left << std::setw(30) << std::setfill('.') << winner << std::endl;
			os << std::right << std::setw(20) << std::setfill('.') << "Loser" <<
				" : " << std::left << std::setw(30) << std::setfill('.') << loser << std::endl;
			os << std::setfill(' ');
		}

		return os;
	}

	//Custom Argument Constructor
	TennisLog::TennisLog(char* fileName)
	{
		//Receives a filename as a parameter from which we'll populate the current object
		std::fstream fIn(fileName);
		
		if (!fIn.is_open()) {
			std::cout << "Cannot open file [" << fileName << "]." << std::endl;
		}

		while (!fIn.eof()) {
			// 1. Read the file to count the number of Tennis Matches in the file.
			readToCount(fIn);

			//Rewind the input stream to the beginning
			fIn.clear();
			fIn.seekg(0);

			// 2. Allocate dynamic memory for the array of matches based on the number found
			if (m_tennisMatch != nullptr) {
				delete[] m_tennisMatch;
				m_tennisMatch = new TennisMatch[tMatchCount];
			}
			else {
				m_tennisMatch = new TennisMatch[tMatchCount];
			}

			// 3. Reread the file from the beginning to load the actual match data into the array
			for (unsigned int i = 0; i < tMatchCount; ++i) {
				this->m_tennisMatch[i].read(fIn);
			}

			fIn.ignore('\n'); //<--Ignore last blank line from the file
		}
		fIn.close();
	}

	//Copy Constructor
	TennisLog::TennisLog(const TennisLog& other)
	{
		this->m_tennisMatch = nullptr;
		*this = other;
	}

	//Copy Assignment Operator
	TennisLog& TennisLog::operator=(const TennisLog& other)
	{
		//STEP 1. CHECK FOR SELF ASSIGNMENT
		if (this != &other) {
			//STEP 2. CLEANUP
			delete[] m_tennisMatch;

			//STEP 3. SHALLOW COPY
			this->tMatchCount = other.tMatchCount;

			//STEP 4. DEEP COPY
			if (other.m_tennisMatch != nullptr) {
				m_tennisMatch = new TennisMatch[tMatchCount];
				for (unsigned int i = 0; i < other.tMatchCount; ++i) {
					m_tennisMatch[i] = other.m_tennisMatch[i];
				}
			}
			else {
				this->m_tennisMatch = nullptr;
			}
		}

		return *this;
	}

	//Move Constructor
	TennisLog::TennisLog(TennisLog&& other) 
	{
		this->m_tennisMatch = nullptr;
		*this = std::move(other);
	}

	//Move Assignment Operator
	TennisLog& TennisLog::operator=(TennisLog&& other) 
	{
		//STEP 1. CHECK FOR SELF ASSIGNMENT
		if (this != &other) {
			//STEP 2. CLEANUP
			delete[] m_tennisMatch;

			//STEP 3. SHALLOW COPY
			this->tMatchCount = other.tMatchCount;
			other.tMatchCount = 0;
			

			//STEP 4. DEEP COPY FOR MOVING THE RESOURCES
			if (other.m_tennisMatch != nullptr) {
				m_tennisMatch = other.m_tennisMatch;
				other.m_tennisMatch = nullptr; //Set other instance's resource to nullptr
			}
			else {
				this->m_tennisMatch = nullptr;
			}

		}
		return *this;
	}

	//Destructor
	TennisLog::~TennisLog()
	{
		delete[] m_tennisMatch;
		m_tennisMatch = nullptr;
	}

	//Read the file to count the number of Tennis Matches in the file.
	void TennisLog::readToCount(std::istream& is)
	{
		std::string tempBuffer;

		if (is.tellg() == 0) {
			//Ignore first line
			is.ignore(100, '\n');
		}
		while (!is.eof()) {
			getline(is, tempBuffer, '\n');

			if (!tempBuffer.empty()) { //<--Prevent from counting the last blank line
				tMatchCount++;
			}
			
		}
	}

	//Reread the file from the beginning to load the actual match data into the array
	void TennisMatch::read(std::istream& is)
	{
		std::string tempStr;

		if (is.tellg() == 0) {
			//Ignore first line
			is.ignore(100, '\n');
		}

		getline(is, tournamentId, ',');
		getline(is, tournamentName, ',');
		getline(is, tempStr, ',');
		matchId = std::stoi(tempStr);
		getline(is, winner, ',');
		getline(is, loser, '\n');		
	}

	//Attempt to append the parameter to the dynamic array of matches held by the current object.
	void TennisLog::addMatch(const TennisMatch& newMatch)
	{
		TennisMatch tempMatch[100]{};


		//Resize the array appropriately to accomodate new objects and avoid memory leaks
		if (m_tennisMatch != nullptr) {

			//Copy the elements from the objects array to the temporary array
			for (unsigned int i = 0; i < tMatchCount; ++i) {
				tempMatch[i] = m_tennisMatch[i];
			}
			//Once the elements are copied then delete the last allocation
			delete[] m_tennisMatch;

			//Create the new dynamic array with the new count for matches
			tMatchCount++;
			m_tennisMatch = new TennisMatch[tMatchCount];

			//Copy the records from temp Array to the newly sized object TennisLog Matches array
			for (unsigned int i = 0; i < tMatchCount - 1; ++i) {
				m_tennisMatch[i] = tempMatch[i];
			}

			//Finally, Copy the new record to the object TennisLog Matches array
			m_tennisMatch[tMatchCount - 1] = newMatch;

		}
		else { //First record in the TennisLog Matches array
			tMatchCount++;
			m_tennisMatch = new TennisMatch[tMatchCount];
			m_tennisMatch[0] = newMatch;
		}
	}

	//Query that receives a name of a player as a parameter and returns a TennisLog object
	TennisLog TennisLog::findMatches(const std::string playerName) const
	{
		TennisLog tempLog{};

		delete[] tempLog.m_tennisMatch;
		tempLog.m_tennisMatch = new TennisMatch[tMatchCount];

		//Will return a TennisLog that contains all of the matches where  either the winner or loser's name matches the parameter
		for (unsigned int i = 0; i < tMatchCount; ++i) {
			if ((strcmp(playerName.c_str(), m_tennisMatch[i].winner.c_str()) == 0)
				|| (strcmp(playerName.c_str(), m_tennisMatch[i].loser.c_str()) == 0)) {
				
				tempLog.m_tennisMatch[tempLog.tMatchCount] = m_tennisMatch[i];
				tempLog.tMatchCount++;
			}
		}

		return tempLog;
	}

	//Query that will return the TennisMatch in the dynamic array at the index provided
	TennisMatch TennisLog::operator[](size_t index) const
	{
		TennisMatch temp{};
		//If the array isn't populated then return an empty TennisMatch instead
		if (m_tennisMatch != nullptr) {
			temp = m_tennisMatch[index];
		}

		return temp;
	}

	//Casting operator that will convert the current object to a size_t value
	TennisLog::operator size_t()
	{
		//The return type for this will be the size of the dynamic array of TennisMatches held by the current object
		return tMatchCount;
	}

	//Overload Insertion Operator
	std::ostream& operator<<(std::ostream& os, const TennisMatch& tMatch)
	{
		tMatch.print(os);
		return os;
	}

}