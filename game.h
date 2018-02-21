//game.h

#ifndef GAME_H
#define GAME_H
#define MAX_SCORES 16
#define MAX_NAME 16
#define ERROR 1
#define OKAY 0
enum{VOID, EXIT, RESTART};

typedef struct {
	int x1;
	int x2;
	int x3;
	float y1;
	float y2;
	float y3;
}TNT; 

typedef struct {
	char name[MAX_NAME];
	int score;
}PLAYER; 

PLAYER hscores[MAX_SCORES];

int start(void);
void print(char** tex, int tex_len, int x, int y);
int input(int* x);
void draw(int x, int y, TNT obj, int dead, int tm, int vrr);
int calculate(TNT* obj, int x, int speed);
int menu(void);
void highScores(void);
void newScore(int tm); 
int save(PLAYER p);









#endif
