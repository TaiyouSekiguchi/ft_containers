#ifndef TIMER_HPP
#define TIMER_HPP

#include <sys/time.h>
#include <iostream>

class Timer
{
	public:
		Timer();
		~Timer();

		void start();
		void stop();
		size_t getElapsedTime() const;

	private:
		struct timeval	start_time_;
		size_t 			elapsed_time_;

}; // class Timer

#endif // TIMER_HPP
