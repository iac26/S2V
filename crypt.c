//crypt.c
#include <stdlib.h>
#include <ncurses.h>
#define KEY_L 64

int crypt(void){
	char* key = "password";
	int i;
	char* filename = "Highscores";
	FILE* data = fopen(filename, "r");
	if(data == NULL) {
		return 1;
	}
	fseek(data, 0L, SEEK_END);
	int size = ftell(data);
	char msg[size];
	rewind(data);
	for(i = 0; i < size; i++){
		msg[i] = fgetc(data);
	}
	fclose(data);
	int len = 8;
	FILE* out = fopen(filename, "w");
	for (i = 0; i < size; i++) {
		fputc((msg[i] ^ key[i%len]), out);
	}
	fclose(out);
	return 0;	
}
