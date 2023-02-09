/*----------------------------------------------
// Workshop 8 - Smart Pointers
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas - martinez@myseneca.ca
ID:		112073218
Date:	Nov 20th, 2022
------ -
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
---------------------------------------------- */
#include <algorithm> //Included
#include "GeneratingList.h"
#include "EmpProfile.h"
#include "WritingRecord.h"

using namespace std;

namespace sdds {
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;
		
		// TODO: Add your code here to build a list of employees
		//         using raw pointers

		//Function that creates a list of active employees;
		//- An employee is considered active if both lists received as parameters contain an employee with the same SIN.
		//- For each active employee found in both lists, dynamically create a new object of type EmployeeWage and add it to the collection activeEmp

		std::string compSIN{};

		for (auto i = 0u; i < emp.size(); ++i) {
			for (auto j = 0u; j < sal.size(); ++j) {
				if (emp[i].id == sal[j].id) {
					//Employee is Active
					
					
					//Dynamically created new object
					EmployeeWage* actEmpObj = new EmployeeWage(emp[i].name, sal[j].salary);

					//Validate Salary Range
					actEmpObj->rangeValidator();

					//Validate the SIN using Luhn's Algorithm
					if (activeEmp.luhnAlgorithm(emp[i].id)) {
						//Add the object to the list
						activeEmp += *actEmpObj;
					}
					else {
						std::string err = "EXC: SIN is NOT VALID!";
						throw err;
					}
					
				}
			}
			
		}

		
		// -------------------- END OF TODO ----------------------

		
		return activeEmp;
	}
}