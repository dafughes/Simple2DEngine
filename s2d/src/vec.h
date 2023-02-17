#pragma once

#include "defines.h"

namespace s2d
{

	template <typename T>
	class Vec2
	{
	public:
		Vec2() : Vec2((T)0, (T)0) {}
		Vec2(T x, T y) : x(x), y(y) {}

		Vec2 operator-() const;

		Vec2& operator+=(const Vec2& rhs);
		Vec2& operator-=(const Vec2& rhs);

		T x, y;
	};

	template <typename T>
	class Vec3
	{
	public:
		Vec3() : Vec3((T)0, (T)0, T(0)) {}
		Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
		
		Vec3 operator-() const;
		   
		Vec3& operator+=(const Vec3& rhs);
		Vec3& operator-=(const Vec3& rhs);

		T x, y, z;
	};

	// ----------Vec2----------

	template <typename T> Vec2<T> Vec2<T>::operator-() const { return Vec2<T>(-x, -y); }

	template <typename T> Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	template <typename T> Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	template <typename T> Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <typename T> Vec2<T> operator-(Vec2<T> lhs, const Vec2<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	template <typename T> inline bool operator==(const Vec2<T>& lhs, const Vec2<T>& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
	template <typename T> inline bool operator!=(const Vec2<T>& lhs, const Vec2<T>& rhs) { return !operator==(lhs, rhs); }

	
	// ----------Vec3----------

	template <typename T> Vec3<T> Vec3<T>::operator-() const { return Vec3<T>(-x, -y, -z); }

	template <typename T> Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	template <typename T> Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	template <typename T> Vec3<T> operator+(Vec3<T> lhs, const Vec3<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <typename T> Vec3<T> operator-(Vec3<T> lhs, const Vec3<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	template <typename T> inline bool operator==(const Vec3<T>& lhs, const Vec3<T>& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }
	template <typename T> inline bool operator!=(const Vec3<T>& lhs, const Vec3<T>& rhs) { return !operator==(lhs, rhs); }

	using Vec2f = Vec2<f32>;
	using Vec2u = Vec2<u32>;
	using Vec2i = Vec2<i32>;

	using Vec3f = Vec3<f32>;
	using Vec3u = Vec3<u32>;
	using Vec3i = Vec3<i32>;
}