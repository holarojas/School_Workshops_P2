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
#include "Restaurant.h"



namespace sdds
{
	//Constructor - Should store copies of all reservations
	//Receives as a parameter an array of pointers to objects of type Reservation
	Restaurant::Restaurant(const Reservation* reservations[], size_t cnt)
	{
		
		delete[] m_ppReserv;
		//Creating array of pointers of type Reservation of size cnt
		m_ppReserv = new Reservation * [cnt];

		for (auto i = 0u; i < cnt; ++i) {
			m_ppReserv[i] = new Reservation(*reservations[i]);
		}
		m_reservCnt = cnt;

	}

	//Copy Constructor
	Restaurant::Restaurant(const Restaurant& other)
	{
		m_reservCnt = 0;
		m_ppReserv = nullptr;
		//Calling copy assignment
		*this = other;
	}

	//Copy Assignment Operator
	Restaurant& Restaurant::operator=(const Restaurant& other)
	{
		//1. CHECK FOR SELF ASSIGNMENT
		if (this != &other) {
			//2. CLEANUP TO GUARANTEE THIS ALWAYS WORKS
			for (auto i = 0u; i < m_reservCnt; ++i) {
				delete m_ppReserv[i];
			}
			delete[] m_ppReserv;

			//3. SHALLOW COPY
			m_reservCnt = other.m_reservCnt;

			//4. DEEP COPY
			if (other.m_ppReserv != nullptr) {
				m_ppReserv = new Reservation * [m_reservCnt];
				for (auto i = 0u; i < m_reservCnt; ++i) {
					m_ppReserv[i] = new Reservation();
					*m_ppReserv[i] = *other.m_ppReserv[i];
				}
			}
			else {
				m_ppReserv = nullptr;
			}
		}

		return *this;
	}

	//Move Constructor
	Restaurant::Restaurant(Restaurant&& other)
	{
		m_reservCnt = 0;

		m_ppReserv = nullptr;
		//Calling Move Assignment Operator
		*this = std::move(other);
	}

	//Move Assignment Operator
	Restaurant& Restaurant::operator=(Restaurant&& other)
	{
		//1. CHECK FOR SELF ASSIGNMENT
		if (this != &other) {
			//2. CLEANUP TO GUARANTEE THIS ALWAYS WORKS
			for (auto i = 0u; i < m_reservCnt; ++i) {
				delete m_ppReserv[i];
			}
			delete[] m_ppReserv;

			//3. SHALLOW MOVE
			m_reservCnt = other.m_reservCnt;
			other.m_reservCnt = 0;

			//4. DEEP MOVE
			m_ppReserv = other.m_ppReserv;
			other.m_ppReserv = nullptr;
		}
			
		return *this;
	}

	//Destructor
	Restaurant::~Restaurant()
	{
		for (auto i = 0u; i < m_reservCnt; ++i) {
			delete m_ppReserv[i];
		}
		delete[] m_ppReserv;
	}

	//Query that returns the number of reservations in the system
	size_t Restaurant::size() const
	{
		return m_reservCnt;
	}


	std::ostream& operator<<(std::ostream& ostr, const Restaurant& rest)
	{
		static size_t CALL_CNT;

		++CALL_CNT;
		ostr << "--------------------------\n"
			<< "Fancy Restaurant (" << CALL_CNT << ")\n"
			<< "--------------------------\n";

		if (rest.m_reservCnt == 0) {
			ostr << "This restaurant is empty!\n";
		}
		else {
			for (auto i = 0u; i < rest.m_reservCnt; ++i) {
				ostr << *rest.m_ppReserv[i];
			}
		}

		ostr << "--------------------------\n";

		return ostr;
	}
}