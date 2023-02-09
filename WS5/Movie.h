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
#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H

namespace sdds
{
	unsigned int const NUMCOL_MOVIES = 2; //Number of columns separated by comma in data entry
	unsigned int const TOP_MOVIES = 5; //Number of movies to load into Collection


	//Stores information for a single Movie
	class Movie
	{
		friend std::ostream& operator<<(std::ostream& ostr, const Movie& movie);

		std::string m_title{};
		size_t m_releaseYear{};
		std::string m_descr{};

	public:
		Movie()	{ }; //Default Constructor
		Movie(const std::string& strMovie);
		const std::string& title() const { return m_title; }; //Query that returns the title of the movie
		
		//Templated Function
		//Assumptions:
		//- Type T must have an overloaded operator() that accepts a string as a parameter
		template <typename T>
		void fixSpelling(T& spellChecker)
		{
			//Calls the overload operator() on instance spellChecker, passing to it the movie title and description
			
			spellChecker(m_title);
			spellChecker(m_descr);

		}
		
	};
}

#endif // !SDDS_MOVIE_H

