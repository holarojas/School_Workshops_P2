/*----------------------------------------------
// Workshop 3 - Templates
// 2022/06/22 - This code was made by Nathan.
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas-martinez@myseneca.ca
ID:		112073218
Date:	Oct. 2nd, 2022
-------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
----------------------------------------------*/
#ifndef SDDS_DICTIONARY_H
#define SDDS_DICTIONARY_H

namespace sdds
{
	class Dictionary
	{
		std::string m_term{};
		std::string m_definition{};
	public:
		const std::string& getTerm() const { return m_term;	}
		const std::string& getDefinition() const { return m_definition;	}
		Dictionary(){};
		Dictionary(const std::string& term, const std::string& definition) : m_term{ term }, m_definition{ definition } {}
		//TODO:
		//Code the missing prototype functions and operators
		//that the class needs in order to work with the Queue class.
		//Implement them in the Dictionary.cpp file.
		Dictionary(const Dictionary& other);
		Dictionary& operator=(const Dictionary& other);
	};

	std::ostream& operator<<(std::ostream& os, const Dictionary& dict);
	bool operator==(const Dictionary& item, const Dictionary& other);
}

#endif // !SDDS_DICTIONARY_H

