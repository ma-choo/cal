
Cal
=====
A Google Calendar-esque console application using Curses.

Building
--------
Build with standard Curses library on Linux or PDCurses library on Windows.
https://pdcurses.org/

Linux:

	gcc jenda.c greg.c date.c ui.c calendar.c event.c -lpdcurses -fno-common
Windows:

	gcc jenda.c greg.c date.c ui.c calendar.c event.c -lpdcurses -fno-common
	
Roadmap
-------
* Show multiple events in one day.
* Show events from the previous month and next month in the events window.
* Read and write calendar and event files.
	* Implement .ical format compatibility.
* Dynamically resize windows on terminal resize.
