#include <math.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int x, y;
} point_t;

void draw_low(WINDOW* scr, int x0, int y0, int x1, int y1, char lc){
	int dx = x1 - x0;
	int dy = y1 - y0;
	int yi = 1;

	if(dy < 0){
		yi = -1;
		dy = -dy;
	}
	int D = (2 * dy) - dx;
	int y = y0;

	for(int x = x0; x < x1; x++){
		mvwaddch(scr, y, x, lc);
		if(D > 0){
			y += yi;
			D += (2 * (dy - dx));
		}
		else
			D += 2 * dy;
	}
}
void draw_high(WINDOW* scr, int x0, int y0, int x1, int y1, char lc){
	int dx = x1 - x0;
	int dy = y1 - y0;
	int xi = 1;

	if(dx < 0){
		xi = -1;
		dx = -dx;
	}
	int D = (2 * dx) - dy;
	int x = x0;

	for(int y = y0; y < y1; y++){
		mvwaddch(scr, y, x, lc);
		if(D > 0){
			x += xi;
			D += (2 * (dx - dy));
		}
		else
			D += 2 * dx;
	}
}

void draw_line(WINDOW* scr, int x0, int y0, int x1, int y1, char lc){	//redo with points
	if(abs(y1 - y0) < abs(x1 - x0)){
		if(x0 > x1)
			draw_low(scr, x1, y1, x0, y0, lc);
		else
			draw_low(scr, x0, y0, x1, y1, lc);
	}
	else{
		if(y0 > y1)
			draw_high(scr, x1, y1, x0, y0, lc);
		else
			draw_high(scr, x0, y0, x1, y1, lc);
	}
}

int main(){
	//initialize the screen & sets up no echo
	initscr();
	cbreak();
	noecho();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	//constants
	const int MAX_COLS = COLS - 1;
	const int MAX_LINES = LINES - 2;

	const char GRID_CHAR = '.';
	const char LINE_CHAR = '#';
	const char POINT_CHAR = '@';

	const char INSTRUCTIONS[] = "q - exit   f - create point   d - delete point   j - up   k - down   h - left   l - right";

	//variables
	int num_points = 0;
	char user_input = ' ';
	//1D arrays
	point_t cursor = (point_t){0, 0};
	point_t points[(LINES - 1) * COLS];

	clear();
	//print the instructions at the bottom
	mvaddstr(MAX_LINES + 1, (MAX_COLS - strlen(INSTRUCTIONS))/2, INSTRUCTIONS);
	//main loop
	while(user_input != 'q'){
		for(int x = 0; x < MAX_LINES + 1; x++){
			for(int y = 0; y < MAX_COLS; y++){
				mvaddch(x, y, GRID_CHAR);
			}
		}
		for(int i = 0; i < num_points - 1; i++){
			draw_line(stdscr, points[i].x, points[i].y, points[i+1].x, points[i+1].y, LINE_CHAR);
		}
		for(int i = 0; i < num_points; i++){
			mvaddch(points[i].y, points[i].x, POINT_CHAR);
		}
		switch(user_input){
			case 'f':
				points[num_points].x = cursor.x;
				points[num_points].y = cursor.y;
				num_points++;
				break;
			case 'd':
				points[num_points].x = 0;
				points[num_points].y = 0;
				if(num_points > 0)
					num_points--;
				break;
			case 'j':
				if(cursor.y != 0)
					cursor.y--;
				break;
			case 'k':
				if(cursor.y != MAX_LINES)
					cursor.y++;
				break;
			case 'h':
				if(cursor.x != 0)
					cursor.x--;
				break;
			case 'l':
				if(cursor.x != MAX_COLS)
					cursor.x++;
				break;
		}
		move(cursor.y, cursor.x);
		user_input = getch();
		refresh();
	}
	endwin();
	return 0;
}
