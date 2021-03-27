#ifndef CALENDARMATH_H
#define CALENDARMATH_H

static char *month_name[12];
static char *mon_name[12];
static char *day_name[7];
static int days_in_month[12];

char *get_month_name(int i);
char *get_mon_name(int i);
char *get_day_name(int i);
int get_days_in_month(int i);

void determine_leap_year(int year);
int zeller(int month, int year);

#endif