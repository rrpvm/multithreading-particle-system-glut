#pragma once
#include "vec2.h"
#define COLOR_ARGB(a,r,g,b)(((a&0xFF)<<24)|((r&0xFF)<<16)|((g&0xFF)<<8)|((b&0xFF)))
using COLOR_VALUE = unsigned long;
class alignas(64) c_particle //2 cases in 1 simd(__128bytes) or 4 cases in __256bytes, 0x29=>41bytes, 2^5 < 41 < 2^6
{
public:
	struct alignas(16) fl_color {//sizeof 0x10(16 bytes)
		float r;//0x4
		float g;//0x8
		float b;//0xC
		float a;//0x10
		fl_color() {
			this->r = 0.0f;
			this->g = 0.0f;
			this->b = 0.0f;
			this->a = 0.0f;
		}
		fl_color(const COLOR_VALUE rgba_value) {
			this->b = (rgba_value & 0xff) / 255.f;
			this->g = (((rgba_value >> 8) & 0xff)) / 255.f;
			this->r = (((rgba_value >> 16) & 0xff)) / 255.f;
			this->a = (((rgba_value >> 24) & 0xff)) / 255.f;
		}
		fl_color(const fl_color& vOther) {
			this->r = vOther.r;
			this->g = vOther.g;
			this->b = vOther.b;
			this->a = vOther.a;
		}
		fl_color(float r, float g, float b, float a) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
	};
	~c_particle();
	c_particle() { this->disabled = true; };
	c_particle(const vec2& pos, const vec2& velocity, const fl_color& color, const float lifetime);
	c_particle(const c_particle& vOther);
public:
	bool& is_disabled();
	float& get_lifetime();
	float get_timestamp() { return this->timestamp; };
	vec2& get_position();
	vec2& get_velocity() { return this->velocity; };
	fl_color& get_color();
	void set_statement(bool bDisabled);
public:
	bool update(const float dt);
	bool shouldExplode();
private:
	vec2 position;//0x0
	vec2 velocity;//0x8
	float lifetime{ 0.f };//0x10
	float timestamp{ 0.f };//0x14
	fl_color color;//0x18
	bool disabled{ false };//0x28
};// sizeof 0x29

