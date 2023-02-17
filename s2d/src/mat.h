#pragma once

#include "defines.h"
#include "vec.h"
#include <cmath>

namespace s2d
{
	template <typename T>
	class Mat3
	{
	public:
		Mat3();

		static Mat3 identity();
		Mat3 inverse() const;
		Mat3 transpose() const;

		static Mat3 translation(T x, T y);
		static Mat3 scaling(T x, T y);
		static Mat3 rotation(T theta);

		T e[3][3];
	};

	template <typename T> Mat3<T>::Mat3() : e{} {}

	template <typename T>
	Mat3<T> Mat3<T>::identity()
	{
		Mat3<T> m;
		m.e[0][0] = T(1);
		m.e[1][1] = T(1);
		m.e[2][2] = T(1);
		return m;
	}

	template <typename T> Mat3<T> Mat3<T>::inverse() const
	{
		const auto ei = e[1][1] * e[2][2];
		const auto fh = e[1][2] * e[2][1];
		const auto di = e[1][0] * e[2][2];
		const auto fg = e[1][2] * e[2][0];
		const auto dh = e[1][0] * e[2][1];
		const auto eg = e[1][1] * e[2][0];
		const auto bi = e[0][1] * e[2][2];
		const auto ch = e[0][2] * e[2][1];
		const auto ai = e[0][0] * e[2][2];
		const auto cg = e[0][2] * e[2][0];
		const auto ah = e[0][0] * e[2][1];
		const auto bg = e[0][1] * e[2][0];
		const auto bf = e[0][1] * e[1][2];
		const auto ce = e[0][2] * e[1][1];
		const auto af = e[0][0] * e[1][2];
		const auto cd = e[0][2] * e[1][0];
		const auto ae = e[0][0] * e[1][1];
		const auto bd = e[0][1] * e[1][0];

		auto determinant = e[0][0] * ei + e[0][1] * fg + e[0][2] * eg - e[0][1] * di - e[0][0] * fh;

		if (determinant == 0)
		{
			// ERROR
		}

		Mat3 result;

		const auto invDet = 1 / determinant;

		result.e[0][0] = (ei - fh) * invDet;
		result.e[1][0] = -(di - fg) * invDet;
		result.e[2][0] = (dh - eg) * invDet;

		result.e[0][1] = -(bi - ch) * invDet;
		result.e[1][1] = (ai - cg) * invDet;
		result.e[2][1] = -(ah - bg) * invDet;

		result.e[0][2] = (bf - ce) * invDet;
		result.e[1][2] = -(af - cd) * invDet;
		result.e[2][2] = (ae - bd) * invDet;

		return result;
	}

	template <typename T>
	Mat3<T> Mat3<T>::transpose() const
	{
		Mat3<T> m;

		// TODO

		return m;
	}

	template <typename T>
	Mat3<T> Mat3<T>::translation(T x, T y)
	{
		Mat3<T> m = Mat3<T>::identity();
		m.e[0][2] = x;
		m.e[1][2] = y;
		m.e[2][2] = T(1);
		return m;
	}

	template <typename T>
	Mat3<T> Mat3<T>::scaling(T x, T y)
	{
		Mat3<T> m;
		m.e[0][0] = x;
		m.e[1][1] = y;
		m.e[2][2] = T(1);
		return m;
	}

	template <typename T>
	Mat3<T> Mat3<T>::rotation(T theta)
	{
		Mat3<T> m;
		m.e[0][0] = std::cos(theta);
		m.e[0][1] = -std::sin(theta);
		m.e[1][0] = std::sin(theta);
		m.e[1][1] = std::cos(theta);
		m.e[2][2] = T(1);
		return m;
	}

	template <typename T>
	Vec3<T> operator*(const Mat3<T>& lhs, const Vec3<T>& rhs)
	{
		Vec3<T> result;

		result.x = lhs.e[0][0] * rhs.x + lhs.e[0][1] * rhs.y + lhs.e[0][2] * rhs.z;
		result.y = lhs.e[1][0] * rhs.x + lhs.e[1][1] * rhs.y + lhs.e[1][2] * rhs.z;
		result.z = lhs.e[2][0] * rhs.x + lhs.e[2][1] * rhs.y + lhs.e[2][2] * rhs.z;

		return result;
	}

	template <typename T>
	Mat3<T> operator*(const Mat3<T>& lhs, const Mat3<T>& rhs)
	{
		Mat3<T> result;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				T sum = T(0);
				for (int k = 0; k < 3; k++)
				{
					sum += lhs.e[i][k] * rhs.e[k][j];
				}
				result.e[i][j] = sum;
			}
		}

		return result;
	}

	using Mat3f = Mat3<f32>;
}