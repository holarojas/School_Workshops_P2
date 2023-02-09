/*----------------------------------------------
// Workshop 3 - Templates
// 2022/06/22 - This code was made by Nathan.
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas-martinez@myseneca.ca
ID:		112073218
Date:	Oct. 2nd, 2022
-------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
----------------------------------------------*/
#ifndef SDDS_UNIQUEQUEUE_H
#define SDDS_UNIQUEQUEUE_H

#include <cmath>
#include "Queue.h"


namespace sdds
{
	//UniqueQueue is a Queue that cannot have multiple items with the same value inside it
	//This class doesn't allow duplicates
	template<typename T>
	class UniqueQueue : public Queue<T,100>
	{

	public:
		bool push(const T& item) override;
	};


	//Mutator that adds a copy of the parameter to the queue if there still is capacity and it is not duplicated.
	//Assumptions:
	// - Comparison Operator == Overload
	template<typename T>
	bool UniqueQueue<T>::push(const T& item) 
	{
		bool result = false;
		bool duplicate = false;

		//Check for duplicates of the item in the current Queue
		for (unsigned int i = 0; i < Queue<T, 100>::getObjCount(); ++i) {
			if (Queue<T, 100>::getObjInQueue(i) == item) {
				duplicate = true;
			}
		}

		//Add the item in the UniqueQueue only if it's not a duplicate
		if (!duplicate) {
			result = Queue<T, 100>::push(item);
		}

		return result;
	}

	//Specialize the function when working with doubles
	template <>
	bool UniqueQueue<double>::push(const double& item)
	{
		bool result = false;
		bool duplicate = false;

		for (unsigned int i = 0; i < getObjCount(); ++i) {
			if (fabs(getObjInQueue(i)) < (fabs(item) - 0.005) || fabs(getObjInQueue(i)) > (fabs(item) + 0.005)) {
				//Both items are considered different
			}
			else {
				duplicate = true;
			}
		}

		if (!duplicate) {
			result = Queue<double, 100>::push(item);
		}

		return result;
	}


}

#endif // !SDDS_UNIQUEQUEUE_H

