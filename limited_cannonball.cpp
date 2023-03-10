#include <stdlib.h>
#include <gmp.h>

int main(int argc, char** argv){
	unsigned long s,i,lim,tri;
	s = atoi(argv[1])-3;
	lim = atoi(argv[2]);
	mpz_t sum,acc;
	mpz_inits(sum,acc,NULL);
	i = lim;
	for(;;){
		if(i == lim){
			s++;
			tri = i = 1;
			mpz_set_ui(acc, (s+2) * (s+2));
		}
		mpz_set_ui(sum, ++i + s*tri);
		tri += i;
		mpz_addmul_ui(acc, sum, s*8);
		if(mpz_perfect_square_p(acc)){
			mpz_sqrt(sum, acc);
			mpz_add_ui(sum, sum, s-2);
			if(mpz_divisible_ui_p(sum, s*2)){
				gmp_printf("n:%d k:%d\n", s+2, i);
			}
		}
	}
	mpz_clears(sum,acc,NULL);
}
