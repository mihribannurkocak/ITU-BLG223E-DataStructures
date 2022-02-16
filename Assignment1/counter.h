/*
PLEASE DO NOT REMOVE ANY FUNCTION OR VARIABLE IN THE STRUCT, IF YOU NEED YOU CAN ADD NEW ONES 
*/
/* @Author
Student Name: Mihriban Nur Kocak
Student ID : 150180090
Date: 11/11/2020 */
#ifndef _H
#define _H
#include <stdio.h>

#define ARRAY_SIZE 100

#include "token.h"

struct Counter{
	int token_count=0;
	Token token_array[ARRAY_SIZE];
	void read_and_count();
	bool contains(char *,char);
	int findindex(Token [],char[]);
	Token *get_most_common_three();
	FILE* pi_file; // I ADDED TO HOLD THE FILE
	Token most_common_three[3]; // I ADDED TO HOLD THE MOST COMMON THREE TOKENS
};
#endif
