/*----------------------------------------------
// Workshop 8 - Smart Pointers
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas - martinez@myseneca.ca
ID:		112073218
Date:	Nov 20th, 2022
------ -
LuhnAlgorithm code taken from:
https://www.geeksforgeeks.org/luhn-algorithm/
---------------------------------------------- */

#ifndef SDDS_GENERATINGLIST_H
#define SDDS_GENERATINGLIST_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {
	template<typename T>
	class GeneratingList {

		std::vector<T> list;
	public:

		GeneratingList(){}
		GeneratingList(const char* f) {
			std::ifstream file(f);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(f) + std::string(" ***");

			while (file) {
				T t;
				if (t.load(file))
					list.push_back(T(t));
			}
		}

		size_t size() const { return list.size(); }
		const T& operator[](size_t i) const { return list[i]; }

		//TODO: Implement the Luhn Algorithm to check the 
		//      valadity of SIN No's

		//Function receives a reference of a const std::string type representing the SIN to check and return true if the SIN is valid, false otherwise.
		bool luhnAlgorithm(const std::string& sin)
		{
			
			int sum{};
			bool isSecond{};

			//STEP 1. Starting from the rightmost digit, double the value of every second digit
			for (auto i = sin.length() - 1; i >= 0; --i) {
				int d = sin[i] - '0';

				if (isSecond == true) {
					d *= 2;
				}

				//STEP 2. If doubling of a number results in a two digit number, then add the digits of the product, to get a single digit number.
				sum += d / 10;
				sum += d % 10;

				isSecond = !isSecond;
			}
			//STEP 3. Take the sum of all the digits and if the total modulo 10 is equal to 0 then the number is valid.
			return (sum % 10 == 0);
		}

		// -------------------- END OF TODO ----------------------



		//TODO: Overload the += operator with a raw pointer
		// as a second operand.
		
		//Function that receives an address of an object to be stored in the GeneratingList container and moves the object into that container
		void operator+=(const T& obj)
		{
			list.push_back(obj);
			
		}

		// -------------------- END OF TODO ----------------------



		void print(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.print(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const GeneratingList<T>& rd) {
		rd.print(os);
		return os;
	}
}
#endif // !SDDS_GENERATINGLIST_H
