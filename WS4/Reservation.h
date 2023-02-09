/*----------------------------------------------
// Workshop 4 - Containers
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas-martinez@myseneca.ca
ID:		112073218
Date:	Oct. 11th, 2022
-------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
----------------------------------------------*/
#ifndef SDDS_RESERVATION_H
#define SDDS_RESERVATION_H

namespace sdds
{
	unsigned int const NUMCOL = 5; //Number of columns separated by comma in data entry

	class Reservation
	{

		friend std::ostream& operator<<(std::ostream& ostr, const Reservation& res);

		std::string m_resId{};		//Reservation ID
		std::string m_name{};			//Name on Reservation
		std::string m_email{};		//Email used to send confirmation
		unsigned int m_pplQty{};	//Number of people in the party
		unsigned int m_day{};			//Day when party expects to come ( 1 - 28)
		unsigned int m_hour{};		//Hour when the party expects to come ( 1 - 24)

	public:
		Reservation() {	};	//Default Constructor
		Reservation(const std::string& res); //Constructor Overload
		~Reservation() { }; //Destructor

		void update(int day, int time);
		void trimWhites(std::string& str); //Remove leading and trailing whitespaces
		

	};

	
}

#endif // !SDDS_RESERVATION_H
