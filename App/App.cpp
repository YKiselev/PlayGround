
#include <iostream>
#include <limits>

class A
{
private:
	int v;

	A() {}

public:
	A(int v) : v{ v } {}
};

int main()
{
	A a{ 1 }, b{ 2 }, c = {3};

	a = b;

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
