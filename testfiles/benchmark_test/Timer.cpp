#include "Timer.hpp"

Timer::Timer()
	: elapsed_time_(0)
{
}

Timer::~Timer()
{
}

void	Timer::start()
{
	gettimeofday(&start_time_, NULL);
}

void	Timer::stop()
{
	struct timeval stop_time;
	gettimeofday(&stop_time, NULL);
	elapsed_time_ += (stop_time.tv_sec - start_time_.tv_sec) * 1000 * 1000 + stop_time.tv_usec - start_time_.tv_usec;
}

size_t Timer::getElapsedTime() const
{
	return (elapsed_time_);
}
