
#include <iostream>
#include <limits>

struct A
{
public:
	const float x;

	A(float v) : x{ v } {}
	A(const A& src) : x{ src.x } {}
};

int main()
{
	A a{ 1 }, b{ 2 }, c = { 3 };

	A d = b;

	if (true)
	{
		int g;
	}
	else
	{
		int f;
	}

	void* p = nullptr;
}
