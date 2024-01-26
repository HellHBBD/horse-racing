#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#if defined(__linux__)
#include <unistd.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

#define CLEAR() printf("\033[2J") // clear screen
#define CLEAR_LINE() printf("\r\033[K") // clear line
#define SET(x, y) printf("\033[%d;%dH", x, y) //set cursor position
#define HIDE() printf("\033[?25l") //hide cursor
#define SHOW() printf("\033[?25h") //show cursor
#define MOVE_DOWN(n) printf("\033[%dB", n) //move cursor down
#define MOVE_RIGHT(n) printf("\033[%dC", n) //move cursor right
#define ORANGE() printf("\033[33m") //change cursor color to orange
#define RESET() printf("\033[0m") //reset cursor color

int horse = 5; //horse amount
int arena_size = 34; //size of the arena
int frequency = 400; //update frequency (ms)

void usleep(unsigned long);
int getopt(int argc, char *argv[], const char *optstring);

void mssleep(long ms) // wait in ms
{
#if defined(__linux__)
	usleep(ms * 1000);
#elif defined(_WIN32)
	Sleep(ms);
#endif
}

void print_arena()
{
	for (int i = 0; i < horse + 1; i++) {
		for (int j = 0; j < arena_size; j++)
			putchar('-');
		MOVE_DOWN(5);
		putchar('\r');
	}
}

void print_horse(int num)
{
	ORANGE();
	CLEAR_LINE();
	MOVE_RIGHT(num);
	puts("  - - ");
	CLEAR_LINE();
	MOVE_RIGHT(num);
	puts("   ---");
	CLEAR_LINE();
	MOVE_RIGHT(num);
	puts("----- ");
	CLEAR_LINE();
	MOVE_RIGHT(num);
	puts("-   - ");
	RESET();
}

int main(int argc, char **argv)
{
	int optarg;
	for (int i = 1; i < argc; i++) {
		if (sscanf(argv[i], "-horse=%d", &optarg))
			horse = optarg;
		else if (sscanf(argv[i], "-arena=%d", &optarg))
			arena_size = optarg;
		else if (sscanf(argv[i], "-freq=%d", &optarg))
			frequency = optarg;
	}

	int *horse_position = (int *)malloc(sizeof(int) * horse);
	memset(horse_position, 0, sizeof(int) * horse);
	int win = 0;

	srand(time(NULL));
	SET(0, 0);
	CLEAR();
	HIDE();
	print_arena();
	while (1) {
		if (win)
			break;

		for (int i = 0; i < horse; i++) {
			horse_position[i] += rand() % 3 + 1;
			if (horse_position[i] > arena_size - 6) {
				horse_position[i] = arena_size - 5;
				win |= (1 << i);
			}
		}

		for (int i = 0; i < horse; i++) {
			SET(5 * i + 2, 0);
			print_horse(horse_position[i]);
		}
		mssleep(frequency);
	}

	puts("");
	for (int i = 0; i < 5; i++) {
		if ((win >> i) & 1)
			printf("horse %d is winner\n", i + 1);
	}
	SHOW();
	free(horse_position);
	return 0;
}
