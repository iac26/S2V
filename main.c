//main.c

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "game.h"



int readFile(void);

int main(void) {
	int sx, sy;
	srand(time(NULL));
	readFile();
	initscr();
	raw();
	noecho();
	getmaxyx(stdscr,sx,sy);
	if(!((sx == 24)&&(sy == 80))) {
		printw("ERROR please use 80x24");
	}else {
		while(1) {
			int s = start();
			if (s == EXIT)
				break;
		}
	}
	refresh();
	endwin();
	return EXIT_SUCCESS;
}

int readFile(void) {
	FILE *f;
	f = fopen("Highscores", "r");
	int num; 
	char str[16];
	fgets(str, 15, f);
	sscanf(str, "%d", &num);
	for(int i = 0; i < num; i++) {
		fgets(str, 15, f);
		sscanf(str, "%s", hscores[i].name);
		fgets(str, 15, f);
		sscanf(str, "%d", &hscores[i].score);
	}
	fclose(f);
	return OKAY; 
}






