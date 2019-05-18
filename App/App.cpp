
#include <iostream>
#include <limits>


int main()
{
	std::cout << sizeof(1) << ", " << sizeof(char) << ", " << sizeof(int) << ", " << sizeof(short) << std::endl;

	std::numeric_limits<float> limits;

	std::cout << "max=" << limits.max() << ", min=" << limits.min() << std::endl;

	auto v = 123;

	std::cout << sizeof(v);
}
