//game.c

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "game.h"
#include "textures.h"

#define TMOUT 50
#define SPEED 1
#define DIFF 0.1
#define S_MAX 2
#define S_MIN 0
#define TITLE_POS 27
enum{S_PLAY, S_HS, S_QUIT};

int start(void) {
	time_t start_time;
	time_t current_time;
	TNT obj;
	obj.x1 = (rand() % 10)+8;
	obj.x2 = (rand() % 10)+8;
	obj.x3 = (rand() % 10)+8;
	obj.y1 = 25.;
	obj.y2 = 50.;
	obj.y3 = 75.;
	int x=4, y=1;
	int dead = 0;
	int ellapsed_time; 
	int speed = SPEED;
	int vrr = 0;
	int m = menu();
	if (m == EXIT) {
		return EXIT;
	}
	start_time = time(NULL);
	while(1) {
		current_time = time(NULL);
		ellapsed_time = current_time - start_time;
		speed = SPEED + DIFF*(ellapsed_time/5);
		vrr = (ellapsed_time/5);
		int o = input(&x);
		if(o == EXIT){
			return EXIT;
		}
		if(o == RESTART){
			return RESTART;
		}
		dead = calculate(&obj, x, speed); 
		clear();
		draw(x, y, obj, dead, ellapsed_time, vrr);
		if(dead){
			newScore(ellapsed_time);
			return RESTART;
		}
	}
	return VOID;
}

int menu(void) {
	int sel = 0; 
	while(1) {
		clear();
		move(1, TITLE_POS);
		printw("SIMULATEUR 2 VOITUR");
		move(2, 35);
		printw("MENU");
		print(s2v, S2V_LEN,6,20);
		move(14, 30);
		if(sel == S_PLAY)
			attron(A_BOLD); 
		printw("Play");
		attroff(A_BOLD);
		move(15, 30);
		if(sel == S_HS)
			attron(A_BOLD); 
		printw("High Scores");
		attroff(A_BOLD);
		move(16, 30);
		if(sel == S_QUIT)
			attron(A_BOLD); 
		printw("Quit");
		attroff(A_BOLD);
		move(14+sel, 45);
		printw(">");
		move(23,79);
		printw(" ");
		timeout(TMOUT);
		char c = getch();
		if (c == 'q')
			return EXIT;
		if (c == 'w') {
			sel -= 1;
			if (sel < S_MIN) {
				sel = S_MAX;
			}
		}
		if (c == 's') {
			sel += 1;
			if (sel > S_MAX) {
				sel = S_MIN;
			}
		}
		if ((c == 'd')||(c == '\n')) {
			if (sel == S_PLAY) {
				return VOID;
			}
			if (sel == S_HS) {
				highScores();
			}
			if (sel == S_QUIT) {
				return EXIT;
			}
		}
		
		
	}
	
}

void highScores(void) {
	while(1) {
		clear();
		move(1, TITLE_POS);
		printw("SIMULATEUR 2 VOITUR");
		move(2, 31);
		printw("HIGH SCORES");
		attron(A_BOLD);
		move(4,28);
		printw("n  name            score");
		attroff(A_BOLD);
		for(int i = 0; i < MAX_SCORES; i++) {
			move(5+i, 27);
			printw("%2d: %-15s  %4d", i+1, hscores[i].name, hscores[i].score);
		}
		move(23,79);
		printw(" ");
		timeout(TMOUT);
		char c = getch();
		if (c == '\n'){
			break;
		}
		
	}
}

void newScore(int tm){
	char name[16];
	for(int i = 0; i < 16; i++)
		name[i] = '\0';
	int i = 0; 
	while(1) {
		clear();
		move(1, TITLE_POS);
		printw("SIMULATEUR 2 VOITUR");
		print(go, GO_LEN, 3, 12);
		move(9, 28);
		attron(A_BOLD);
		printw("score: %d", tm); 
		attroff(A_BOLD);
		move(10, 28);
		printw("enter name: %-15s", name); 
		move(10, 39);
		attron(A_BLINK);
		printw(">");
		attroff(A_BLINK);
		move(23,79);
		printw(" ");
		timeout(TMOUT);
		char c = getch();
		if((((int) c) > 31)&&(((int) c) < 127) ){
			name[i] = c;
			i++;
		}
		if((c == '\n')||(i > 13)){
			name[i] = '\0';
			PLAYER p;
			strcpy(p.name, name);
			p.score = tm;
			save(p);
			break;
		}
	}
}

