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
#ifndef SDDS_QUEUE_H
#define SDDS_QUEUE_H

#include "Dictionary.h"

namespace sdds
{
	//Queue represents a queue of elements of any data type.
	//Objects get added to the back of the queue and are removed from the front of the queue.
	// T = The type of any element in the queue
	// CAPACITY = Maximum number of elements that can be added to the queue
	template<typename T, unsigned int CAPACITY>
	class Queue
	{
		T m_obj[CAPACITY]{};  //Statically-allocated array of objects of any type.
		unsigned int m_cnt{}; //How many objects the class is currently storing
		static T m_dummy; //This object will be returned by member-functions when the client requests an object that is not in the queue
	
	public:
		virtual bool push(const T& item); //Enable inclusion Polymorphism
		T pop();
		unsigned int size() const;
		void display(std::ostream& os = std::cout) const;
		T operator[](size_t index) const;
		T getObjInQueue(size_t index) const;
		unsigned int getObjCount() const;

		virtual ~Queue() {}; //Empty Body Destructor
	};

	template<typename T, unsigned int CAPACITY>
	T Queue<T, CAPACITY>::m_dummy{ };

	//Specialize the class-member object when type T=Dictionary and CAPACITY=100u
	//so the term is "Empty Term" and the definition is "Empty Substitute".
	template<>
	Dictionary Queue<Dictionary, 100u>::m_dummy{"Empty Term", "Empty Substitute"};


	//Mutator that adds a copy of the parameter to the queue if there still is capacity.
	//Assumptions:
	// - Copy Assignment Operator
	template<typename T, unsigned int CAPACITY>
	bool Queue<T, CAPACITY>::push(const T& item)
	{
		bool result = false;
		//If there is space for more objects in the array
		if (m_cnt < CAPACITY) {
			m_obj[m_cnt] = item;
			m_cnt++;
			//If the item has been added, this function return true; false otherwise.
			result = true;
		} 
		return result;
	}

	//Mutator that removes the first member of the queue.
	//This function returns a copy of the removed object
	//Assumptions:
	// - Copy Assignment Operator
	// - Copy Constructor
	template<typename T, unsigned int CAPACITY>
	T Queue<T, CAPACITY>::pop()
	{
		T tempCopy{};
		//It creates a temporary copy of it 
		tempCopy = m_obj[0];
		m_cnt--;
		
		//Shifts the rest of the queue elements forward by one index.
		for (unsigned int i = 0; i < m_cnt; ++i) {
			m_obj[i] = m_obj[i + 1];
		}
		
		return tempCopy;
	}

	//Query that returns the current number of elements in the queue
	template<typename T, unsigned int CAPACITY>
	unsigned int Queue<T, CAPACITY>::size() const
	{
		return m_cnt;
	}

	//Query that receives as the parameter an output stream (with default value std::cout)
	//Assumptions:
	// - Overload << operator
	template<typename T, unsigned int CAPACITY>
	void Queue<T, CAPACITY>::display(std::ostream& os) const
	{
		//Inserts into the stream all items from the collection
		os << "----------------------" << std::endl;
		os << "| Dictionary Content |" << std::endl;
		os << "----------------------" << std::endl;

		for (unsigned int i = 0; i < m_cnt; ++i) {
			os << m_obj[i] << std::endl;
		}

		os << "----------------------" << std::endl;
	}

	//Query that receives an index as parameter and returns a copy of the element stored in the collection at the specified index.
	//Assumptions:
	// - Copy Assignment Operator
	// - Copy Constructor
	template<typename T, unsigned int CAPACITY>
	T Queue<T, CAPACITY>::operator[](size_t index) const
	{
		T tempObj{};

		//If the index is not valid (outside of the boundaries of the collection), this query returns the dummy object
		if (index >= 0 && index < m_cnt) {
			tempObj = m_obj[index];
		}
		else { 
			tempObj = m_dummy;
		}

		return tempObj; 
	}

	//Query to give access of an specific Object in Queue
	template<typename T, unsigned int CAPACITY>
	T Queue<T, CAPACITY>::getObjInQueue(size_t index) const  
	{
		return m_obj[index];
	};

	//Query to give count of objects in Queue
	template<typename T, unsigned int CAPACITY>
	unsigned int Queue<T, CAPACITY>::getObjCount() const 
	{
		return m_cnt;
	};
	
}


#endif // !SDDS_QUEUE_H

