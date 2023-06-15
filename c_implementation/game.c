#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define L 30
#define H 30

int** evolution(int* w[]) {
	int** tw = malloc(sizeof(int*) * H);
	for (int i = 0; i < H; i++) {
		tw[i] = malloc(sizeof(int) * L);
		for (int j = 0; j < L; j++) {
			tw[i][j] = w[i][j];
		}
	}

	for (int i = 0; i < H; i++) {
		int li = (i - 1 + H) % H;
		int ri = (i + 1) % H;
		for (int j = 0; j < L; j++) {
			int uj = (j - 1 + L) % L;
			int dj = (j + 1) % L;
			int naibs = w[li][uj] + w[li][j] + w[li][dj]\
						+ w[i][uj] + w[i][dj] +\
						w[ri][uj] + w[ri][j] + w[ri][dj];
			if (naibs > 3) {
				// not enough resources to survive
				tw[i][j] = 0;
			} else if (naibs < 2) {
				// died lonely
				tw[i][j] = 0;
			} else if (naibs == 3) {
				// reproduction
				tw[i][j] = 1;
			}

		}
	}

	return tw;
}


void random_creature(int** w) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < L; j++) {
			if ((rand() % 30) == 0) {
				w[i][j] = w[i][j] == 0 ? 1 : 0;
			}
		}
	}
}


void show(int** world) {
	system("clear");
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < L; j++) {
			if (world[i][j] == 1)
				printf("\033[92m* ");
			else
				printf("\033[0m. ");
		}
		printf("\033[0m\n");
	}

}

int main(int argc, char* argv[]) {
	srand(time(0));	
	int** world = malloc(sizeof(int*) * H);
	for (int i = 0; i < H; i++) {
		world[i] = (int*)malloc(sizeof(int) * L);
		for (int j = 0; j < L; j++) {
			world[i][j] = 0;
		}
	}

//  glider
//	world[5][5] = 1;
//	world[4][4] = 1;
//	world[6][5] = 1;
//	world[6][4] = 1;
//	world[6][3] = 1;

	while (1) {
		show(world);
		usleep(300000);
		world = evolution(world);
		if ((rand() % 8) == 0)
			random_creature(world);
	}

	return 0;
}
