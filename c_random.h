#pragma once
#include <random>
class c_random
{
public:
	static void initialize() {
		f_random_engine.seed(std::random_device()());
	}
	static float get_float() {//0.0 - 0.1f
		return (static_cast<float>(f_distribution(f_random_engine)) / (float)std::numeric_limits<uint32_t>::max())/10.f;
	}
	static bool get_bool(int chance) {
		return ((static_cast<float>(f_distribution(f_random_engine)) / (float)std::numeric_limits<uint32_t>::max())) <  static_cast<float>(chance)/100.f;
	}
private:
	static std::mt19937 f_random_engine;
	static std::uniform_int_distribution<std::mt19937::result_type> f_distribution;
};

