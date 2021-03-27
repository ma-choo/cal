#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "cvector.h"
#include "greg.h"
#include "date.h"
#include "calendar.h"
#include "event.h"
#include "ui.h"

int main()
{
	calendar_t cal1 = calendar_init("My Calendar");
	calendar_t cal2 = calendar_init("Work Schedule");
	calendar_t cal3 = calendar_init("English Class");
	calendar_t cal4 = calendar_init("Math Class");
	
	vector(calendar_t) calendar_list = NULL;
	
	vector_push_back(calendar_list, cal1);
	vector_push_back(calendar_list, cal2);
	vector_push_back(calendar_list, cal3);
	vector_push_back(calendar_list, cal4);
	
	event_t event1 = event_init("Test Event 1", 6, 4, 2021);
	event_t event2 = event_init("Test Event 2", 16, 4, 2021);
	event_t event3 = event_init("Test Event 3", 2, 7, 2021);
	
	vector_push_back(calendar_list[0].events, event1);
	vector_push_back(calendar_list[0].events, event2);
	vector_push_back(calendar_list[0].events, event3);

	init_current_time();

	initscr();
	noecho();
	
	ui_start_color_pairs();
	ui_init_windows();
	ui_init_working_date();

	int running = 1;
	int jump = 1;
	int key = 0;
	int did_month_year_change = 1;
	
	refresh();

	while(running)
	{
		if(did_month_year_change)
		{
			ui_draw_calendarwin();
			ui_draw_eventswin_border();
			ui_draw_eventswin_calevents(calendar_list[0]);
		}
		
		ui_draw_eventswin_days();
		promptwin_echo(key);
		
		key = getch();
		
		switch(key)
		{
			case 50: case 51: case 52: case 53:
			case 54: case 55: case 56: case 57:
			jump = key - 48;
			break;

			case 100: case 108: // d, l
			did_month_year_change = ui_change_working_date(1 * jump);
			jump = 1;
			break;

			case 68: case 104: // D, h
			did_month_year_change = ui_change_working_date(-1 * jump);
			jump = 1;
			break;

			case 119: case 106: // w, j
			did_month_year_change = ui_change_working_date(7 * jump);
			jump = 1;
			break;

			case 87: case 107: // W, k
			did_month_year_change = ui_change_working_date(-7 * jump);
			jump = 1;
			break;

			case 113: // q
			running = 0;
			break;
		}
	}

	// delwin(listwin);
	ui_del_windows();
	endwin();

	return 0;
}
