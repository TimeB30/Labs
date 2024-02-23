#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include"enums.h"




unsigned long long int fctrl( unsigned int value){
	unsigned long long answer = 0;
	if ((value > 20) || (value < 0)){
		return answer;
	}
	else if ((value == 1) || (value == 0)){
		answer = 1;
		return answer;
	}
	return value * fctrl(value-1);
    
}

long long int* char_to_int(char* value[]) {
	long long int* answer = (long long int*)calloc(2,sizeof(long long int));
	if (answer == NULL){
		answer[0] == 1; //allocation status report
		return answer;
	}
	char* string = value[1];
	int string_len = strlen(string);
	bool negative = false;
	int i = 0;
	if (string_len > 19){
		answer[1] = 3;
	}
	if (answer == NULL){
		answer[1] = 2;
		return answer;
	}
	if (string[0] == '-') {
		negative = true;
		i = 1;
		
	}
	for (i; i < string_len; i++) {
		if (((string[i] < 48) || (string[i] > 57))) {
			answer[1] = 1;
			return answer;	
		}
		else {
			int num = string[i] - 48;
			answer[0] = answer[0] * 10 + num;
		}
	 }
	 
	if (negative) {
		answer[0] *= -1;
	}
	return answer;
}

enum flags command_rec(int argc,char** argv,long long int* answer) {
	char* string = argv[2];
    if (argc > 3){
		return more_than_needs;
	}
	else if (argc < 3){
		return less_than_needs;
	}
	else if (answer[1] == 3){
		return too_big_number;
	}
	else if (answer[1] == 2){
		return no_allocation;
	}
	else if (answer[1] == 1){
		return not_number;
	}
	if ((string[0] == '-') || (string[0] == '/')){
		if (string[1] == 'h') {
			return multiplicity;
		}
		else if (string[1] == 'p') {
			return simp_comp_check;
		}
		else if (string[1] == 's') {
			return separate;
		}
		else if (string[1] == 'e') {
			return degree_table;
		}
		else if (string[1] == 'a') {
			return summ_numbers;
		}
		else if (string[1] == 'f') {
			return factorial;
		}
		else{
			return wrong_flag;
		}
	}
	else{
		return wrong_flag;
	}
	
    
}

int* narutal_multiplicities(int num){
	num = fabs(num);
	int size = 100 / num + 1;
	int* answer = (int*)calloc(size,sizeof(int));
	int buff = 0;
	if (answer == NULL){
		answer[0] == 1; //allocation status report
		return answer;
	}
	else{
		answer[0] = 0;
		answer[size] = -1;
	}
	for (int i = 1; i < size; i++){
		buff += num;
		answer[i] = buff ;  
	}
	return answer;
}
int check_to_simple(int num){
	int limit = sqrt(num);
	int count = 1;
    if (num < 2){
        return 3;
    }
    else if (num == 2){	
        return 1;
    }
	for (int i = 2; i <= limit; i++){
		if (num % i == 0){
			return 0;
			//count += 1;
           
		}
		// if (count > 1){
		// 	return 0;
		// }
	}
   
	return 1;

}
