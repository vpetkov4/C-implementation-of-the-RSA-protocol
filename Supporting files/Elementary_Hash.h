#pragma once
#ifndef GUARD_Elementary_Hash
#define GUARD_Elementary_Hash



#include "stdafx.h"

#include<vector>
#include<tuple>
#include<string>

int Hash_letter(char a);
std::vector<long int> Hash_text_as_vector(std::string text);

char Hash_to_letter(int x);

std::string Hash_text_as_sequence (std::string text);
//std::string Hash_text_as_letter_cryptext (std::string text);
#endif // !1
