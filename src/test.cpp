#include <cstdlib>
#include <iostream>

#include "CompileTimePhysicalValueTypeChecker.hpp"

int main()
{
	std::cout << 2_m / 2_s << std::endl;

	return EXIT_SUCCESS;
}
