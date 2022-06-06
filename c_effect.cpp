#include "c_effect.h"
#include "c_particle_system.h"
#include "c_effects_factory.h"
#include "test.h"
void c_effect::update(float dt)
{
	this->alive = false;
	if (particles_container.empty())return;
	for (c_particle& particle : particles_container) {
		if (particle.is_disabled())continue;
		particle.get_lifetime() -= dt;
		particle.get_color().a = (particle.get_lifetime() / particle.get_timestamp());

		if (particle.get_lifetime() <= 0.0f) {
			particle.is_disabled() = true;
			if (particle.shouldExplode()) {
				/*5head code detected*/
				c_particle_system::get_instance()->emit_effect(g_effect_factory->create_effect(particle.get_position().x(), particle.get_position().y(), particle.get_timestamp()));
				break;
			}
		}
		auto& pos = particle.get_position();
		if (pos.x() < 0.0f || pos.y() > test::SCREEN_HEIGHT + 5 || pos.x() > test::SCREEN_WIDTH) {
			particle.is_disabled() = true;
			//particle.get_lifetime() = 0.0f;
			continue;
		}
		pos = pos + (particle.get_velocity() * dt);
		this->alive = true;
	}
}
void c_effect::emit_particle(c_particle & particle)
{
	if (this->particle_idx >= PARTICLE_EXPLODE_NODES)return;
	c_particle* _particle = &this->particles_container[this->particle_idx];
	if (!_particle->is_disabled())return;
	*_particle = particle;
	if (this->particle_idx <= 0)this->particle_idx = PARTICLE_EXPLODE_NODES - 1;
	else this->particle_idx--;
}
bool c_effect::is_alive()
{
	return this->alive;
}
std::vector<c_particle>& c_effect::get_particles()
{
	return this->particles_container;
}
uint32_t c_effect::get_idx()
{
	return this->particle_idx;
}
c_effect::~c_effect()
{
	this->particles_container.clear();
}
c_effect::c_effect()
{
	this->particles_container.resize(PARTICLE_EXPLODE_NODES);
	this->particle_idx = PARTICLE_EXPLODE_NODES - 1;
	this->alive = true;
}
c_effect::c_effect(const c_effect & vOther)
{
	this->particles_container = vOther.particles_container;
	this->particle_idx = vOther.particle_idx;
	this->alive = vOther.alive;
}