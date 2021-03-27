#ifndef EVENT_H
#define EVENT_H

typedef struct event
{
	char name[32];
	int day;
	int month;
	int year;
	int completed;
} event_t;

event_t event_init(char *name, int day, int month, int year);

#endif