int save(PLAYER p) {
	for(int i = 0; i < MAX_SCORES; i++){
		if(p.score > hscores[i].score){
			for (int j = MAX_SCORES-1; j > i; j--) {
				strcpy(hscores[j].name, hscores[j-1].name);
				hscores[j].score = hscores[j-1].score;
			}
			hscores[i].score = p.score;
			strcpy(hscores[i].name, p.name);
			FILE* f;
			f = fopen("Highscores", "w");
			fprintf(f, "%d\n", MAX_SCORES);
			for (int i = 0; i < MAX_SCORES; i++) {
				fprintf(f, "%s\n",hscores[i].name);
				fprintf(f, "%d\n",hscores[i].score);
			}
			fclose(f);
			return OKAY; 
		}
	}
	return OKAY;
}

int input(int* x) {
	char ch;
	timeout(TMOUT);
	ch = getch();
	if (ch == 'w') {
		if (*x > 2)
			*x -= 1;
	}
	if (ch == 's') {
		if (*x < 17)
			*x += 1;
	}
	if (ch == 'q') {
		return EXIT;
	}
	if (ch == 'm') {
		return RESTART;
	}
	return VOID;
}

void print(char** tex, int tex_len, int x, int y) {
	for (int i = 0; i < tex_len; i++) {
		move(x+i,y);
		printw(tex[i]);
	}
}

void draw(int x, int y, TNT obj, int dead, int tm, int vrr) {
	move(0,0);
	printw("press \"m\" for menu");
	move(1, TITLE_POS);
	printw("SIMULATEUR 2 VOITUR");
	print(road, ROAD_LEN, 3, 2);
	print(road, ROAD_LEN, 21, 2);
	print(car, CAR_LEN, x, y);
	print(tnt, TNT_LEN, obj.x1, (int)obj.y1);
	print(tnt, TNT_LEN, obj.x2, (int)obj.y2);
	print(tnt, TNT_LEN, obj.x3, (int)obj.y3);
	attron(A_BOLD);
	move(0,70);
	printw("Score: %d", tm);
	move(23, 1);
	printw("VRRRRRRR");
	vrr += (rand()%4) -1;
	for(int i = 0; i < vrr; i++) {
		move(23,9+i);
		printw("R");
	}
	
	attroff(A_BOLD);
	move(23,79);
	printw(" ");
	if (dead) {
		timeout(-1);
		attron(A_BOLD);
		print(explo, EXPLO_LEN, x-2, y+3);
		print(go, GO_LEN, 9, 20);
		move(23, 1);
		printw("BOOOOOOOOOOOOOM                          ");
		attroff(A_BOLD);
		move(15,35);
		printw("you survived %d seconds!", tm);
		move(23,79);
		printw(" ");
		while(getch()!='\n');
	}
}

int calculate(TNT* obj, int x, int speed) {
	
	if(obj->y1 < 1) {
		obj->y1 = 75;
		obj->x1 = (rand() % 16)+2;
	}
	if(obj->y2 < 1) {
		obj->y2 = 75;
		obj->x2 = (rand() % 16)+2;
	}
	if(obj->y3 < 1) {
		obj->y3 = 75;
		obj->x3 = x;
	}
	
	obj->y1 -= speed;
	obj->y2 -= speed;
	obj->y3 -= speed;
	
	if (obj->y1 < 15) {
		if ((obj->x1 < x+4)&&(obj->x1 > x-4))
			return 1;
	}
	if (obj->y2 < 15) {
		if ((obj->x2 < x+4)&&(obj->x2 > x-4))
			return 1;
	}
	if (obj->y3 < 15) {
		if ((obj->x3 < x+4)&&(obj->x3 > x-4))
			return 1;
	}
	return 0;
}



/*
 * 1) move objects
 * 2) wait for user with timeout
 * 3) print everything
 **/
