/*
 * TemplateTest.cpp
 *
 *  Created on: Sep 20, 2013
 *      Author: harish
 */
#include <iostream>

template <unsigned long N>
struct binary
{
	static unsigned const value = binary<N/10>::value << 1 | N%10;
};

template <>
struct binary<0>
{
	static unsigned const value = 0;
};

int main() {
	std::cout << binary<1010101011110000101>::value << std::endl;
}



