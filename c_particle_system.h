#pragma once
#include "c_effect.h"
#include "c_particle.h"
#include <vector>
#define MAX_EFFECTS 2048u
#define PARTICLE_EXPLODE_TIMER_MS 2000u
#define PARTICLE_EXPLODE_CHANCE 15u
class c_particle_system
{
public:
	c_particle_system();
	~c_particle_system();
	static c_particle_system* get_instance();
public:
	void initialize();
	void destroy();
	void update(float dt);
	void emit_effect(c_effect& vEffect);
	float get_time();
	std::vector<c_effect>& get_pool();//contains actual data
	std::vector<c_effect>& get_buffer();//contains data for render
private:
	std::vector<c_effect>m_effects_pool;
	std::vector<c_effect>m_effects_buffer;
	unsigned int effects_idx = MAX_EFFECTS-1;
	float global_time = 0u;
};

