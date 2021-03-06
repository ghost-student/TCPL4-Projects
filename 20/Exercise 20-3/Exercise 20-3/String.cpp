#include "String.h"

char* expand(const char* ptr, int n)
{
	char* p = new char[n];
	strcpy(p, ptr);
	return p;
}

void String::copy_from(const String& x)
{
	if (x.sz <= short_max) {
		memcpy(this, &x, sizeof(x));
		ptr = ch;
	}
	else {
		ptr = expand(x.ptr, x.sz + 1);
		sz = x.sz;
		space = 0;
	}
}

void String::move_from(String& x)
{
	if (x.sz <= short_max) {
		memcpy(this, &x, sizeof(x));
		ptr = ch;
	}
	else {
		ptr = x.ptr;
		sz = x.sz;
		space = x.space;
		x.ptr = x.ch;
		x.sz = 0;
		x.ch[0] = 0;
	}
}

String::String()
	: sz{ 0 }, ptr{ ch }
{
	ch[0] = 0;
}

String::String(const char* p)
	: sz{ static_cast<int>(strlen(p)) },
	ptr{ (sz <= short_max) ? ch : new char[sz + 1] },
	space{ 0 }
{
	strcpy(ptr, p);
}

String::String(const String& x)
{
	copy_from(x);
}

String& String::operator=(const String& x)
{
	if (this == &x) 
		return *this;
	char* p = (short_max < sz) ? ptr : nullptr;
	copy_from(x);
	delete[] p;
	return *this;
}

String::String(String&& x)
{
	move_from(x);
}

String& String::operator=(String&& x)
{
	if (this == &x) 
		return *this;
	if (short_max < sz) 
		delete[] ptr;
	move_from(x);
	return *this;
}

String::SubString String::operator()(int begin, int end)
{
	if (begin < 0 || begin > end || end > sz)
		throw runtime_error("bad index");
	return SubString{ *this, begin, end };
}

String& String::operator+=(char c)
{
	if (sz == short_max) {
		int n = sz + sz + 2;
		ptr = expand(ptr, n);
		space = n - sz - 2;
	}
	else if (short_max < sz) {
		if (space == 0) {
			int n = sz + sz + 2;
			char* p = expand(ptr, n);
			delete[] ptr;
			ptr = p;
			space = n - sz - 2;
		}
		else
			--space;
	}
	ptr[sz] = c;
	ptr[++sz] = 0;

	return *this;
}

ostream& operator<<(ostream& os, const String& s)
{
	return os << s.c_str();
}

istream& operator>>(istream& is, String& s)
{
	s = "";
	is >> ws;
	char ch = ' ';
	while (is.get(ch) && !isspace(ch))
		s += ch;
	return is;
}

bool operator==(const String& a, const String& b)
{
	if (a.size() != b.size())
		return false;
	for (int i = 0; i != a.size(); ++i)
		if (a[i] != b[i])
			return false;
	return true;
}

bool operator!=(const String& a, const String& b)
{
	return !(a == b);
}

char* begin(String& x)
{
	return const_cast<char*>(x.c_str());
}

char* end(String& x)
{
	return const_cast<char*>(x.c_str() + x.size());
}

const char* begin(const String& x)
{
	return x.c_str();
}

const char* end(const String& x)
{
	return x.c_str() + x.size();
}

String& operator+=(String& a, const String& b)
{
	for (auto x : b)
		a += x;
	return a;
}

String operator+(const String& a, const String& b)
{
	String res{ a };
	res += b;
	return res;
}

String operator"" _s(const char* p, size_t)
{
	return String{ p };
}

void String::SubString::operator=(const String& x)
{
	if (x.size() <= sz)
		for (int i = 0; i < x.size(); i++)
			ptr[i] = x[i];
	else
		for (int i = 0; i < sz; i++)
			ptr[i] = x[i];
}

String::SubString::operator String()
{
	String res = "";
	for (int i = 0; i < sz; i++)
		res += ptr[i];
	return res;
}