#include "sn_swapper.h"



void SnSwapper::Swap(int & a, int & b)
{
	a = a^b;
	b = a^b;
	a = a^b;
}

SnSwapper::SnSwapper()
{
}


SnSwapper::~SnSwapper()
{
}
