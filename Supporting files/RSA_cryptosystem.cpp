#pragma once

#include "stdafx.h"
#include "RSA_cryptosystem.h"
#include "Extended_Euclidean_Algorithm.h"
#include "Elementary_Hash.h"
#include "Fast_Power.h"

#include<iostream>
#include<vector>
#include<string>
#include <iomanip>
#include<tuple>
#include<math.h>
#include<cmath>
#include<fstream>
#include<cstdlib>

//generate RSA keys
std::istream&  generate_RSA_key(std::istream& in, RSA_cryptosystem_key& RSA_key)
{ 
	// read the primes
	std::cout << "First prime: ";

	in >> RSA_key.prime_p;

	std::cout << "Second prime: ";

	in >> RSA_key.prime_q;

	//Compute n and Phi(n);
	RSA_key.modulus_n = RSA_key.prime_p*RSA_key.prime_q;
	RSA_key.Phi_n = (RSA_key.prime_p - 1)*(RSA_key.prime_q - 1);



	//read the public key




	do {
		std::cout << "Public key e: ";

		in >> RSA_key.public_key_e;
	} while (GCD(RSA_key.public_key_e, RSA_key.Phi_n) > 1);



	

	//compute the private key
	std::tuple<long int, long int, long int> t = Extended_GCD(RSA_key.public_key_e, RSA_key.Phi_n);


	//record the private key
	RSA_key.private_key_d = std::get<1>(t);
	while (RSA_key.private_key_d < 0)
	{
		RSA_key.private_key_d = RSA_key.private_key_d + RSA_key.Phi_n;
	}
	while (RSA_key.private_key_d > RSA_key.Phi_n)
	{
		RSA_key.private_key_d = RSA_key.private_key_d - RSA_key.Phi_n;
	}

	return in;
};


//encrypt a letter (Plaintext , modulus , encryption key)
long int RSA_encrypt_block(long int plain, long int n, long int e )
{
	long int x;

	x = Fast_Power(plain, e, n);

	return x;

};

//encrypt text as a vector of numbers
std::vector<long int> RSA_encrypt_vector(std::string text, long int modulus, long int public_key)
{
	long int x;
	std::vector<long int> v_plain, v_crypt;
	v_plain = Hash_text_as_vector(text);

	for (int i = 0; i < v_plain.size(); i++)
	{
		x = v_plain[i];
		x = RSA_encrypt_block(x, modulus, public_key);
		v_crypt.push_back(x);

	}
	return v_crypt;
};

//string RSA_encrypt_sequence(std::string text, long int modulus, long int public_key);
//string RSA_encrypt_text(std::string text, long int modulus, long int public_key);

//Decrypt using RSA
std::string RSA_decrypt(std::vector<long int> v, long int modulus, long int private_key)
{
	//plaintext
	std::string s;
	long int x;

	for (int i = 0; i < v.size(); i++)
	{
		//quick exponentiation to be added
		x = Fast_Power(v[i],private_key,modulus);

		s = s + Hash_to_letter(x);
	}

	return s;



};


//Breaking the key for n<10000
RSA_cryptosystem_key Breaking_code(long int modulus, long int public_key, std::vector<int> primes)
{
	long int prime_p, prime_q;

	RSA_cryptosystem_key RSA_key;

	RSA_key.modulus_n = modulus;
	RSA_key.public_key_e = public_key;

	int j = 0;

	while (j < primes.size() && modulus%primes[j] != 0)
	{
		j++;
	}
	
	RSA_key.prime_p = primes[j];
	RSA_key.prime_q = modulus / primes[j];

	//compute Phi(n)
	RSA_key.Phi_n = (RSA_key.prime_p - 1)*(RSA_key.prime_q - 1);

	// compute the private key.

	std::tuple<long int, long int, long int> t = Extended_GCD(RSA_key.public_key_e, RSA_key.Phi_n);


	//record the private key
	RSA_key.private_key_d = std::get<1>(t);
	while (RSA_key.private_key_d < 0)
	{
		RSA_key.private_key_d = RSA_key.private_key_d + RSA_key.Phi_n;
	}
	while (RSA_key.private_key_d > RSA_key.Phi_n)
	{
		RSA_key.private_key_d = RSA_key.private_key_d - RSA_key.Phi_n;
	}

	return RSA_key;
};



