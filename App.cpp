#include <iostream>
#define h 25
#define w 60
using namespace std;

char buffer[h][w];

void init_buffer();
void render();

int main() {
	init_buffer();
	render();
	return 0;
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
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << buffer[i][j]<<" ";
		}
		cout << endl;
	}
}
