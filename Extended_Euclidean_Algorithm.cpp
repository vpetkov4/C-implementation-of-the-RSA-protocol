
#include "stdafx.h"
#include "Extended_Euclidean_Algorithm.h"

#include<vector>
#include<tuple>


//Euclidean Algorithm
long int GCD(long int a, long int b)
{
	if (a == 0)
		return b;

	long int gcd; 
	
	gcd= GCD(b%a, a);

	return gcd;

};

//Extended Euclidean algorithm
std::tuple<long int, long int, long int> Extended_GCD(long int a, long int b)
{

	//Base case
	if (a == 0)
		return std::make_tuple(b, 0, 1);

	long int gcd, x, y;

	std::tie(gcd, x, y) = Extended_GCD(b%a, a);

	return std::make_tuple(gcd, (y - (b / a)*x), x);
};