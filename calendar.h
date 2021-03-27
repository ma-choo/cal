#ifndef CALENDAR_H
#define CALENDAR_H

#include "cvector.h"
#include "event.h"

typedef struct calendar
{
	char name[32];
	vector(event_t) events;
	int hidden;
} calendar_t;

calendar_t calendar_init(char *name);
void cal_add_event(calendar_t cal, event_t ev);

#endif