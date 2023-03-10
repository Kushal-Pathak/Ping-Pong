#include <iostream>
#include <windows.h>
#include <conio.h>
#define h 15
#define w 30
using namespace std;

char buffer[h][w];

struct player {
	int len = 4;
	int pos = h / 2 - len / 2 - 4;
};
struct pong {
	float x = w / 2, y = h / 2;
	float vx = -1, vy = 1;
};
pong ball;
player bat;

int game_over = 0;
int score = 0;
char play = 'y';

void init_buffer();
void bind_objects();
void render();
void update_ball();
void detect_collision();
void control();
void home_screen();
void game_over_message();
void reset_game();

int main() {
	home_screen();
	while (play == 'y') {
		reset_game();
		while (!game_over) {
			init_buffer();
			bind_objects();
			render();
			detect_collision();
			control();
			update_ball();
			Sleep(50);
		}
		game_over_message();
	}
	return 0;
}

void game_over_message() {
	cout << "                         Game Over!\n";
	Sleep(2000);
	fflush(stdin);
	cout << "                        Play again(y)? ";
	cin >> play;
}

void home_screen() {
	cout << "How to play\n";
	cout << "w: move up  s: move down\n";
	play = _getch();
	play = 'y';
}
void reset_game() {
	score = 0;
	game_over = 0;
	ball.x = w / 2; ball.y = h / 2;
	bat.pos = h / 2 - bat.len / 2;
}

void control() {
	if (_kbhit()) {
		char c = _getch();
		switch (c) {
		case 'w': if (bat.pos > 1) bat.pos--;  break;
		case 's': if (bat.pos + bat.len < h - 2) bat.pos++;  break;
		}
	}
}

void detect_collision() {
	if (ball.y <= 1 || ball.y >= h - 2) {
		ball.vy = -ball.vy;
		Beep(400, 50);
	}
	if (ball.x <= 1 || ball.x >= w - 2) {
		game_over = 1;
		Beep(300, 1000);
	}
	for (int i = bat.pos; i <= bat.pos + bat.len; i++) {
		if (ball.x == 2 && ball.y == i) {
			ball.vx = -ball.vx;
			score++;
			Beep(500, 50);
		}
		if (ball.x == w - 3 && ball.y == i) {
			ball.vx = -ball.vx;
			score++;
			Beep(500, 50);
		}
	}
}

void update_ball() {
	ball.x += ball.vx; ball.y += ball.vy;
}

void bind_objects() {
	buffer[(int)ball.y][(int)ball.x] = 'O';
	for (int i = bat.pos; i <= bat.pos + bat.len; i++) {
		buffer[i][1] = '#';
		buffer[i][w - 2] = '#';
	}
}

void init_buffer() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			buffer[i][j] = ' ';
			if (j == 0 || j == w - 1||i==0||i==h-1)buffer[i][j] = 'X';
			
		}
	}
}

void render() {
	system("cls");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << buffer[i][j]<<" ";
		}
		cout << endl;
	}
	cout << "                          Score: " << score<<endl;
}