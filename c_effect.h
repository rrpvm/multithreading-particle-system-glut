#pragma once
#include <vector>
#include "c_particle.h"
#define PARTICLE_EXPLODE_NODES 64u
class c_effect
{
public:
	c_effect();
	c_effect(const c_effect& vOther);
	~c_effect();
public:
	void update(float flUpdate);
	void emit_particle(c_particle& particle);
public:
	bool is_alive();
	uint32_t get_idx();
	std::vector<c_particle>& get_particles();
private:
	std::vector<c_particle>particles_container;
	int particle_idx = PARTICLE_EXPLODE_NODES-1u;
	bool alive{ true };
};

