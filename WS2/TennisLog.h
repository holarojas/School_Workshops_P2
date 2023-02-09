/*----------------------------------------------
// Workshop 2
// Michael Huang
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
#ifndef SDDS_TENNISLOG_H
#define SDDS_TENNISLOG_H

#include <string>

namespace sdds
{
	struct TennisMatch
	{
		std::string tournamentId{};
		std::string tournamentName{};
		unsigned int matchId{};
		std::string winner{};
		std::string loser{};

		TennisMatch() {};
		TennisMatch(std::string tId, std::string tName, unsigned int mId, std::string w, std::string l);
		
		void read(std::istream& is);
		std::ostream& print(std::ostream& ostr) const;
	};

	//Class that will manage a dynamic array of TennisMatches and keep a count of how many are being stored
	class TennisLog
	{
		TennisMatch* m_tennisMatch{ nullptr };
		size_t tMatchCount{};

	public:
		TennisLog()	{};
		TennisLog(char* fileName);
		TennisLog(const TennisLog& other); //1. Copy Constructor
		TennisLog(TennisLog&& other); //4. Move Constructor
		~TennisLog(); //3. Destructor

		void readToCount(std::istream& is);
		void addMatch(const TennisMatch& newMatch);
		TennisLog findMatches(const std::string playerName) const;

		TennisLog& operator=(const TennisLog& other); //2. Copy Assignment Operator
		TennisLog& operator=(TennisLog&& other); //5. Move Assignment Operator
		TennisMatch operator[](size_t index) const;
		operator size_t();
	};

	std::ostream& operator<<(std::ostream& os, const TennisMatch& tMatch);
	
}

#endif // !SDDS_TENNISLOG_H

