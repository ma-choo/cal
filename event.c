#include <stdlib.h>
#include <string.h>
#include "event.h"

event_t event_init(char *name, int day, int month, int year)
{
	event_t *ev = malloc(sizeof(event_t));
	strcpy(ev->name, name);
	ev->day = day;
	ev->month = month;
	ev->year = year;
	ev->completed = 0;
	return *ev;
}