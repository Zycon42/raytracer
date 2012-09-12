// This header file is based on code from Google gtest.
//
// **********************************************************************
// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Authors: wan@google.com (Zhanyong Wan), eefacm@gmail.com (Sean Mcafee)
//
// The Google C++ Testing Framework (Google Test)
// ***********************************************************************

#pragma once

#ifndef PRECOMPILED_HEADERS_INCLUDED
#include <cstdint>
#include <limits>
#endif // !PRECOMPILED_HEADERS_INCLUDED


/**
 * This template is used as compile time chooser
 * for primitive types according to specified size.
 */
template <size_t Size>
struct TypeWithSize {
	/// typedef to void will prevent using this with non-specialized template.
	typedef void UInt;
	typedef void Int;
};

template<>
struct TypeWithSize<2>
{
	typedef int16_t Int;
	typedef uint16_t UInt;
};

template<>
struct TypeWithSize<4>
{
	typedef int32_t Int;
	typedef uint32_t UInt;
};

template<>
struct TypeWithSize<8>
{
	typedef int64_t Int;
	typedef uint64_t UInt;
};

template <typename T>
class FloatingPoint
{
public:
	/// Integer type with same size as T.
	typedef typename TypeWithSize<sizeof T>::UInt Bits;

	explicit FloatingPoint(const T& value) : _value(value) { }

	const Bits& bits() const { return _bits; }
	const T& value() const { return _value; }

	Bits signBit() const { return SIGN_MASK & _bits; }
	Bits mantisaBits() const { return MANT_MASK & _bits; }
	Bits exponentBits() const { return EXP_MASK & _bits; }

	/// Checks if is this is nan.
	bool isNan() const {
		// NaN is when all exponent bits are ones and mantisa is not zero.
		return exponentBits() == EXP_MASK && mantisaBits() != 0;
	}

	/**
	 * Test if rhs is almost equal to this.
	 * @param rhs second floating point number
	 * @param maxUlps how many ULPs we want to tolerate.
	 * @return true when almost equal, false otherwise.
	 * @see http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
	 */
	bool almostEqual(const FloatingPoint& rhs, size_t maxUlps = 4) {
		if (isNan() || rhs.isNan())
			return false;

		return distanceBetweenSignAndMagnitudeNumbers(bits(), rhs.bits()) <= maxUlps;
	}
private:
	/// Number of bits in number.
	static const size_t BIT_COUNT = sizeof(T) * CHAR_BIT;
	/// Number of bits in mantisa part.
	static const size_t MANT_BIT_COUNT = std::numeric_limits<T>::digits - 1;
	/// Number of bits in exponent part.
	static const size_t EXP_BIT_COUNT = BIT_COUNT - 1 - MANT_BIT_COUNT;
	/// Mask for sign bit.
	static const Bits SIGN_MASK = static_cast<Bits>(1) << (BIT_COUNT - 1);
	/// Mask for mantisa part.
	static const Bits MANT_MASK = static_cast<Bits>(0) >> (EXP_BIT_COUNT + 1);
	/// Mask for exponent part.
	static const Bits EXP_MASK = ~(SIGN_MASK | MANT_MASK);

	/**
	 * Converts an integer from the sign-and-magnitude representation to
	 * the biased representation.  More precisely, let N be 2 to the
	 * power of (kBitCount - 1), an integer x is represented by the
	 * unsigned number x + N.
	 *
	 * For instance,
	 *
	 *   -N + 1 (the most negative number representable using
	 *          sign-and-magnitude) is represented by 1;
	 *   0      is represented by N; and
	 *   N - 1  (the biggest number representable using
	 *          sign-and-magnitude) is represented by 2N - 1.
	 *
	 * @see http://en.wikipedia.org/wiki/Signed_number_representations
	 */
	static Bits signAndMagnitudeToBiased(const Bits& sam) {
		if (SIGN_MASK & sam)
			// sam represents negative number
			return ~sam + 1;
		else
			// sam represents positive number
			return SIGN_MASK | sam;
	}

	/**
	 * Get distance between two numbers in sign and magnitude representation.
	 * @param sam1 first number
	 * @param sam2 second number
	 * @return distance as unsigned integer
	 */
	static Bits distanceBetweenSignAndMagnitudeNumbers(const Bits& sam1, const Bits& sam2) {
		Bits biased1 = signAndMagnitudeToBiased(sam1);
		Bits biased2 = signAndMagnitudeToBiased(sam2);
		return (biased1 >= biased2) ? (biased1 - biased2) : (biased2 - biased1);
	}

	union
	{
		T _value;
		Bits _bits;
	};
};

typedef FloatingPoint<float> Float;
typedef FloatingPoint<double> Double;
