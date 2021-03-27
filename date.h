#ifndef DATE_H
#define DATE_H

#include <time.h>

static struct tm *current_time;

static int current_day, current_month, current_year;

void init_current_time();

int get_current_day();
int get_current_month();
int get_current_year();
#endif