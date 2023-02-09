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

#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H

namespace sdds
{
	const size_t ARR_SIZE = 6;

	//This module holds two parallel arrays of strings, both of size 6 (statically allocated)
	class SpellChecker //Functor class
	{
		std::string m_badWords[ARR_SIZE];
		std::string m_goodWords[ARR_SIZE];
		size_t m_bwCount{};
		size_t m_gwCount{};
		size_t m_mispWordsCtr[ARR_SIZE]{}; //Array to keep count of each mispelled word

	public:
		SpellChecker(const char* filename);
		void operator()(std::string& text); 
		void showStatistics(std::ostream& out) const;
	};
}

#endif // !SDDS_SPELLCHECKER_H

