#include <curses.h>
#include "cvector.h"
#include "greg.h"
#include "date.h"
#include "calendar.h"
#include "event.h"

static int screen_h, screen_w;
static int calendar_h, calendar_w, calendar_y, calendar_x;
static int events_h, events_w, events_y, events_x, events_hfactor, events_wfactor;
static int promptwin_h, promptwin_w, promptwin_y, promptwin_x;

static int selected_day, working_month, working_year;
static int first_day_offset;

static WINDOW *calendarwin, *eventswin, *promptwin;

void ui_init_working_date()
{
	selected_day = get_current_day();
	working_month = get_current_month();
	working_year = get_current_year();
	first_day_offset = zeller(working_month, working_year);
}

int ui_change_working_date(int i)
{
	selected_day += i;
	if (selected_day > get_days_in_month(working_month))
	{
		selected_day -= get_days_in_month(working_month);
		working_month++;
		if(working_month > 11)
		{
			working_year++;
			working_month = 0;
		}
		first_day_offset = zeller(working_month, working_year);
		return 1;
	}
	else if (selected_day < 1)
	{
		working_month--;
		if(working_month < 0)
		{
			working_year--;
			working_month = 11;
		}
		selected_day += get_days_in_month(working_month);
		first_day_offset = zeller(working_month, working_year);
		return 1;
	}
	return 0;
}

void ui_start_color_pairs()
{
	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_GREEN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLUE);
}

void ui_init_windows()
{
	getmaxyx(stdscr, screen_h, screen_w);
	
	calendar_h = 9;
	calendar_w = 22;
	calendar_y = 0;
	calendar_x = 0;

	events_hfactor = (screen_h - 2) / 6;
	events_wfactor = ((screen_w - calendar_w) - 2) / 7;
	events_h = (events_hfactor * 6) + 1;
	events_w = (events_wfactor * 7) + 1;
	events_y = 0;
	events_x = calendar_w;

	promptwin_h = 1;
	promptwin_w = screen_w;
	promptwin_y = events_h;
	promptwin_x = 0;
	
	calendarwin = newwin(calendar_h, calendar_w, calendar_y, calendar_x);
	eventswin = newwin(events_h, events_w, events_y, events_x);
	promptwin = newwin(promptwin_h, promptwin_w, promptwin_y, promptwin_x);
}

void ui_del_windows()
{
	delwin(eventswin);
	delwin(calendarwin);
	delwin(promptwin);
}

void ui_draw_calendarwin()
{
	wclear(calendarwin);
	box(calendarwin, 0, 0);
	mvwprintw(calendarwin, 0, 1, "%s %d", get_month_name(working_month), working_year);
	mvwprintw(calendarwin, 1, 2, "S  M  T  W  T  F  S");
	
	for(int d = 1, y = 2, x = first_day_offset; d <= get_days_in_month(working_month); d++)
	{
		if(d == get_current_day() && working_month == get_current_month() && working_year == get_current_year())
			wattron(calendarwin, COLOR_PAIR(7));
		else
			wattroff(calendarwin, COLOR_PAIR(7));
		
		mvwprintw(calendarwin, y, x * 3 + 1, "%2d", d);
		if(++x > 6)
		{
			y++;
			x=0;
		}
	}
	wrefresh(calendarwin);
}

void ui_draw_eventswin_border()
{
	wclear(eventswin);
	for(int y = 1; y < 6; y++)
	{	
		mvwhline(eventswin, events_hfactor * y, 0, ACS_HLINE, events_w);
	}
	for(int x = 1; x < 7; x++)
	{
		mvwvline(eventswin, 0, events_wfactor * x, ACS_VLINE, events_h);
	}
	box(eventswin, 0, 0);
	for (int x = 0; x < 7; x++)
	{
		mvwprintw(eventswin, 0, x * events_wfactor + 1, "%s", get_day_name(x));
	}
}

void ui_draw_eventswin_days()
{
	for(int day = 1, y = 1, x = first_day_offset; day <= get_days_in_month(working_month); day++)
	{
		if(day == selected_day)
			wattron(eventswin, A_REVERSE);
		else if(day == get_current_day() && working_month == get_current_month() && working_year == get_current_year())
			wattron(eventswin, COLOR_PAIR(7));
		
		mvwprintw(eventswin, y, 1 + x * events_wfactor, "%*d", events_wfactor - 1, day);
		if(day == 1)
			mvwprintw(eventswin, y, x * events_wfactor + 1, "%*s", events_wfactor - 3, get_mon_name(working_month));
		
		if(++x > 6)
		{
			y += events_hfactor;
			x = 0;
		}
		wattroff(eventswin, A_REVERSE);
		wattroff(eventswin, COLOR_PAIR(7));
	}
	wrefresh(eventswin);
}

void ui_draw_eventswin_calevents(calendar_t cal)
{
	vector(event_t) events = cal.events;

	for(int i = 0; i <= vector_size(events); i++)
	{
		wattron(eventswin, COLOR_PAIR(1));
		if(events[i].month == working_month + 1)
		{
			int day_pos = events[i].day - 1 + first_day_offset;

			int y = day_pos / 7;
			int x = day_pos % 7;
			y = y * events_hfactor + 2;
			x = x * events_wfactor + 1;

			while(mvwinch(eventswin, y, x) != ' ') y++; // Move down if an event was already printed here
			mvwprintw(eventswin, y, x, "%s", events[i].name);
		}
		wattroff(eventswin, COLOR_PAIR(1));
	}
}

void ui_promptwin_echo(int key)
{
	mvwprintw(promptwin, 0, 0, "%c - ", key);
	switch(key)
	{
		case 100: // d
		mvwprintw(promptwin, 0, 4, "next-day");
		break;
		case 68: // D
		mvwprintw(promptwin, 0, 4, "prev-day");
		break;
		case 119: // w
		mvwprintw(promptwin, 0, 4, "next-week");
		break;                
		case 87: // W         
		mvwprintw(promptwin, 0, 4, "prev-week");
		break;               
		case 110: // n
		mvwprintw(promptwin, 0, 4, "new: [c]alendar, [e]vent");
		break;
		case 113: // q        
		mvwprintw(promptwin, 0, 4, "Are you sure?");
		break;               
		default:             
		mvwprintw(promptwin, 0, 0, "cal version 0.01 - type '?' for help");
	}
	wclrtoeol(promptwin);
	wrefresh(promptwin);
}