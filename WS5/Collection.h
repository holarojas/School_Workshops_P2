/*----------------------------------------------
// Workshop 5 - Functions and Error Handling
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail : mrrojas - martinez@myseneca.ca
ID : 112073218
Date : Oct. 18th, 2022
------ -
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
---------------------------------------------- */
#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <string>

namespace sdds
{
	//Manage a collection of items of template type.
	template <typename T>
	class Collection
	{
		
		std::string m_colName{}; //Name of the collection
		T* m_col{ nullptr }; //Dynamically allocated array of objects of type T
		size_t m_colSize{}; //Size of the array
		void (*m_ptrObs)(const Collection<T>&, const T&); //Observer function

		
	public:
		//Custom Constructor
		Collection(const std::string& name)
		{
			//Sets the name of the collection to the string referred to by the parameter
			m_colName = name;
			m_col = nullptr;
			m_colSize = 0;
			m_ptrObs = nullptr;
		}
		
		Collection(const Collection& other) = delete; //Copy constructor
		Collection& operator=(const Collection& other) = delete; //Copy assignment operator
		
		//Destructor
		~Collection()
		{
			delete[] m_col;
		};

		//Query that returns the name of the collection
		const std::string& name() const
		{
			return m_colName;
		}

		//Query that returns the number of items in the collection
		size_t size() const
		{
			return m_colSize;
		}

		//Stores the address of the callback function (observer) into an attribute.
		void setObserver(void (*observer)(const Collection<T>&, const T&))
		{
			//The parameter is a pointer to a function that returns void and accepts two parameters:
			//a collection and an item that has just been added to the collection.
			//This function is called when an item is added to the collection.
			//m_ptrObs = &(*observer);
			m_ptrObs = observer;
		}

		//Adds a copy of item to the collection, only if the collection doesn't contain an item with the same title.
		//Assumptions:
		//- Type T has a member function called title() that returns the title of the item (std::string)
		Collection<T>& operator+=(const T& item)
		{
			bool isFoundInCol = false;
			T* temp_col{ nullptr }; //Temporary array of any type
			
			//Search for the same title in the current collection array
			for (auto i = 0u; i < m_colSize; ++i) {
				if (m_col[i].title() == item.title()) {
					isFoundInCol = true;
				}
			}

			//If item is already in the collection, this function does nothing.
			if (!isFoundInCol) {
				//Creates a new array to save the current pointers
				temp_col = new T[m_colSize];
				for (auto i = 0u; i < m_colSize; ++i) {
					//Copy the current items to the temp array
					temp_col[i] = m_col[i];
				}

				//Resize the instance's array of any type
				//Step 1. Delete current array of any type 
				delete[] m_col;

				//Step 2. Add 1 to the count of items
				++m_colSize;

				//Step 3. Create a new array of any type of the new required size
				m_col = new T[m_colSize];

				//Step 4. Copy items from the temp array of any type  to the instance's array of any type
				if (m_colSize > 1) {
					for (auto i = 0u; i < m_colSize - 1; ++i) {
						m_col[i] = temp_col[i];
					}
				}

				//Step 5. Add new item to the end of the new size instance's array
				m_col[m_colSize - 1] = item;

				//Step 6. Deallocate memory used for temporary array
				delete[] temp_col;

				// - TODO: If an observer has been registered, this operator calls the observer function passing the current object (*this) and the new item as arguments
				if (m_ptrObs != nullptr) {
					m_ptrObs(*this, item);
				}
			}

			return *this;
		}

		//Returns the item at index idx
		T& operator[](size_t idx) const
		{
			if (idx > m_colSize - 1 || idx < 0) {
				std::out_of_range err_oor("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_colSize) + "] items.");
				throw err_oor;
			}

			return m_col[idx];
		}

		//Returns the address of the item with the title
		//Assumptions:
		//- Type T has a member function called title() that returns the title of the item
		T* operator[](const std::string& title)
		{
			//If no such item exists, this function returns nullptr
			T* ptr{ nullptr };

			//Search for the same title in the current collection array
			for (auto i = 0u; i < m_colSize; ++i) {
				if (m_col[i].title() == title) {
					ptr = &m_col[i];
				}
			}

			return ptr;
		}

	};

	//Free Helper Function
	//Overload insertion operator to insert the content of a Collection object into an ostream object
	template <typename T>
	std::ostream& operator<<(std::ostream& ostr, const Collection<T>& col)
	{
		//Iterate over all elements in the collection and insert each one into the ostream object
		for (auto i = 0u; i < col.size(); ++i) {
			ostr << col[i];
		}

		return ostr;
	}
}


#endif // !SDDS_COLLECTION_H
