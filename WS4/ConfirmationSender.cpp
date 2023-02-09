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

#include <iostream>
#include "ConfirmationSender.h"


namespace sdds
{
	//Copy Constructor
	ConfirmationSender::ConfirmationSender(const ConfirmationSender& other)
	{
		m_ppConfReserv = nullptr;
		m_confReservCnt = 0;
		//Calling copy assignment operator
		*this = other;
	}

	//Copy Assignment Operator
	ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& other)
	{
		//1. CHECK FOR SELF ASSIGNMENT
		if (this != &other) {
			//2. CLEANUP TO GUARANTEE THIS ALWAYS WORKS
			delete[] m_ppConfReserv;

			//3. SHALLOW COPY
			m_confReservCnt = other.m_confReservCnt;

			//4. DEEP COPY
			if (other.m_ppConfReserv != nullptr) {
				m_ppConfReserv = new const Reservation * [m_confReservCnt];
				for (auto i = 0u; i < m_confReservCnt; ++i) {
					m_ppConfReserv[i] = other.m_ppConfReserv[i];
				}
			}
			else {
				m_ppConfReserv = nullptr;
			}
		}

		return *this;
	}

	//Move Constructor
	ConfirmationSender::ConfirmationSender(ConfirmationSender&& other)
	{
		m_ppConfReserv = nullptr;
		m_confReservCnt = 0;
		//Calling Move Assignment operator
		*this = std::move(other);
	}
	
	//Move Assignment Operator
	ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& other)
	{
		//1. CHECK FOR SELF ASSIGNMENT
		if (this != &other) {
			//2. CLEANUP TO GUARANTEE THIS ALWAYS WORKS
			delete[] m_ppConfReserv;

			//3. SHALLOW MOVE
			m_confReservCnt = other.m_confReservCnt;
			other.m_confReservCnt = 0;

			//4. DEEP MOVE
			m_ppConfReserv = other.m_ppConfReserv;
			other.m_ppConfReserv = nullptr;
		}
		return *this;
	}

	//Destructor
	ConfirmationSender::~ConfirmationSender()
	{
		delete[] m_ppConfReserv;
	}


	//Insertion Operator Overload
	//Inserts the content of a ConfirmationSender object into an ostream object
	std::ostream& operator<<(std::ostream& ostr, const ConfirmationSender& confSend)
	{
		ostr << "--------------------------\n"
			<< "Confirmations to Send\n"
			<< "--------------------------\n";

		//If there are not Confirmations to send
		if (confSend.m_confReservCnt == 0) {
			ostr << "There are no confirmations to send!\n";
				
		}
		else {
			for (auto i = 0u; i < confSend.m_confReservCnt; ++i) {
				ostr << *confSend.m_ppConfReserv[i];
			}
		}

		ostr << "--------------------------\n";

		return ostr;
	}


	//Adds the reservation to the array by adding its address
	ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res)
	{
		bool isReservFound = false;
		const Reservation** temp_ppConfReserv{ nullptr };

		//Check if res already exists in array of Confirmed Reservations
		for (auto i = 0u; i < m_confReservCnt; ++i) {
			if (m_ppConfReserv[i] == &res) {
				isReservFound = true;
			}
		}

		//If the address of res is already in the array, this operator does nothing
		if (!isReservFound) {
			//Create a new array of pointers to Reservations to save the current pointers
			if (m_confReservCnt > 0) {
				temp_ppConfReserv = new const Reservation * [m_confReservCnt];
				for (auto i = 0u; i < m_confReservCnt; ++i) {
					//Copy the pointer to each reservation
					temp_ppConfReserv[i] = m_ppConfReserv[i];
				}
			}

			//Steps to Resize Array of Pointers

			//Step 1. Delete current array of pointers to confirmed reservations
			//(now we have the pointers saved in the temp Array
			delete[] m_ppConfReserv;

			//Step 2. Add 1 to the count of confirmed reservations
			++m_confReservCnt;

			//Step 3. Create a new array of pointers of the new required size
			m_ppConfReserv = new const Reservation * [m_confReservCnt];

			//Step 4. Copy current addresses from temp array (old size array) to new size array
			if (m_confReservCnt > 1) {
				for (auto i = 0u; i < m_confReservCnt - 1; ++i) {
					m_ppConfReserv[i] = temp_ppConfReserv[i];
				}
			}

			//Step 5. Add address of res to the end of new size array of pointers
			m_ppConfReserv[m_confReservCnt - 1] = &res;

			//Step 6. Deallocate memory used for temporary array
			delete[] temp_ppConfReserv;
		}
		return *this;
	}

	//Removes the reservation res from the array by removing its address
	ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res)
	{
		bool isReservFound = false;
		const Reservation** temp_ppConfReserv{ nullptr };
		auto idxFound = 0u;

		//Check if res already exists in array of Confirmed Reservations
		for (auto i = 0u; i < m_confReservCnt; ++i) {
			//Searches the array for the address of res
			if (m_ppConfReserv[i] == &res) {
				isReservFound = true;
				idxFound = i;
				//Sets the pointer in the array to nullptr if res is found
				m_ppConfReserv[i] = nullptr;
			}
		}

		if (isReservFound) {
			//Create a new array of pointers to Reservations to save the current pointers
			if (m_confReservCnt > 0) {
				temp_ppConfReserv = new const Reservation * [m_confReservCnt - 1];
				for (auto i = 0u; i < m_confReservCnt; ++i) {
					if (i < idxFound) {
						//Copy the pointer to each reservation
						temp_ppConfReserv[i] = m_ppConfReserv[i];
					}
					else if (i == idxFound) {
						//Don't copy the nullptr element
					}
					else {
						temp_ppConfReserv[i - 1] = m_ppConfReserv[i];
					}
				}
			}

			//Steps to Resize Array of Pointers

			//Step 1. Delete current array of pointers to confirmed reservations
			//(now we have the pointers saved in the temp Array
			delete[] m_ppConfReserv;

			//Step 2. Subtract 1 to the count of confirmed reservations
			--m_confReservCnt;

			//Step 3. Create a new array of pointers of the new required size
			m_ppConfReserv = new const Reservation * [m_confReservCnt];

			//Step 4. Copy current addresses from temp array (old size array) to new size array
			if (m_confReservCnt > 1) {
				for (auto i = 0u; i < m_confReservCnt; ++i) {
					m_ppConfReserv[i] = temp_ppConfReserv[i];
				}
			}

			//Step 5. Deallocate memory used for temporary array
			delete[] temp_ppConfReserv;

		}

		return *this;
	}



}