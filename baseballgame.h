#ifndef BASEBALLGAME_BASEBALLGAME_H
#define BASEBALLGAME_BASEBALLGAME_H

// 0 ~ 9 넘패드를 기준으로 작성했으며 변경이 필요하시면 변경하시면 됩니다.
// https://www.devicemart.co.kr/goods/view?no=32503
#define INPUT_NUM_MIN 0
#define INPUT_NUM_MAX 9

// 맞춰야하는 길이입니다.
// ppt기준으로 생각하면 4입니다.
// 숫자야구는 중복이 없으므로, 반드시 INPUT_NUM_MAX - INPUT_NUM_MIN + 1 보다 커야합니다.
#define NUMBER_SEQUENCE_LEN 4

// 현재 틱이나 시간을 넣거나, 이미 랜덤이 구현되어 있다면 초기화될 떄 그 값을 넣어 호출해주세요
void init_random(int seed);

// 시작전이나 4(NUMBER_SEQUENCE_LEN) strike가 나오면 호출해주세요
void reset();

// 유저가 키패드로 입력하면 호출해주세요
// 숫자를 모두 입력하면 1을 반환합니다.
// 이 경우 check_ball_strike()를 호출하여 결과를 보여주세요
int on_keypad_input(int keypad_input);

struct ball_strike {
	int ball;
	int strike;
};
// 이떄 시도 횟수를 가산합니다.
struct ball_strike check_ball_strike();

// 시도 횟수를 반환합니다.
int get_attempt_count();

// 정답이 나온 후 타이머를 이용해 3초가 지날동안 입력이 이뤄지지 않았으면, 호출해주시면 됩니다.
void on_attempt_timeout();

#endif //BASEBALLGAME_BASEBALLGAME_H
