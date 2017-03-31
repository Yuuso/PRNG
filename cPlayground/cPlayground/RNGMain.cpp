
#include "RNG.h"

#include <stdint.h>
#include <iostream>


int main()
{
	PRNG<uint32_t> random;
	
	for (size_t i = 0; i < 100; i++)
	{
		std::cout << random.random<float, Distribution::Exponential<float>>() << std::endl;
	}

	std::cin.ignore();
	return 0;
}