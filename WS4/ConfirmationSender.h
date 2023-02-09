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
#ifndef SDDS_CONFIRMATIONSENDER_H
#define SDDS_CONFIRMATIONSENDER_H
#include "Reservation.h"

namespace sdds
{
	//Purpose of this module is to receive all the reservations from multiple restaurants,
	//and contact the recipients with a confirmation message.
	class ConfirmationSender
	{
		friend std::ostream& operator<<(std::ostream& ostr, const ConfirmationSender& confSend);

		const Reservation** m_ppConfReserv{ nullptr }; //Dynamically allocated array of pointers
		size_t m_confReservCnt{};	//Number of confirmed reservations in the system

	public:
		ConfirmationSender() { };	//Default Constructor
		ConfirmationSender(const ConfirmationSender& other); //Copy Constructor
		ConfirmationSender& operator=(const ConfirmationSender& other); //Copy Assignment Operator
		ConfirmationSender(ConfirmationSender&& other); //Move Constructor
		ConfirmationSender& operator=(ConfirmationSender&& other); //Move Assignment Operator
		~ConfirmationSender();

		ConfirmationSender& operator+=(const Reservation& res);
		ConfirmationSender& operator-=(const Reservation& res);
	};

}

#endif // !SDDS_CONFIRMATIONSENDER_H
