Calendar Program
----------------

This is a calendar program that can be used to manage events accross different dates.

Features:
---------
1. Add event
2. Display events
3. Search events by date or keyword
4. Edit event
5. Delete event
6. Exit

Compiling and Running:
----------------------
To compile the program, have a C compiler installed. Save the provided calendar program code in a file named "calendar.c".

Open a terminal/command prompt, find the directory where the "calendar.c" file is located, and execute the following commands:

gcc -o calendar calendar.c
./calendar (or calendar.exe on Windows)

This compiles the code and creates and executable called "calendar" (or "calendar.exe" on Windows). Run the executable to start the program.

Usage Example:
--------------
1. Compile and run the program as described in the "Compiling and Running" section.
2. Add an event by selecting option "1" and entering the event details.
3. Display the events by selecting option "2".
4. Search for events by selecting option "3" and following the prompts.
5. Edit an event by selecting option "4" and following the prompts.
6. Delete an event by selecting option "5" and following the prompts.
7. Exit the program by selecting option "6".

-----
The program stores events in a file named "calendar.txt" in the same directory as the executable. 
The events are loaded from this file when the program starts and saved to the file when the program exits.
