

#include "stdafx.h"
#include "Elementary_Hash.h"

#include<vector>
#include<tuple>
#include<string>
#include<cmath>
#include<fstream>
#include<cstdlib>

//Hash single letter 'A'->2, 'B'->3,....
int Hash_letter(char a)
{
	char temp_char='a', Temp_char='A';

	for (int i = 0; i < 26; i++)
	{
		if (a == temp_char || a == Temp_char)
		{
			return i + 2;
		}
		temp_char++; Temp_char++;
	}

};

char Hash_to_letter(int x)
{
	char a = 'A';
	

	for(int i = 2;i<28;i++)
	{
		if (i == x) return a;
		a = a + 1;
	}
};




//Hash a word as a vector
std::vector<long int> Hash_text_as_vector(std::string text)
{
	int x;
	std::vector<long int> v;

	for (int i = 0; i < text.size(); i++)
	{
		x = Hash_letter(text[i]);
		v.push_back(x);
	}

	return v;

};


//Hash word as a sequense of numbers
std::string Hash_text_as_sequence(std::string text)
{
	std::vector<long int> v;
	std::string s;

	v = Hash_text_as_vector(text);

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] < 10) {
			s = s + '0';
			s = s+std::to_string(v[i]);
		}
		else s = s + std::to_string(v[i]);
	}

	return s;

};