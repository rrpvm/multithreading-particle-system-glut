#include "c_effects_factory.h"
#include "c_random.h"
#include "c_particle_system.h"
std::unique_ptr<c_effects_factory> g_effect_factory;
c_effect c_effects_factory::create_effect(int x, int y,int global_time)
{
	c_effect effect = c_effect();//in stack, not heap
	const c_particle::fl_color color = c_particle::fl_color(COLOR_ARGB(255, 255, 0, 0));
	const vec2 origin = vec2(x, y);
	for (size_t i = 0u; i < PARTICLE_EXPLODE_NODES; ++i) {
		const float lifetime = PARTICLE_EXPLODE_TIMER_MS +  c_random::get_float() * 5e+4;
		vec2 velocity = vec2(c_random::get_float() * (c_random::get_bool(50) ? 1.f : -1.f), c_random::get_float()*1.5f);
		c_particle particle = c_particle(origin, velocity, color, lifetime);
		effect.emit_particle(particle);
	}
	return effect;
}
