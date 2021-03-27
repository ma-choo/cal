#include <time.h>

static struct tm *current_time;

static int current_day, current_month, current_year;

void init_current_time()
{
	time_t s, val = 1;
	s = time(NULL);
	current_time = localtime(&s);
	
	current_day = current_time->tm_mday;
	current_month = current_time->tm_mon;
	current_year = current_time->tm_year + 1900;
}

int get_current_day()
{
    return current_day;
}

int get_current_month()
{
    return current_month;
}

int get_current_year()
{
    return current_year;
}