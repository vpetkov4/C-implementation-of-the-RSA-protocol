// Encryption algorithms.cpp : Defines the entry point for the console application.
//




#include "stdafx.h"

#include "RSA_cryptosystem.h"
#include "Extended_Euclidean_Algorithm.h"
#include "Elementary_Hash.h"
#include "Fast_Power.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include "math.h"
#include <string>
#include <fstream>
#include <tuple>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;







int main()
{

	//Download list of primes.
	vector<int> list_primes;
	
	//file reading operator
	ifstream bucky;

	//file writing opperator
	ofstream ducky;

	bucky.open("list_of_primes.txt");
	if (!bucky.is_open()) {
		exit(EXIT_FAILURE);
	}
	int prime_number;
	bucky >> prime_number;
	while (bucky.good())
	{
		list_primes.push_back(prime_number);
		bucky >> prime_number;
	}

	bucky.close();

	//Define the RSA key
	RSA_cryptosystem_key key;

	//Deafault key: p=29, q=31,  trivial e=d=1
	{key.prime_p = 29; key.prime_q = 31;
	key.modulus_n = key.prime_p*key.prime_q;
	key.Phi_n = (key.prime_p - 1)*(key.prime_q - 1);
	key.public_key_e = 1; key.private_key_d = 1;
	}

	//Ask what would you like to do for the first time
	{cout << "What would you like to do: \n"
		<< "1: Generate an RSA cypher\n"
		<< "2: Break an RSA cypher\n"
		<< "3: Encrypt using the generated/cracked cypher\n"
		<< "4: Decrypt a message from a file\n"
		<< "5: Print saved RSA public key\n"
		<< "6: Print full RSA key\n"
		<< "0: Exit\n";
	}

	int choice;
		cin >> choice;

	while(choice!=0)	
	{
		switch (choice)
		{			//Generate RSA key
		case 1: {generate_RSA_key(cin, key); break; }
					
					//Break RSA cryptosystem
			case 2: {

					cout << "Write modulus: ";
					long int modulus;
					cin >> modulus;

					cout << "Write public key: ";
					long int public_key;
					cin >> public_key;

					RSA_cryptosystem_key broken_key;
					broken_key = Breaking_code(modulus, public_key, list_primes);
					cout << "The first prime is: p=" << broken_key.prime_p 
						 << ". The second prime is: q="
						 << broken_key.prime_q << ".\n";
					cout << "The modulus is: " << broken_key.modulus_n << endl;
					cout << "The public key is: " << broken_key.public_key_e << endl;
					
					cout << "The private key is: " << broken_key.private_key_d << endl;

					cout << "Phi(n) is:  " << broken_key.Phi_n << endl;
					cout << "The gcd is: " << GCD(broken_key.public_key_e, broken_key.Phi_n) << endl;

					key = broken_key; 
					break; }

					//Encrypt with RSA saved key
			case 3: { 
				
				//Encrypt using RSA key
					vector<long int> v_plain, v_crypt;
					string text;
					cout << "Write plain text without spaces: ";
					cin >> text;
					v_plain = Hash_text_as_vector(text);

					v_crypt = RSA_encrypt_vector(text, key.modulus_n, key.public_key_e);

					for (int i = 0; i < v_plain.size(); i++)
						{
							cout << v_plain[i] << " ";
							}
					cout << endl;

					for (int i = 0; i < v_crypt.size(); i++)
					{
						cout << v_crypt[i] << " ";
					}
					cout << endl;

					cout << RSA_decrypt(v_crypt, key.modulus_n, key.private_key_d) << endl; 
		
					string choice2;
					cout << "Would you like to export the cryptext to a .txt file? Yes/No\n";
						cin >> choice2;
					if (choice2 == "Yes" || choice2 == "YES" || choice2 == "yes")
					{
						string filename;
						cout << "What would you like to name the file?\n";
						cin >> filename;

						ofstream myfile(filename.c_str());

						//myfile << "This file contains an encrypted message using the RSA generated public key ( " << key.modulus_n << " , " << key.public_key_e << " )\n\n";

						myfile << key.modulus_n << " " << key.public_key_e << "\n";
						for (int i = 0; i < v_crypt.size(); i++)
						{
							myfile << v_crypt[i] << " ";
						}
						myfile << endl;
						myfile.close();




						}


					break;
				}
			
					//Decrypt message 
			case 4: { vector<long int> v_plain, v_crypt;
					  string text;
				
					  string filename;
				      cout << "What file would you like me to open? \n";
					  cin>> filename;
                      bucky.open(filename);
					  if (!bucky.is_open()) { cout << "This file does not exist\n"; break; }

					  long int number_block;
					  //Read the public key
					  {bucky >> number_block;
					  key.modulus_n = number_block;
					  bucky >> number_block;
					  key.public_key_e = number_block; }

					  //Break the key
					  key = Breaking_code(key.modulus_n, key.public_key_e, list_primes);

					  //Read cryptext
					  {bucky >> number_block;
					  while (bucky.good())
							{
								v_crypt.push_back(number_block);
								bucky >> number_block;
							}
					  v_crypt.push_back(number_block);

					  }

					  //Print the cryptext vector
					  {for (int i = 0; i < v_crypt.size(); i++)
					  {  cout << v_crypt[i]<< " ";
							}
					  cout << endl;

					  }

					  //Decrypt cryptext and print plaintext
					  cout << RSA_decrypt(v_crypt, key.modulus_n, key.private_key_d) << endl;
					  
					  bucky.close();
					  break;
					}
					//Print RSA public key
			case 5: {cout << "Public key: (n,e)=( " << key.modulus_n << " , " 
						  << key.public_key_e << " )\n"; 
					
					 break;	
					}
			       
					//Print full key
			case 6: {cout << "Public key: (n,e)=( " << key.modulus_n << " , "
						  << key.public_key_e << " )\n"; 
					 cout << "First prime: " << key.prime_p 
						  << " Second prime: " << key.prime_q << endl;
					 cout << "Private key: " << key.private_key_d << endl;
					
					 break;
					}

			default:
					break;
		}

		//Ask what you want to do again 
	  {cout << "\n" << "What would you like to do: \n"
			<< "1: Generate a new RSA cypher\n"
			<< "2: Break a new RSA cypher\n"
			<< "3: Encrypt using the generated/cracked cypher\n"
			<< "4: Decrypt a message from a file\n"
			<< "5: Print saved RSA public key\n"
			<< "6: Print full RSA key\n"
			<< "0: Exit\n";
		}


		 cin >> choice;
   }
	
	
/*
   int d, a,b,p,r;
   cout << "d=";
   cin >> d;

   while (d==1)
   {
	   cin >> p >> r >> a >> b;

	   cout << "r^a mod p= " << Fast_Power(r, a, p) << endl;
	   cout << "r^b mod p= " << Fast_Power(r, b, p) << endl;
	   cout << "r^ab mod p= " << Fast_Power(r, a*b, p) << endl;

	   cout << "d=";
	   cin >> d;
   }


   */

	//test RSA
	
	
	
/*Testing the key
	cout << "The modulus is: " << key.modulus_n << endl;
	cout << "Phi(n) is:  " << key.Phi_n << endl;
	cout << "The public key is: " << key.public_key_e << endl;
	cout << "The gcd is: " << GCD(key.public_key_e, key.Phi_n) << endl;
	cout << "The private key is: " << key.private_key_d << endl;

*/
	//Testing the elementary hash
	/*char a = 'B', b = 'k';

	cout << Hash_letter(a) << " " << Hash_letter(b) << endl;

	cout << Hash_to_letter(11) << " " << Hash_to_letter(15) << endl;

	cout << Hash_text_as_sequence("Hello") << endl;*/


	
	
	//cout << int(pow(2, 11))%(29*31);



	//Choosing other cypher wip.
	/*int cypher_type;
	cout << "Which cypher do you want to use?\n";
	cin >> cypher_type;
	switch (cypher_type)
	{ case 1:                                 

	default:
		break;
	}
	*/


    return system("pause");
}

