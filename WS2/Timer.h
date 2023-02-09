/*----------------------------------------------
// Workshop 2
// Michael Huang
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas-martinez@myseneca.ca
ID:		112073218
Date:	Sept. 25th, 2022
-------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.
----------------------------------------------*/
#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

namespace sdds
{
	//Useful in measuring how much time an operation takes
	class Timer
	{
		std::chrono::time_point<std::chrono::steady_clock> startTime{};

	public:
		void start();
		long long stop();
	};
}

#endif // !SDDS_TIMER_H

