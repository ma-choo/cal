#ifndef UI_H
#define UI_H

static int screen_h, screen_w;
static int calendar_h, calendar_w;
static int events_h, events_w, events_hfactor, events_wfactor;

static int selected_day, working_month, working_year;
static int first_day_offset;

static WINDOW *calendarwin, *eventswin, *promptwin;

void ui_init_working_date();
int ui_change_working_date(int i);

void ui_start_color_pairs();
void ui_init_windows();
void ui_del_windows();

void ui_draw_calendarwin();

void ui_draw_eventswin_border();
void ui_draw_eventswin_days();
void ui_draw_eventswin_calevents(calendar_t cal);

void promptwin_echo(int key);

#endif