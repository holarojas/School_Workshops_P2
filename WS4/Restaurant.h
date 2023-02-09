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
#ifndef SDDS_RESTAURANT_H
#define SDDS_RESTAURANT_H
#include "Reservation.h"

namespace sdds
{
	//This module should mantain a dynamically allocated array of pointers to objects of type Reservation
	class Restaurant
	{
		friend std::ostream& operator<<(std::ostream& ostr, const Restaurant& rest);

		Reservation** m_ppReserv{ nullptr };	//Dynamically allocated array of pointers
		size_t m_reservCnt{};	//Number of reservations in the system
		
	
	public:
		Restaurant(const Reservation* reservations[], size_t cnt); //Constructor Overload
		Restaurant(const Restaurant& other); //Copy Constructor
		Restaurant& operator=(const Restaurant& other); //Copy Assignment Operator
		Restaurant(Restaurant&& other); //Move Constructor
		Restaurant& operator=(Restaurant&& other); //Move Assignment Operator
		~Restaurant(); //Destructor

		size_t size() const;
	};

}

#endif // !SDDS_RESTAURANT_H