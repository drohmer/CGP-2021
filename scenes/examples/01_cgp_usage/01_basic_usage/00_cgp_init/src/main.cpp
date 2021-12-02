#include "cgp/cgp.hpp"
#include <iostream>


using namespace cgp;

int main(int, char* argv[])
{
	vec3 a = { 1,2,3 };
	vec3 b = { 4,5,6 };
	std::cout << a + b << std::endl;

	return 0;
}

