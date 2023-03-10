/*
slightly faster, but the polygon may not have more than about a billion sides, and must be run on a 64-bit systems
*/

#include <cstdio>
#include <iostream>
#include <gmp.h>

bool mpz_polytest(unsigned long int s, mpz_t& A, mpz_t& maybe, unsigned long int s2, unsigned long int s8){
/*
s*s - 8*s + 16 + (8*s - 16)*A
*/
	mpz_mul_ui(maybe, A, s8);
	mpz_add_ui(maybe, maybe, s2);

	if(!mpz_perfect_square_p(maybe)){
		return false;
	}

	mpz_t second;
	mpz_init(second);
	mpz_sqrt(maybe, maybe);
	mpz_add_ui(maybe, maybe, s);
	mpz_sub_ui(maybe, maybe, 4);
	mpz_set_ui(second, 2*s - 4);
	if(mpz_divisible_p(maybe, second)){
		mpz_clear(second);
		return true;
	}
	mpz_clear(second);
	return false;
}


int main(int argc,  char** argv){
	mpz_t sum;
	mpz_init(sum);
	mpz_set_ui(sum, 1);

	unsigned long int s = atoi(argv[1]);
	mpz_t s_twice;
	mpz_init(s_twice);
	mpz_set_ui(s_twice, s-2);
	unsigned long int i = 1;
	unsigned long int lim = atoi(argv[2]);

	mpz_t temp;
	mpz_init(temp);

	unsigned long int s2 = s*s - s*8 + 16;
	unsigned long int s8 = s*8 - 16;

	unsigned long int triag = 1;

	while(1){

//(s-2) * n * (n - 1)//2 + n;
		mpz_addmul_ui(sum, s_twice, triag);
		i++;
		triag += i;
		mpz_add_ui(sum, sum, i);


		if(mpz_polytest(s, sum, temp, s2, s8)){
			gmp_printf("%Zd %d %d\n", sum, s, i);
		}
		/*if(i == lim){
			gmp_printf("reached %Zd\n", sum);
			break;
		}
		continue;*/
		if(i == lim){
			s++;
			s2 = s*s - s*8 + 16;
			s8 = s*8 - 16;
			mpz_set_ui(s_twice, s-2);
			triag = 1;
			/*if(mpz_cmp_ui(s, 10) == 0){
				break;
			}*/
			i = 1;
			mpz_set_ui(sum, 1);
		}
	}
	mpz_clear(sum);

	mpz_clear(temp);

	mpz_clear(s_twice);

	return 0;
}
