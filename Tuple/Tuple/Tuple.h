#pragma once
#include <iostream>
using namespace std;

template<typename T1 = _Nil, typename T2 = _Nil, typename T3 = _Nil, typename T4 = _Nil>
struct Tuple : Tuple<T2, T3, T4> {
	T1 x;

	using Base = Tuple<T2, T3, T4>;
	Base* base() { return static_cast<Base*>(this); }
	const Base* base() const { return static_cast<const Base*>(this); }

	Tuple(const T1& t1, const T2& t2, const T3& t3, const T4& t4) :Base{ t2,t3,t4 }, x{ t1 } { }
};

template<>
struct Tuple<> { Tuple() {} };

template<typename T1>
struct Tuple<T1> : Tuple<> {
	T1 x;

	using Base = Tuple<>;
	Base *base() { return static_cast<Base*>(this); }
	const Base *base() const { return static_cast<const Base*>(this); }

	Tuple(const T1& t1) :Base{}, x{ t1 } { }
};

template<typename T1, typename T2>
struct Tuple<T1, T2> : Tuple<T2> {
	T1 x;

	using Base = Tuple<T2>;
	Base* base() { return static_cast<Base*>(this); }
	const Base* base() const { return static_cast<const Base*>(this); }

	Tuple(const T1& t1, const T2& t2) :Base{ t2 }, x{ t1 } { }
};

template<typename T1, typename T2, typename T3>
struct Tuple<T1, T2, T3> : Tuple<T2, T3> {
	T1 x;
	using Base = Tuple<T2, T3>;
	Base* base() { return static_cast<Base*>(this); }
	const Base* base() const { return static_cast<const Base* >(this); }

	Tuple(const T1& t1, const T2& t2, const T3& t3) :Base{ t2, t3 }, x{ t1 } { }
};

template<typename T1, typename T2, typename T3, typename T4>
void print_elements(ostream& os, const Tuple<T1, T2, T3, T4>& t)
{
	os << t.x << ", ";
	print_elements(os, *t.base());
}

template<typename T1, typename T2, typename T3>
void print_elements(ostream& os, const Tuple<T1, T2, T3>& t)
{
	os << t.x << ", ";
	print_elements(os, *t.base());
}

template<typename T1, typename T2>
void print_elements(ostream& os, const Tuple<T1, T2>& t)
{
	os << t.x << ", ";
	print_elements(os, *t.base());
}

template<typename T1>
void print_elements(ostream& os, const Tuple<T1>& t)
{
	os << t.x;
}

template<>
void print_elements(ostream& os, const Tuple<>& t)
{
	os << " ";
}

template<typename T1, typename T2, typename T3, typename T4>
ostream& operator<<(ostream& os, const Tuple<T1, T2, T3, T4>& t)
{
	os << "{ ";
	print_elements(os, t);
	os << " }";
	return os;
}