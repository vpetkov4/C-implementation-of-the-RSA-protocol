#pragma once
#ifndef GUARD_RSA_cryptosystem_h
#define GUARD_RSA_cryptosystem_h



#include<iostream>
#include<vector>
#include<string>
#include <iomanip>
#include<tuple>
#include<math.h>
#include<cmath>
#include<fstream>
#include<cstdlib>

#include "stdafx.h"
#include "Extended_Euclidean_Algorithm.h"
#include "Fast_Power.h"


struct RSA_cryptosystem_key
{
	long int prime_p, prime_q;
	long int modulus_n;
	long int Phi_n;
	long int public_key_e;
	long int private_key_d;

};

std::istream&  generate_RSA_key(std::istream& in, RSA_cryptosystem_key& RSA_key);

//encrypt a letter (Plaintext ,  modulus, encyption key)
long int RSA_encrypt_block(long int plain, long int n, long int e);

//encrypt text as a vector of numbers
std::vector<long int> RSA_encrypt_vector(std::string text, long int modulus, long int public_key);



//string RSA_encrypt_sequence(std::string text, long int modulus, long int public_key);
//string RSA_encrypt_text(std::string text, long int modulus, long int public_key);



//Decrypt using RSA
std::string RSA_decrypt(std::vector<long int> v, long int modulus, long int private_key);

//Breaing the code by factoring n<10000

RSA_cryptosystem_key Breaking_code(long int modulus, long int public_key, std::vector<int> primes);




#endif // !GUARD_RSA_cryptosystem_h
