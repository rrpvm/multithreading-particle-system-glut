#pragma once
#include <stdint.h>
#include <cmath>
#include <limits>
class alignas(8) vec2 //2^3, <= 0x4 + 0x4 == 0x8
{
public:
	~vec2() {};
	vec2() {};
	vec2(float x, float y) {
		this->_x = x;
		this->_y = y;
	}
	vec2(const vec2& vOther) {
		this->_x = vOther._x;
		this->_y = vOther._y;
	}
	inline float x() {
		return this->_x;
	}
	inline float y() {
		return this->_y;
	}
	inline double magnitude() {
		return sqrt(pow(this->_x, 2) + pow(this->_y, 2));
	}
	inline vec2 operator+(const vec2& vOther) {
		return vec2(this->_x + vOther._x, this->_y + vOther._y);
	}
	inline vec2 operator-(const vec2& vOther) {
		return vec2(this->_x - vOther._x, this->_y - vOther._y);
	}
	inline vec2 operator*(const vec2& vOther) {
		return vec2(this->_x * vOther._x, this->_y * vOther._y);
	}
	inline vec2 operator/(const vec2& vOther) {
		if (!vOther._x || !vOther._y)
		{
			return infinity_vec();
		}
		return vec2(this->_x / vOther._x, this->_y / vOther._y);
	}
	inline vec2 operator+(float value) {
		return vec2(this->_x + value, this->_y + value);
	}
	inline vec2 operator-(float value) {
		return vec2(this->_x - value, this->_y - value);
	}
	inline vec2 operator*(float value) {
		return vec2(this->_x * value, this->_y * value);
	}
	inline vec2 operator/(float value) {
		if (value == 0.0f) {
			return  infinity_vec();
		}
		return vec2(this->_x / value, this->_y / value);
	}
	inline static vec2 infinity_vec() {
		return vec2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	}
	inline float& operator[](size_t idx) {
		return *(float*)((uintptr_t)(this) + idx * sizeof size_t);
	}
	inline bool equals(const vec2& vOther) {
		return this->_x == vOther._x && this->_y == vOther._y;
	}
	inline bool valid() {
		return this->_x == std::numeric_limits<float>::infinity() || this->_y == std::numeric_limits<float>::infinity();
	}
private:
	float _x;
	float _y;
};

