#include <iostream>
#include <windows.h>
#define h 15
#define w 40
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

void init_buffer();
void bind_objects();
void render();
void update_ball();
void detect_collision();

int main() {
	while (!game_over) {
		init_buffer();
		bind_objects();
		detect_collision();
		render();
		update_ball();
		Sleep(50);
	}
	cout << "Game Over!";
	return 0;
}

void detect_collision() {
	if (ball.y <= 1 || ball.y >= h - 2) ball.vy = -ball.vy;
	if (ball.x <= 1 || ball.x >= w - 2) game_over = 1;
	for (int i = bat.pos; i <= bat.pos + bat.len; i++) {
		if (ball.x == 2 && ball.y == i) ball.vx = -ball.vx;
		if (ball.x == w-3 && ball.y == i) ball.vx = -ball.vx;
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
}
