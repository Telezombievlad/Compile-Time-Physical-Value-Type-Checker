#ifndef COMPILE_TIME_PHYS_VAL_CHECKER_HPP_INCLUDED
#define COMPILE_TIME_PHYS_VAL_CHECKER_HPP_INCLUDED

// Includes:

#include <ostream>
#include <iostream>

// Defines:

#define PHYS_VAL_TYPE(index) int s##index, int m##index, int kg##index, int A##index, int K##index, int mol##index, int cd##index

#define PHYS_VAL(index) PhysVal<Data_t, s##index, m##index, kg##index, A##index, K##index, mol##index, cd##index>

#define PHYS_VAL_TYPES_ARE_EQUAL(index0, index1) \
(  s##index0 ==   s##index1) && \
(  m##index0 ==   m##index1) && \
( kg##index0 ==  kg##index1) && \
(  A##index0 ==   A##index1) && \
(  K##index0 ==   K##index1) && \
(mol##index0 == mol##index1) && \
( cd##index0 ==  cd##index1)

#define NEW_PHYS_VAL(operation, index0, index1) \
PhysVal                                  \
<                                        \
    Data_t,                              \
    (  s##index0 operation   s##index1), \
    (  m##index0 operation   m##index1), \
    ( kg##index0 operation  kg##index1), \
    (  A##index0 operation   A##index1), \
    (  K##index0 operation   K##index1), \
    (mol##index0 operation mol##index1), \
    ( cd##index0 operation  cd##index1)  \
>

// Value with it's physical type:

template
<
	class Data_t, // Some integral type, hopefully
	PHYS_VAL_TYPE(0)
>
class PhysVal
{
	public:
		// Ctors:
			PhysVal(Data_t val) : val_ (val) {}
			PhysVal(const PhysVal& ) = default;
			PhysVal(      PhysVal&&) = default;

		// Assignment:
			PhysVal& operator=(const PhysVal& ) = default;
			PhysVal& operator=(      PhysVal&&) = default;

		// Dtor:
			~PhysVal() = default;

		// Conversion operator:
			explicit operator Data_t() const
			{
				return val_;
			}

		// Arithmetics:

			template <PHYS_VAL_TYPE(1)>
			PhysVal& operator+=(const PHYS_VAL(1)& v)
			{
				static_assert(PHYS_VAL_TYPES_ARE_EQUAL(0, 1), "Terms have to be of the same physical type.");

				val_ += v.val_;

				return *this;
			}

			template <PHYS_VAL_TYPE(1)>
			PhysVal& operator-=(const PHYS_VAL(1)& v)
			{
				static_assert(PHYS_VAL_TYPES_ARE_EQUAL(0, 1), "Terms have to be of the same physical type.");

				val_ -= v.val_;

				return *this;
			}

	// Variable:
		Data_t val_;
};

// More PhysVal arithmetics (+, -, *, /):

template
<
	class Data_t,
	PHYS_VAL_TYPE(0),
	PHYS_VAL_TYPE(1)
>
PHYS_VAL(0) operator+(const PHYS_VAL(0)& v0, const PHYS_VAL(1)& v1)
{
	PHYS_VAL(0) toReturn{v0};

	toReturn += v1;

	return toReturn;
}

template
<
	class Data_t,
	PHYS_VAL_TYPE(0),
	PHYS_VAL_TYPE(1)
>
PHYS_VAL(0) operator-(const PHYS_VAL(0)& v0, const PHYS_VAL(1)& v1)
{
	PHYS_VAL(0) toReturn{v0};

	toReturn -= v1;

	return toReturn;
}

template
<
	class Data_t,
	PHYS_VAL_TYPE(0),
	PHYS_VAL_TYPE(1)
>
NEW_PHYS_VAL(+, 0, 1) operator*(const PHYS_VAL(0)& v0, const PHYS_VAL(1)& v1)
{
	auto toReturn = v0.val_ * v1.val_;

	return toReturn;
}

template
<
	class Data_t,
	PHYS_VAL_TYPE(0),
	PHYS_VAL_TYPE(1)
>
NEW_PHYS_VAL(-, 0, 1) operator/(const PHYS_VAL(0)& v0, const PHYS_VAL(1)& v1)
{
	auto toReturn = v0.val_ / v1.val_;

	return toReturn;
}

// Printing:

template <class Data_t, PHYS_VAL_TYPE(0)>
std::ostream& operator<<(std::ostream& os, const PHYS_VAL(0)& val)
{
	os << val.val_;

	if (  s0 != 0) os << "s^"   <<   s0;
	if (  m0 != 0) os << "m^"   <<   m0;
	if ( kg0 != 0) os << "kg^"  <<  kg0;
	if (  A0 != 0) os << "A^"   <<   A0;
	if (  K0 != 0) os << "K^"   <<   K0;
	if (mol0 != 0) os << "mol^" << mol0;
	if ( cd0 != 0) os << "cd^"  <<  cd0;

	return os;
}

// Some user-defined literals:

PhysVal<unsigned long long, 1, 0, 0, 0, 0, 0, 0> operator "" _s(unsigned long long i) { return i; }
PhysVal<       long double, 1, 0, 0, 0, 0, 0, 0> operator "" _s(       long double i) { return i; }

PhysVal<unsigned long long, 0, 1, 0, 0, 0, 0, 0> operator "" _m(unsigned long long i) { return i; }
PhysVal<       long double, 0, 1, 0, 0, 0, 0, 0> operator "" _m(       long double i) { return i; }

PhysVal<unsigned long long, 0, 0, 1, 0, 0, 0, 0> operator "" _kg(unsigned long long i) { return i; }
PhysVal<       long double, 0, 0, 1, 0, 0, 0, 0> operator "" _kg(       long double i) { return i; }

PhysVal<unsigned long long, 0, 0, 0, 1, 0, 0, 0> operator "" _A(unsigned long long i) { return i; }
PhysVal<       long double, 0, 0, 0, 1, 0, 0, 0> operator "" _A(       long double i) { return i; }

PhysVal<unsigned long long, 0, 0, 0, 0, 1, 0, 0> operator "" _K(unsigned long long i) { return i; }
PhysVal<       long double, 0, 0, 0, 0, 1, 0, 0> operator "" _K(       long double i) { return i; }

PhysVal<unsigned long long, 0, 0, 0, 0, 0, 1, 0> operator "" _mol(unsigned long long i) { return i; }
PhysVal<       long double, 0, 0, 0, 0, 0, 1, 0> operator "" _mol(       long double i) { return i; }

PhysVal<unsigned long long, 0, 0, 0, 0, 0, 0, 1> operator "" _cd(unsigned long long i) { return i; }
PhysVal<       long double, 0, 0, 0, 0, 0, 0, 1> operator "" _cd(       long double i) { return i; }


// Undefining everything:

#undef PHYS_VAL_TYPE
#undef PHYS_VAL
#undef PHYS_VAL_TYPES_ARE_EQUAL
#undef NEW_PHYS_VAL

#endif /*COMPILE_TIME_PHYS_VAL_CHECKER_HPP_INCLUDED*/
