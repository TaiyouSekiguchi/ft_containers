#ifndef BENCHMARK_TEST_HPP
#define BENCHMARK_TEST_HPP

#include <iostream>
#include <ctime>   // time
#include <cstdlib> // srand, rand
#include "Timer.hpp"

#ifdef FT
#define PRE ft
#include "../../containers/vector.hpp"
#include "../../containers/stack.hpp"
#include "../../containers/map.hpp"
#else
#define PRE std
#include <vector>
#include <stack>
#include <map>
#endif

#define SIZE 1000

#endif // BENCHMARK_TEST_HPP
