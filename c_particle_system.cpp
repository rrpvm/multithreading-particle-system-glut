#include "c_particle_system.h"
#include "c_random.h"
#include <memory>
#include <algorithm>
void c_particle_system::update(float dt)
{
	this->global_time += dt;
	for (c_effect& _effect : this->m_effects_pool) {
		if (!_effect.is_alive())continue;
		_effect.update(dt);
	}
}
void c_particle_system::emit_effect(c_effect & vEffect)//функа создания эффектов
{
	if (this->effects_idx >= MAX_EFFECTS)return;
	c_effect* _effect = &this->m_effects_pool[this->effects_idx];
	if (_effect->is_alive())return;
	*_effect = vEffect;
	if (this->effects_idx <= 0u)this->effects_idx = MAX_EFFECTS - 1;
	else this->effects_idx--;
}
void c_particle_system::initialize()
{
	this->m_effects_pool.resize(MAX_EFFECTS);
	this->m_effects_buffer.resize(MAX_EFFECTS);
}
void c_particle_system::destroy()
{
	this->m_effects_buffer.clear();
	this->m_effects_pool.clear();
}
float c_particle_system::get_time()
{
	return this->global_time;
}
std::vector<c_effect>& c_particle_system::get_pool()
{
	return this->m_effects_pool;
}
std::vector<c_effect>& c_particle_system::get_buffer()
{
	return this->m_effects_buffer;
}
c_particle_system * c_particle_system::get_instance()
{
	static std::unique_ptr<c_particle_system> instance = NULL;
	if (!instance) {
		instance = std::make_unique<c_particle_system>();
	}
	return instance.get();
}
c_particle_system::c_particle_system()
{

}
c_particle_system::~c_particle_system()
{

}