#pragma once

#include "Types.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>

/**
 * Three dimensional vector.
 * T has to be compatible with double (casting available both ways).
 */
template <class T>
class Vector3
{
public:
	/// Zero-argument ctor.
	Vector3() : _x(0.0), _y(0.0), _z(0.0) {}
	/// Ctor from 3 values.
	Vector3(T x, T y, T z) : _x(x), _y(y), _z(z) {}
	/// Ctor from 3 values array.
	explicit Vector3(T cells[3]) { std::copy(cells, cells + 3, this->_cells); }

	/// Access x vector component.
	T& x() { return _x; }
	/// Return x vector component.
	T x() const { return _x; }
	/// Access y vector component.
	T& y() { return _y; }
	/// Return y vector component.
	T y() const { return _y; }
	/// Access z vector component.
	T& z() { return _z; }
	/// Return z vector component.
	T z() const { return _z; }

	/// Access vector as 3d array.
	T& operator [](const int i) { assert(i < 3 && i >= 0); return _cells[i]; }
	/// Return vector components via array indices.
	T operator [](const int i) const { assert(i < 3 && i >= 0); return _cells[i]; }

	bool operator ==(const Vector3& v) const { return x() == v.x() && y() == v.y() && z() == v.z(); }
	bool operator !=(const Vector3& v) const { return !(*this == v); }

	Vector3& operator +=(const Vector3& rhs) {
		x() += rhs.x(); y() += rhs.y(); z() += rhs.z();
		return *this;
	}
	Vector3& operator -=(const Vector3& rhs) {
		x() -= rhs.x(); y() -= rhs.y(); z() -= rhs.z();
		return *this;
	}
	Vector3& operator *=(const Vector3& rhs) {
		x() *= rhs.x(); y() *= rhs.y(); z() *= rhs.z();
		return *this;
	}
	Vector3& operator *=(const T rhs) {
		x() *= rhs; y() *= rhs; z() *= rhs;
		return *this;
	}
	Vector3 operator -() const { return Vector3(-x(), -y(), -z()); }
	friend Vector3 operator +(Vector3 lhs, const Vector3& rhs) { lhs += rhs; return lhs; }
	friend Vector3 operator -(Vector3 lhs, const Vector3& rhs) { lhs -= rhs; return lhs; }
	friend Vector3 operator *(Vector3 lhs, const Vector3& rhs) { lhs *= rhs; return lhs; }
	friend Vector3 operator *(Vector3 lhs, const T rhs) { lhs *= rhs; return lhs; }
	friend Vector3 operator *(const T lhs, Vector3 rhs) { rhs *= lhs; return rhs; }

	/**
	 * Returns length of vector.
	 * @warning This method uses {@link sqrt}, therefore it has high CPU cost. 
	 * If you don't need exact length value use {@link lengthSquared} instead.
	 */
	T length() const { return sqrt( x() * x() + y() * y() + z() * z() ); }
	/**
	 * Returns squared length of vector.
	 * @remarks This method is for efficiency, because {@link length} uses {@link sqrt}.
	 * Use it when you need to i.e. find min, max length.
	 */
	T lengthSquared() const { return x() * x() + y() * y() + z() * z(); }
	/**
	 * Returns distance to another vector.
	 * @warning This method uses {@link sqrt}, therefore it has high CPU cost. 
	 * If you don't need exact distance value use {@link distanceSquared} instead.
	 */
	T distance(const Vector3& v) const { return (*this - v).length(); }
	/**
	 * Returns squared distance to another vector.
	 * @remarks This method is for efficiency, because {@link distance} uses {@link sqrt}.
	 * Use it when you need to i.e. find min, max length.
	 */
	T distanceSquared(const Vector3& v) const { return (*this - v).lengthSquared(); }

	/// Normalizes vector so it has length 1.
	void normalize() {
		T l = T(1.0) / (length() ? length() : T(1.0));
		x() *= l; y() *= l; z() *= l; 
	}
	/// Returns normalized copy of this vector.
	Vector3 normalizedCopy() const { Vector3 tmp = *this; tmp.normalize(); return tmp; }

	/// Returns dot product with another vector.
	T dot(const Vector3& v) const { return x() * v.x() + y() * v.y() + z() * v.z(); }
	/// Returns cross product with another vector.
	Vector3 cross(const Vector3& v) const { 
		return Vector3(y() * v.z() - v.y() * z(), 
				z() * v.x() - v.z() * x(),
				x() * v.y() - v.x() * y()
			); 
	}
private:
	union
	{
		struct { T _x, _y, _z; };
		struct { T _cells[3]; };
	};
};

template<class T>
std::ostream& operator<<(std::ostream& out, const Vector3<T>& v) {
	out.precision(10);
	out << "Vector3(" << v.x() << " " << v.y() << " " << v.z() << ")";
	return out;
}

template<>
bool Vector3<float>::operator==(const Vector3& v) const { 
	return Float(x()).almostEqual(Float(v.x())) &&
		Float(y()).almostEqual(Float(v.y())) &&
		Float(z()).almostEqual(Float(v.z()));
}

template<>
bool Vector3<double>::operator==(const Vector3& v) const { 
	return Double(x()).almostEqual(Double(v.x())) &&
		Double(y()).almostEqual(Double(v.y())) &&
		Double(z()).almostEqual(Double(v.z()));
}

/// Three dimensional vector with float values.
typedef Vector3<float> Vector3f;
/// Three dimensional vector with double values.
typedef Vector3<double> Vector3d;
/// Three dimensional vector with int values.
typedef Vector3<int> Vector3i;
