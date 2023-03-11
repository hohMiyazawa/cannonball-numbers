#include <stdlib.h>
#include <gmp.h>

int main(int argc, char** argv){
	unsigned long s,i,lim,tri;
	s = atoi(argv[1])-3;
	lim = atoi(argv[2]);
	unsigned __int128 sum;
	mpz_t acc,temp;
	mpz_inits(acc,temp,NULL);
	i = lim;
	for(;;){
		if(i == lim){
			s++;
			tri = i = 1;
			mpz_set_ui(acc, (s+2) * (s+2));
		}
		sum = (++i + s*tri) * (unsigned __int128)(s*8);
		tri += i;
		mpz_add_ui(acc, acc, sum);
		if(mpz_perfect_square_p(acc)){
			mpz_sqrt(temp, acc);
			mpz_add_ui(temp, temp, s-2);
			if(mpz_divisible_ui_p(temp, s*2)){
				gmp_printf("n:%d k:%d\n", s+2, i);
			}
		}
	}
	mpz_clears(acc,temp,NULL);
}
