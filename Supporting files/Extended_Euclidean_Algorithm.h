#pragma once

#ifndef GUARD_Extended_Euclidean_Algorithm
#define GUARD_Extended_Euclidean_Algorithm

#include "stdafx.h"

#include<vector>
#include<tuple>

long int GCD(long int a, long int b);
std::tuple<long int, long int, long int> Extended_GCD(long int a, long int b);



#endif // !Extended_Euclidean_Algorithm.h
