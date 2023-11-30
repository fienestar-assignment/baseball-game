#include "baseballgame.h"

static int prng_seed;

void init_random(int seed)
{
	prng_seed = seed;
}

// 임의의 C 난수 분포를 가져왔습니다.
// 고르지 않은 prng입니다.
// https://pubs.opengroup.org/onlinepubs/009695399/functions/rand.html
static int custom_random(int end)
{
	prng_seed = prng_seed * 1103515245 + 12345;
	return (prng_seed % end + end) % end;
}

struct baseball_game {
	int answer[NUMBER_SEQUENCE_LEN];
	int user_input[NUMBER_SEQUENCE_LEN];
	int input_index;
	int attempt_count;
};

static struct baseball_game data;
static int initialized = 0;

#include <stdio.h>

static void init_answer(struct baseball_game* game)
{
	int i;
	int len = INPUT_NUM_MAX - INPUT_NUM_MIN + 1;
	int buffer[len];
	for(i=0; i!=len; ++i)
		buffer[i] = INPUT_NUM_MIN + i;

	for(i=0; i!=len*2; ++i) {
		int a = custom_random(len), b = custom_random(len);
		int t = buffer[a];
		buffer[a] = buffer[b];
		buffer[b] = t;
	}

	for(i=0; i!=NUMBER_SEQUENCE_LEN; ++i) {
		game->answer[i] = buffer[i];
		printf("%d ", game->answer[i]);
	}
	printf("\n");
}

void reset()
{
	initialized = 1;
	init_answer(&data);
	data.input_index = 0;
	data.attempt_count = 0;
}

int on_keypad_input(int keypad_input)
{
	if(!initialized) reset();
	if(data.input_index == NUMBER_SEQUENCE_LEN) return 1;
	data.user_input[data.input_index++] = keypad_input;
	return data.input_index == NUMBER_SEQUENCE_LEN;
}

struct ball_strike check_ball_strike()
{
	struct ball_strike result = {};
	int i, j;

	if(!initialized) reset();

	for(i=0; i!=NUMBER_SEQUENCE_LEN; ++i)
		for(j=0; j!=NUMBER_SEQUENCE_LEN; ++j)
			if(data.user_input[i] == data.answer[j]){
				if(i == j) ++result.strike;
				else ++result.ball;
			}

	data.input_index = 0;
	++data.attempt_count;

	return result;
}

int get_attempt_count()
{
	return data.attempt_count;
}

void on_attempt_timeout()
{
	++data.attempt_count;
}
