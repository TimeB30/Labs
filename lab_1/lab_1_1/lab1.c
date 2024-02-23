#include"func_lib.c"


int main(int argc, char** argv) {
	long long int* answer = char_to_int(argv);
	long long int number = answer[0];
	switch (command_rec(argc,argv,answer)) {
		case more_than_needs:
			printf("Bad input: You enter more than 2 arguments\n");
			break;
		case less_than_needs:
			printf("Bad input: You did not enter 2 arguments\n");
			break;
		case too_big_number:
			printf("The number is too big\n");
			break;
		case no_allocation:
			printf("Error: Memory for number is not allocated\n");
		case not_number:
			printf("Bad input: not number\n");
			break;
		case wrong_flag:
			printf("You enter wrong flag\n");
			break;
		case multiplicity:		
			if (number == 0){
				printf("Can not divide by 0\n");
				break;
			}
			int* result = narutal_multiplicities(number);
			int i = 0;
			if (result[0] == 1){
				printf("Error: Memory for result is not allocated");
				break;
			}
			else{
				while(true){
					if (result[i] == -1){
						break;
					}
					printf("%d ",result[i]);
					i += 1;
				}
			}
			printf("\n");
			break;
		case simp_comp_check:
			int is_simple =  check_to_simple(number);
			if (is_simple == 1){
				printf("Number is simple \n");
			}
			else if (is_simple == 3){
				printf("Number is not simple and not compound\n");
			}
			else{
				printf("Number is compound \n");
			}
			break;
		case separate:
			int string_len = strlen(argv[1]);
			char* string = argv[1];
			int zero_indicator = 1;
			for (int i = 0; i < string_len; i++){
				if (zero_indicator){
					if (string[i] != '0'){
						printf("%c ",string[i]);
						zero_indicator = 0;				
					}
				}	
				else{
					printf("%c ",string[i]);
				}		
			}
			printf("\n");
		break;
		
		case degree_table:
			if (number < 1){
				printf("Number is lower than 1\n");
				break;
			}
			else if (number > 10){
				printf("Number is bigger than 10\n");
				break;
			}
			printf("%13d  ",1);
			for (int i = 2; i < number+1; i++){
				printf("%11d  ",i);
			}
			printf("\n\n\n\n");
			printf(" 1");
			for (int i = 0; i < number; i++){
					
					printf("%11d  ",1);
				}
			printf("\n\n\n\n");
			for (int i = 2; i < 11; i++){
				printf("%2d",i);
				int buff = i;
				printf("%11d  ",i);
				for(int n = 2; n <= number; n++){
					buff *= i;
					printf("%11d  ",buff);
				}
				printf("\n\n\n\n");
			}
		break;
		case summ_numbers:
			
				if (number < 1){
					printf("Number is lower than 1\n");
					break;
				}
				unsigned long long int summ = 1;
				summ = (1+number)*number/2;
				printf("%llu\n",summ);
			break;
		case factorial:
				unsigned long long int result2 = fctrl(number);
				if (result2 == 0){
					printf("Number is negative or too big\n");
				}
				else{
					printf("%llu\n",result2);
				}
			break;
		
	}
	return 0;
}

