#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int print_tree(int midy, int midx, int** tree, int lanes, int turn);
int print_text(int midy, int midx, int lanes, int turn);

int main(int argc, char const *argv[]) {
	initscr();
	noecho();	
	curs_set(0);
	if(has_colors() == 0) {	endwin();
		printf("Your terminal does not support color\n");
		return 0;
	}

	srand(time(0));

	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);

	//DEFINE TREE
	int** tree;
	int lanes = 10;

	//INIT TREE
	tree = (int**) malloc(sizeof(int*)*lanes);
	for (int i = 0; i < lanes; ++i) {
		tree[i] = (int*) malloc(sizeof(int)*(i*2+1));
		
		for (int j = 1; j < i*2; ++j) {
			tree[i][j] = 2;
		}

		tree[i][0] = tree[i][i*2] = 1;
	}

	tree[0][0] = 5;

	tree[1][1] = tree[2][3] = tree[3][2] = tree[3][6] = tree[4][2] = 10;
	tree[5][4] = tree[5][9] = tree[6][2] = tree[6][8] = tree[7][4] = tree[7][12] = 10;
	tree[8][2] = tree[8][8] = tree[8][11] = tree[9][4] = tree[9][10] = tree[9][13] = 10;

	tree[1][1] = tree[2][1] = tree[3][5] = tree[4][3] = tree[4][7] = 11;
	tree[5][3] = tree[5][8] = tree[6][1] = tree[6][9] = tree[7][5] = tree[7][11] = 11;
	tree[8][3] = tree[8][9] = tree[8][14] = tree[9][1] = tree[9][6] = tree[9][16] = 11;


	int x, y, turn;

	turn = 0;
	getmaxyx(stdscr, x, y);
	while(1) {
		turn++;
		print_tree(x/2,y/2,tree, lanes, turn);
		print_text(x/2,y/2,lanes,turn);
		refresh();
		usleep(400*1000);
	}

	endwin();	
	return 0;
}

int print_tree(int midy, int midx, int** tree, int lines, int turn) {
	int starting_x = midx;
	int starting_y = midy-((lines+2)/2);
	int col;

	attron(A_BOLD);
	for (int i = 0; i < lines; ++i) {
		int tot = i * 2+1;
		for (int j = 0; j < tot; ++j) {
			switch(tree[i][j] + (turn%2)) {
				case 11:

					col = (rand()) % 6;

					switch (col) {
						case 0:
							attron(COLOR_PAIR(1)); 
						break;

						case 1:
							attron(COLOR_PAIR(3)); 
						break;

						case 2:
							attron(COLOR_PAIR(4)); 
						break;

						case 3:
							attron(COLOR_PAIR(5)); 
						break;

						case 4:
							attron(COLOR_PAIR(6)); 
						break;

						case 5:
							attron(COLOR_PAIR(7)); 
						break;
					}

					if ((rand() * 1758237) % 2) 
						mvaddch(starting_y+i,starting_x-i+j,'o'); 
					else 
						mvaddch(starting_y+i,starting_x-i+j,'O');

					attroff(COLOR_PAIR(1));
					attroff(COLOR_PAIR(3));
					attroff(COLOR_PAIR(4));
					attroff(COLOR_PAIR(5));
					attroff(COLOR_PAIR(6));
					attroff(COLOR_PAIR(7));
				break; 

				case 5: case 6:
					attron(COLOR_PAIR(3)); 
					mvaddch(starting_y+i,starting_x-i+j,'*');
					attroff(COLOR_PAIR(3));
				break;

				default:		
					attron(COLOR_PAIR(2)); 
					mvaddch(starting_y+i,starting_x-i+j,'*');
					attroff(COLOR_PAIR(2));
				break;
			}
		}
	}
	attroff(A_BOLD);

	attron(COLOR_PAIR(3));
	mvprintw(starting_y+lines,starting_x-1,"mWm");
	mvprintw(starting_y+lines+1,starting_x-2,"mWWWm");
	attroff(COLOR_PAIR(3));
}

int print_text(int midy, int midx, int lines, int turn) {	
	//MERRY CHRISTMAS
	int starting_x = midx - 7;
	int starting_y = midy-((lines+2)/2) - 3;
	
	//HAPPY CODING YEAR 2020
	int ending_x = midx - 11;
	int ending_y = midy+((lines+2)/2) + 3;
	
	attron(A_BOLD);
	attron(COLOR_PAIR(1));

	mvprintw(starting_y, starting_x, "MERRY CHRISTMAS");
	mvprintw(ending_y, ending_x, "HAPPY ");
	attroff(COLOR_PAIR(1));
	
	switch (turn % 6) {
		case 1: case 2:
			attron(COLOR_PAIR(6));
		break;
		
		case 3: case 4:
			attron(COLOR_PAIR(7));
		break;

		case 5: case 0:
			attron(COLOR_PAIR(4));
		break;
	}

	printw("CODING ");
	attroff(COLOR_PAIR(6));
	attroff(COLOR_PAIR(7));
	attroff(COLOR_PAIR(4));
	
	attron(COLOR_PAIR(1));
	printw("YEAR 2020!");
	attroff(COLOR_PAIR(1));
	attroff(A_BOLD);
}