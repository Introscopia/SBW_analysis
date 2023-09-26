#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


int random_in_range( int min, int max ){
    return (rand() % (max-min)) + min;
}

int roll_d( int X, int D ){
	int o = 0;
	for (int i = 0; i < X; ++i){
		o += ( rand() % D ) + 1;
	}
	return o;
}

int main(int argc, char const *argv[]){

	srand (time(NULL));

	int stats [3] = { 3, 3, 3 };
	const char stat_names [3][16] = { "Sexy", "Battle", "Wizard" };

	enum{ FULL, RESULTS };

	int MODE = RESULTS;

	for (int N = 0; N < 2600; ++N ){

		int victories = 0;
		int stress = 0;
		int determination = 0;
		int round = 1;

		while(1){

			int challenge_type = random_in_range( 0, 3 );
			int challenge_level = random_in_range( 4, 7 );

			if( MODE == FULL ){
				printf("Round %d. Challenge: %s level %d.\n", round, stat_names[challenge_type], challenge_level );
			}

			int success = 0;
			int highest = 0;

			if( MODE == FULL ) printf("Rolled: ");
			for (int i = 0; i < stats[ challenge_type ]; ++i ){
				int R = roll_d( 1, 6 );
				if( MODE == FULL ) printf("%d", R );
				if( R > highest ) highest = R;
				if( MODE == FULL ){
					if( i < stats[ challenge_type ]-1 ) printf(", ");
					else printf(".\n");
				}
			}
			how_did_i_do:
			if( highest > challenge_level ) success = 1;
			else if( highest == challenge_level ){
				success = 1;
				stress += 1;
			}

			if( success ){
				if( MODE == FULL ) printf("Success!\n");
				victories++;
			}
			else{
				if( determination > 0 ){
					if( MODE == FULL ) printf("using determination... ");
					while( determination > 0 ){
						determination--;
						int R = roll_d( 1, 6 );
						if( MODE == FULL ) printf("%d", R );
						if( R > highest ) highest = R;
						if( R >= challenge_level ){
							if( MODE == FULL ) printf("\n");
							goto how_did_i_do;
						}
						if( MODE == FULL ) printf(", ");
					}
					if( MODE == FULL ) printf("\n");
				}

				if( MODE == FULL ) printf("Failure.\n");
				stress += 1;
				determination += 1;

				if( stress > highest ){
					if( MODE == FULL ) printf("YOU EXPLODE! (%d>%d)\n", stress, highest );
					break;
				}

			}
			if( MODE == FULL ) printf("Stress: %d, Determination: %d.\n\n", stress, determination );
			round++;
		}

		if( MODE == FULL ) printf("Had %d victories in %d rounds.\n", victories, round );
		else printf("%d, %d\n", victories, round );
	}

	return 0;
}