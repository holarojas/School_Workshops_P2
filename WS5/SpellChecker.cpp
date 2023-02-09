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
#include <fstream>
#include <string>
#include <iomanip>
#include "SpellChecker.h"

namespace sdds
{
	//Custom Constructor
	//Receives the address of a C-style null-terminated string that holds the name of the file that contains the mispelled words.
	SpellChecker::SpellChecker(const char* filename)
	{
		//If the file is missing, this constructor throws an exception
		std::ifstream file(filename);
		if (!file) {
			const char* err = "Bad file name!";
			throw err;
		}
		else { //If the file exists, this constructor loads its contents.
			std::string strRecord;

			do {
				
				getline(file, strRecord);
				if (!strRecord.empty()) { //To work even if the last record of the file is an \n
					
					size_t pos = 0;
					size_t posEnd = strRecord.find(" ", pos);
					m_badWords[m_bwCount] = strRecord.substr(pos, posEnd);
					++m_bwCount;

					pos = strRecord.find_first_not_of(" ", posEnd);
					posEnd = strRecord.find("\n", pos);
					m_goodWords[m_gwCount] = strRecord.substr(pos, posEnd);
					++m_gwCount;
				}
				
			} while (!file.eof());
		}
		file.close();
	}

	//Searches text and replaces any mispelled word with the correct version.
	void SpellChecker::operator()(std::string& text)
	{
		//It should count how many times each misspelled word has been replaced
		size_t pos{};
		size_t posFound{};

		//Search the whole text for each mispelled word [i]   at a time
		for (auto i = 0u; i < m_bwCount; ++i) {
			//Using iterators to keep reading after I find the [i] mispelled word
			for (auto it = text.begin(); it != text.end(); ++it) { 
				posFound = text.find(m_badWords[i], pos);
				//If mispelled word is found
				if (posFound != std::string::npos) {
					++m_mispWordsCtr[i];
					text.replace(posFound, m_badWords[i].length(), m_goodWords[i]);
					posFound = std::string::npos;
				}
				
			}
		}
		
	}

	//Inserts into the parameter how many times each mispelled word has been replaced by the correct word
	void SpellChecker::showStatistics(std::ostream& out) const
	{
		for (auto i = 0u; i < m_bwCount; ++i) {
			out << std::setw(15) << std::right << m_badWords[i] << ": "
				<< m_mispWordsCtr[i] << " replacements" << std::endl;
		}
	}

}