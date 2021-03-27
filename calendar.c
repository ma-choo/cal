#include <stdlib.h>
#include <string.h>

#include "calendar.h"

calendar_t calendar_init(char *name)
{
	calendar_t *cal = malloc(sizeof(calendar_t));
	strcpy(cal->name, name);
	cal->events = NULL;
	cal->hidden = 0;
	return *cal;
}

void cal_add_event(calendar_t cal, event_t ev)
{
	vector_push_back(cal.events, ev);
}