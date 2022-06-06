#include "c_particle.h"
#include "c_random.h"
#include "c_particle_system.h"
c_particle::c_particle(const vec2& pos, const vec2& velocity, const fl_color& color,const float lifetime)
{
	this->position = pos;
	this->velocity = velocity;
	this->color = color;
	this->lifetime = lifetime;
	this->timestamp = lifetime;//stores the full lifetime
	this->disabled = false;
}
bool c_particle::update(const float dt)
{
	return true;
	//nothing to implement
}
bool c_particle::shouldExplode()
{
	return c_random::get_bool(PARTICLE_EXPLODE_CHANCE);
}
vec2& c_particle::get_position()
{
	return this->position;
}
c_particle::fl_color & c_particle::get_color()
{
	return this->color;
}
void c_particle::set_statement( bool b_disabled)
{
	this->disabled = b_disabled;
}
bool& c_particle::is_disabled()
{
	return this->disabled;
}
float& c_particle::get_lifetime()
{
	return this->lifetime;
}
c_particle::c_particle(const c_particle & vOther)
{
	this->position = vOther.position;
	this->velocity = vOther.velocity;
	this->color = vOther.color;
	this->lifetime = vOther.lifetime;
	this->disabled = vOther.disabled;
	this->timestamp = vOther.timestamp;
}
c_particle::~c_particle()
{

}