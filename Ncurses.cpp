#include <ncurses.h>

int main (int argc, char* argv[])
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	attron(COLOR_PAIR(1));
	printw("Hello World!");
	attroff(COLOR_PAIR(1));
	
	getch();
	endwin();
	
	return 0;
}
