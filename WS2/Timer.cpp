/*----------------------------------------------
// Workshop 2
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas-martinez@myseneca.ca
ID:		112073218
Date:	Sept. 25th, 2022
-------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
For chronos usage I got examples from:
https://en.cppreference.com/w/cpp/chrono/time_point
----------------------------------------------*/
#include <iostream>
#include <chrono>
#include "Timer.h"


using namespace std::chrono;

namespace sdds
{
	//Modifier that starts the timer
	void Timer::start()
	{
		//Takes the current timestamp and stores it in an attribute
		startTime =	steady_clock::now();
	}

	//Modifier that stops the timer
	long long Timer::stop()
	{
		//Takes the current timestamp and 
		const auto endTime = steady_clock::now();
		
		//Returns how many nanoseconds passed since  the timer has started as a long long value
		long long duration = duration_cast<nanoseconds>(endTime - startTime).count();
		return duration;
	}

}
