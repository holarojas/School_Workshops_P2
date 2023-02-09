/*----------------------------------------------
// Workshop 1
// Wail Mardini - 2022/07/04
// Cornel - 2022/09/08
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas-martinez@myseneca.ca
ID:		112073218
Date:	Sept. 17th, 2022
-------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
----------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "carads.h"


double g_taxrate;
double g_discount;

namespace sdds
{

	using std::cout;
	using std::endl;

	//Copy Constructor
	Cars::Cars(const Cars& other)
	{
		this->m_carBrand = nullptr;
		this->m_carModel = nullptr;
		*this = other;
	}

	//Default Destructor
	Cars::~Cars()
	{
		delete[] m_carBrand;
		delete[] m_carModel;
	}

	//Copy Assignment Operator
	Cars& Cars::operator=(const Cars& other)
	{
		//STEP 1. SELF FOR CHECK ASSIGNMENT
		if (this != &other) {
			//STEP 2. CLEANUP
			delete[] m_carBrand;
			delete[] m_carModel;

			//STEP 3. SHALLOW COPY
			this->carManYear = other.carManYear;
			this->carPrice = other.carPrice;
			this->carStatus = other.carStatus;
			this->carPromoDisc = other.carPromoDisc;

			//STEP 4. DEEP COPY
			if (other.m_carBrand != nullptr) {
				this->m_carBrand = new char[strlen(other.m_carBrand) + 1];
				strcpy(this->m_carBrand, other.m_carBrand);
			}
			else {
				this->m_carBrand = nullptr;
			}

			if (other.m_carModel != nullptr) {
				this->m_carModel = new char[strlen(other.m_carModel) + 1];
				strcpy(this->m_carModel, other.m_carModel);
			}
			else {
				this->m_carModel = nullptr;
			}
		}
		return *this;
	}

	//Bool Operator
	//Returns true if the Car is new, false otherwise
	Cars::operator bool() const
	{
		return this->carStatus == 'N';
	}

	//Function to echo the set of arguments to standard output
	//Receives the same parameters as the main function
	void listArgs(int argc, char** argv)
	{
		cout << "Command Line:" << endl;
		cout << "--------------------------" << endl;
		for (int i = 0; i < argc; i++) {
			cout << "  " << i + 1 << ": " << argv[i] << endl;
		}
		cout << "--------------------------\n" << endl;
	}

	//Read into file and store the info into the current object
	void Cars::read(std::istream& is)
	{
		if (!is.fail()) {

			char tempPromoDisc;
			char tempBrand[MAXL_BRAND];
			char tempModel[MAXL_MODEL];

			is.get(carStatus); //Extracts Status character
			is.ignore(); //Extracts the ','
			is.getline(tempBrand, MAXL_BRAND, ','); //Extracts Brand
			if (m_carBrand != nullptr) {
				delete[] m_carBrand;
				m_carBrand = new char[strlen(tempBrand) + 1];
				strcpy(m_carBrand, tempBrand);
			}
			else {
				m_carBrand = new char[strlen(tempBrand) + 1];
				strcpy(m_carBrand, tempBrand);
			}
			is.getline(tempModel, MAXL_MODEL, ','); //Extracts Model
			if (m_carModel != nullptr) {
				delete[] m_carModel;
				m_carModel = new char[strlen(tempModel) + 1];
				strcpy(m_carModel, tempModel);
			}
			else {
				m_carModel = new char[strlen(tempModel) + 1];
				strcpy(m_carModel, tempModel);
			}
			is >> carManYear; //Extracts Manufacture Year
			is.ignore(); //Extracts the ','
			is >> carPrice; //Extracts Price
			is.ignore(); //Extracts the ','
			is.get(tempPromoDisc);
			is.ignore(); //Extracts the '\n'

			if (tempPromoDisc == 'Y') {
				carPromoDisc = true;
			}
			else if (tempPromoDisc == 'N') {
				carPromoDisc = false;
			}

		}
	}

	//Query that displays to the screen the content of a Cars instance
	void Cars::display(const bool reset) const
	{
		static int counter;

		if (!reset) {
			counter++;
		}
		else {
			counter = 0;
			counter++;
		}

		if (m_carBrand == nullptr) {
			cout << std::left << std::setw(2) << std::setfill(' ') << counter << ". " <<
				std::setw(10) << "No Car";
		}
		else {
			if (carPromoDisc) {
				cout << std::left << std::setw(2) << std::setfill(' ') << counter << ". " <<
					std::setw(10) << m_carBrand << "| " <<
					std::setw(15) << m_carModel << "| " <<
					carManYear << " |" <<
					std::setw(12) << std::right << std::setprecision(2) << std::fixed << carPrice + (carPrice * g_taxrate) << "|" <<
					std::setw(12) << std::right << std::setprecision(2) << std::fixed << (carPrice + (carPrice * g_taxrate)) - (carPrice + (carPrice * g_taxrate)) * g_discount << endl;
			}
			else {
				cout << std::left << std::setw(2) << std::setfill(' ') << counter << ". " <<
					std::setw(10) << m_carBrand << "| " <<
					std::setw(15) << m_carModel << "| " <<
					carManYear << " |" <<
					std::setw(12) << std::right << std::setprecision(2) << std::fixed << carPrice + (carPrice * g_taxrate) << "|" << endl;
			}
		}
	}

	//Query that returns if the car is new or used
	char Cars::getStatus() const
	{
		return carStatus;
	}


	//Operators Overload
	std::istream& operator>>(std::istream& is, Cars& car)
	{
		car.read(is);
		return is;
	}

	//Copies in the second parameter the content of the first parameter
	void operator>>(const Cars& car1, Cars& car2)
	{
		car2 = car1;
	}
}
