#pragma once
#include <memory>
#include "c_effect.h"
class c_effects_factory
{
public:
	c_effect create_effect(int x, int y, int global_time);
};
extern std::unique_ptr<c_effects_factory> g_effect_factory;
