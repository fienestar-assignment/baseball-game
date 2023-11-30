#include <stdio.h>
#include <time.h>
#include "baseballgame.h"

int main() {
	struct ball_strike result;
	int keypad_input;
	init_random((int)time(NULL));
	while(1) {
		reset();
		do {
			do {
				scanf("%d", &keypad_input);
			} while (!on_keypad_input(keypad_input));

			result = check_ball_strike();
			printf("%d Ball %d Strike\n", result.ball, result.strike);
		} while(result.strike != NUMBER_SEQUENCE_LEN);
		printf("attempt-count: %d\n", get_attempt_count());
	}
}
