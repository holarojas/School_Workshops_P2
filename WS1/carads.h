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
#ifndef SDDS_CARADS_H
#define SDDS_CARADS_H


extern double g_taxrate;
extern double g_discount;

namespace sdds
{
	const int MAXL_BRAND = 10, MAXL_MODEL = 15;

	//Stores information about a car ad
	class Cars
	{
		char* m_carBrand{ nullptr };
		char* m_carModel{ nullptr };
		int carManYear{};
		double carPrice{};
		char carStatus{};
		bool carPromoDisc{};

	public:
		Cars(){}; //Default Constructor
		Cars(const Cars& other); //Copy Constructor
		~Cars(); //Default Destructor
		void read(std::istream& is);	
		void display(const bool reset) const; 
		char getStatus() const;

		operator bool() const;
		Cars& operator=(const Cars& other); //Copy Assignment operator

	};

	void listArgs(int argc, char** argv);

	std::istream& operator>>(std::istream& is, Cars& car);
	void operator>>(const Cars& car1, Cars& car2);
}
#endif // !SDDS_CARADS_H


