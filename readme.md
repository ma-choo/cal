
jenda
=====
A Google Calendar-esque console application.

Building
--------
This requires the PDCurses library to build on Windows. It should build with regular ncurses on Linux, too.
https://pdcurses.org/
Add PDCurses to your gcc library. Until I can figure out makefiles, just run this at the terminal:

	gcc jenda.c greg.c date.c ui.c calendar.c event.c -lpdcurses -fno-common
	
Roadmap
-------
* Show multiple events in one day.
* Show events from the previous month and next month in the events window.
* Read and write calendar and event files.
	* Implement .ical format compatibility.
* Dynamically resize windows on terminal resize.