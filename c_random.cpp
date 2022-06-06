#include "c_random.h"
std::mt19937 c_random::f_random_engine;
std::uniform_int_distribution<std::mt19937::result_type> c_random::f_distribution;