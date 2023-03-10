#include <cstdio>
#include <iostream>
#include <gmp.h>

bool mpz_polytest(mpz_t& s, mpz_t& A, mpz_t& maybe, mpz_t& s2, mpz_t& s8){

	//s*s - 8*s + 16 + (8*s - 16)*A, must be a square

	mpz_mul(maybe, A, s8);
	mpz_add(maybe, maybe, s2);

	if(!mpz_perfect_square_p(maybe)){
		//vast majority of cases
		return false;
	}

	//there are handful of examples where we have to test if root is properly divisible

	mpz_t second;
	mpz_init(second);
	mpz_sqrt(maybe, maybe);
	mpz_add(maybe, maybe, s);
	mpz_sub_ui(maybe, maybe, 4);
	mpz_sub_ui(second, s, 2);
	mpz_mul_ui(second, second, 2);
	if(mpz_divisible_p(maybe, second)){
		mpz_clear(second);
		return true;
	}
	mpz_clear(second);
	return false;
}


int main(int argc,  char** argv){
	mpz_t s;
	mpz_t sum;
	mpz_t i;
	mpz_init(s);
	mpz_init(i);
	mpz_init(sum);
	mpz_set_si(s, atoi(argv[1]));
	mpz_set_si(sum, 1);
	mpz_set_si(i, 1);
	
	mpz_t lim;
	mpz_init(lim);
	mpz_set_str (lim, argv[2], 0);

	mpz_t temp;
	mpz_t s_twice;
	mpz_init(temp);
	mpz_init(s_twice);

	mpz_sub_ui(s_twice, s, 2);

	mpz_t s2;
	mpz_init(s2);
	mpz_mul(s2, s, s);
	mpz_submul_ui(s2, s, 8);
	mpz_add_ui(s2, s2, 16);

	mpz_t s8;
	mpz_init(s8);
	mpz_mul_ui(s8, s, 8);
	mpz_sub_ui(s8, s8, 16);

	mpz_t triag;
	mpz_init(triag);
	mpz_set_si(triag, 1);

	while(1){

		//the nth s-gonal number (s-2) * n * (n - 1)//2 + n

		//we sum it direclty into the sum, without ever having it separate
		mpz_addmul(sum, triag, s_twice);
		mpz_add_ui(i, i, 1);
		mpz_add(triag, triag, i);
		mpz_add(sum, sum, i);


		if(mpz_polytest(s, sum, temp, s2, s8)){
			gmp_printf("%Zd n:%Zd k:%Zd\n", sum, s, i);
		}
		/*if(mpz_cmp(i, lim) > 0){
			gmp_printf("reached %Zd\n", sum);
			break;
		}*/
		if(mpz_cmp(i, lim) > 0){
			mpz_add_ui(s, s, 1);
			mpz_mul(s2, s, s);
			mpz_submul_ui(s2, s, 8);
			mpz_add_ui(s2, s2, 16);
			mpz_mul_ui(s8, s, 8);
			mpz_sub_ui(s8, s8, 16);
			mpz_sub_ui(s_twice, s, 2);
			mpz_set_si(triag, 1);
			mpz_set_ui(i, 1);
			mpz_set_ui(sum, 1);
		}
	}
	mpz_clear(s);
	mpz_clear(sum);
	mpz_clear(i);
	mpz_clear(lim);
	mpz_clear(temp);
	mpz_clear(s_twice);
	mpz_clear(s2);
	mpz_clear(s8);

	mpz_clear(triag);

	return 0;
}
