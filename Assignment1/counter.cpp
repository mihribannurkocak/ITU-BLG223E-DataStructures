/*
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/
/* @Author
Student Name: Mihriban Nur Kocak
Student ID : 150180090
Date: 11/11/2020 */
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "counter.h"

using namespace std;

	
int Counter::findindex(Token *arr,char elem[]){
	//THIS FUNCTION WILL BE CODED BY YOU
	int index = -1;
	for(int i = 0; i < token_count; i++){
		if(!strcmp(arr[i].token,elem)){ //strcmp returns 0 if both strings are identical
			index = i;
		}
	}
	return index;
} 

bool Counter::contains(char *token, char target){
	//THIS FUNCTION WILL BE CODED BY YOU
	/*
	Contains function is used to eliminate not accepted tokens. Please read carefully explanation of homework, 
	"Note that, tokens have to consist of two digits, and token array have to contain tokens in only the decimal part of pi. 
	For example; ’3.’ is ’.1’ are not accepted forms."
	*/
	bool contain = false; //assume token doesn't contain target
	int i = 0;
	while(token[i] != '\0'){
		if(target == token[i]){
			contain = true;
			break;
		}
		i++;
	}

	return contain;
}

void Counter::read_and_count(){ 
	//THIS FUNCTION WILL BE CODED BY YOU
	const char* filename = "pi_approximate";
	pi_file = fopen(filename, "r");
	
	/*
	//I AM NOT SURE WHETHER DO I NEED TO CHECK THIS PART OR NOT FOR THIS HOMEWORK SO I COMMENTED
	if(!pi_file){
		cerr << "Cannot open file" << endl;   
		exit(1); 
	}*/

	//FIRST TRY TO REACH THE DECIMAL PART
	//Firstly check the starting two digits
	char buffer_token[3]; //Due to the '/0'
	buffer_token[0] = fgetc(pi_file);
	buffer_token[1] = fgetc(pi_file);
	buffer_token[2] = '\0';
	char target = '.'; //Since we are searching for tokens which are entirely from after decimal point
	int contains_dot_count = 0; // There will be 2 tokens which consist of dot so that we are trying to reach this ones and start counting valid tokens after them
	if(contains(buffer_token,target)) contains_dot_count++;

	//Then check the next ones
	while(contains_dot_count < 2){
		buffer_token[0] = buffer_token[1]; //The first digit of new token is always the second digit of previous one
		buffer_token[1] = fgetc(pi_file);
		if(contains(buffer_token,target)) contains_dot_count++;
	}
	//Now we can get the first valid token
	buffer_token[0] = buffer_token[1]; //The first digit of new token is always the second digit of previous one
	buffer_token[1] = fgetc(pi_file);
	strcpy(token_array[0].token,buffer_token);
	token_array[0].count++;
	token_count++; //holds quantity of tokens
	
	//THEN CHECK NEXT ONES TO GET ALL TOKENS
	while(!feof(pi_file)){ 
		buffer_token[0] = buffer_token[1]; //The first digit of new token is always the second digit of previous one
		buffer_token[1] = fgetc(pi_file);
		if(contains(buffer_token,'\r') || contains(buffer_token,'\n')) break; //To block to take the last digit with new line as a token
		int index_of_finded = findindex(token_array,buffer_token); //index of finded token
		if(index_of_finded == -1){
			//create new token
			strcpy(token_array[token_count].token, buffer_token);
			token_array[token_count].count++;
			token_count++;
		}
		else{
			//increase count of token by 1
			token_array[index_of_finded].count++;
		}
	}
	fclose(pi_file);
}

Token *Counter::get_most_common_three(){
	//THIS FUNCTION WILL BE CODED BY YOU
	int max_counts[3] = {0,0,0}; //Hold max counts
	int max_indexes[3] = {0,0,0}; //Hold indexes of ith count as ith element

	//FIND MAX1
	for(int i = 0; i < token_count; i++){
		if(token_array[i].count > max_counts[0]){
			max_counts[0] = token_array[i].count;
			max_indexes[0] = i;
		}
	}

	//FIND MAX2
	for(int i = 0; i < token_count; i++){
		if(token_array[i].count > max_counts[1] && i != max_indexes[0]){
			max_counts[1] = token_array[i].count;
			max_indexes[1] = i;
		}
	}
	
	//FIND MAX3
	for(int i = 0; i < token_count; i++){
		if(token_array[i].count > max_counts[2] && i != max_indexes[0] && i != max_indexes[1]){
			max_counts[2] = token_array[i].count;
			max_indexes[2] = i;
		}
	}

	//COPY THEM TO THE MOST COMMON THREE TOKEN ARRAY
	strcpy(most_common_three[0].token, token_array[max_indexes[0]].token);
	most_common_three[0].count = max_counts[0];
	strcpy(most_common_three[1].token, token_array[max_indexes[1]].token);
	most_common_three[1].count = max_counts[1];
	strcpy(most_common_three[2].token, token_array[max_indexes[2]].token);
	most_common_three[2].count = max_counts[2];
	
	return most_common_three;
}
