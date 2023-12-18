#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define the maximum number of events and the maximum length of an event description
#define MAX_EVENTS 100
#define MAX_DESCRIPTION_LENGTH 256
#define FILE_NAME "calendar.txt"

typedef struct{
  int day;
  int month;
  int year;
  int start_time;
  int end_time;
  char description[MAX_DESCRIPTION_LENGTH];
} Event;

// Declare functions
void add_event (Event events[], int *event_count);
void display_events (const Event events[], int event_count);
void search_events (const Event events[], int event_count);
void edit_event (Event events[], int event_count);
void delete_event (Event events[], int *event_count);
void load_events (Event events[], int *event_count);
void save_events (const Event events[], int event_count);

int main () {
  Event events[MAX_EVENTS];
  int event_count = 0;

  // Load events from file
  load_events (events, &event_count);

  int choice;
  bool exit_program = false;

  while (!exit_program) {
      printf ("\nCalendar Menu:\n");
      printf ("1. Add event\n");
      printf ("2. Display events\n");
      printf ("3. Search events\n");
      printf ("4. Edit event\n");
      printf ("5. Delete event\n");
      printf ("6. Exit\n");
      printf ("Enter your choice: ");
      scanf ("%d", &choice);
      getchar ();		// Consume newline character

      switch (choice) {
	case 1:
	  add_event (events, &event_count);
	  break;
	case 2:
	  display_events (events, event_count);
	  break;
	case 3:
	  search_events (events, event_count);
	  break;
	case 4:
	  edit_event (events, event_count);
	  break;
	case 5:
	  delete_event (events, &event_count);
	  break;
	case 6:
	  exit_program = true;
	  break;
	default:
	  printf ("Invalid choice. Please try again.\n");
	}
    }

  // Save events to file
  save_events (events, event_count);

  return 0;
}

void add_event (Event events[], int *event_count) {
    Event new_event;
    printf ("Enter event date (DD MM YYYY): ");
    scanf ("%d %d %d", &new_event.day, &new_event.month, &new_event.year);
    getchar ();			// Consume newline character
    printf ("Enter event start time (HHMM): ");
    scanf ("%d", &new_event.start_time);
    printf ("Enter event end time (HHMM): ");
    scanf ("%d", &new_event.end_time);
    getchar ();			// Consume newline character
    printf ("Enter event description: ");
    fgets (new_event.description, MAX_DESCRIPTION_LENGTH, stdin);
    new_event.description[strcspn (new_event.description, "\n")] = 0;	// Remove newline character

    events[*event_count] = new_event;
    (*event_count)++;
    printf ("Event added successfully.\n");
}

void display_events (const Event events[], int event_count) {
    printf ("\nEvents:\n");
    for (int i = 0; i < event_count; i++) {
        printf ("%02d/%02d/%04d %04d-%04d: %s\n",
	      events[i].day, events[i].month, events[i].year,
	      events[i].start_time, events[i].end_time,
	      events[i].description);
    }
}

void search_events (const Event events[], int event_count) {
    int choice;
    printf ("1. Search by date\n");
    printf ("2. Search by keyword\n");
    printf ("Enter your choice: ");
    scanf ("%d", &choice);
    getchar ();			// Consume newline character

    if (choice == 1) {
        int day, month, year;
        printf ("Enter date (DD MM YYYY): ");
        scanf ("%d %d %d", &day, &month, &year);
        getchar ();		// Consume newline character

        printf ("\nEvents on %02d/%02d/%04d:\n", day, month, year);
        for (int i = 0; i < event_count; i++) {
	    if (events[i].day == day && events[i].month == month
	        && events[i].year == year) {
	        printf ("%04d-%04d: %s\n", events[i].start_time,
		            events[i].end_time, events[i].description);
	    }
	}
    }
  else if (choice == 2) {
        char keyword[MAX_DESCRIPTION_LENGTH];
        printf ("Enter keyword: ");
        fgets (keyword, MAX_DESCRIPTION_LENGTH, stdin);
        keyword[strcspn (keyword, "\n")] = 0;	// Remove newline character

        printf ("\nEvents containing \"%s\":\n", keyword);
        for (int i = 0; i < event_count; i++) {
	    if (strstr (events[i].description, keyword) != NULL) {
	        printf ("%02d/%02d/%04d %04d-%04d: %s\n",
		          events[i].day, events[i].month, events[i].year,
		          events[i].start_time, events[i].end_time,
		          events[i].description);
	  }
	  }
    }
  else
    {
        printf ("Invalid choice. Please try again.\n");
    }
}

void edit_event (Event events[], int event_count) {
    int index;
    printf ("Enter event index (1-%d) to edit: ", event_count);
    scanf ("%d", &index);
    getchar ();			// Consume newline character

    if (index >= 1 && index <= event_count) {
        index--;			// Adjust index for zero-based array
        printf ("Editing event:\n");
        printf ("%02d/%02d/%04d %04d-%04d: %s\n",
	            events[index].day, events[index].month, events[index].year,
	            events[index].start_time, events[index].end_time,
	            events[index].description);

        printf ("Enter new event date (DD MM YYYY): ");
        scanf ("%d %d %d", &events[index].day, &events[index].month,&events[index].year);
        getchar ();		// Consume newline character
        printf ("Enter new event start time (HHMM): ");
        scanf ("%d", &events[index].start_time);
        printf ("Enter new event end time (HHMM): ");
        scanf ("%d", &events[index].end_time);
        getchar ();		// Consume newline character
        printf ("Enter new event description: ");
        fgets (events[index].description, MAX_DESCRIPTION_LENGTH, stdin);
               events[index].description[strcspn (events[index].description, "\n")] = 0;	// Remove newline character

        printf ("Event updated successfully.\n");
    }
    else
    {
        printf ("Invalid event index.\n");
    }
}

void delete_event (Event events[], int *event_count) {
    int index;
    printf ("Enter event index (1-%d) to delete: ", *event_count);
    scanf ("%d", &index);
    getchar ();			// Consume newline character

    if (index >= 1 && index <= *event_count) {
        index--;			// Adjust index for zero-based array
        printf ("Deleting event:\n");
        printf ("%02d/%02d/%04d %04d-%04d: %s\n",
	            events[index].day, events[index].month, events[index].year,
	            events[index].start_time, events[index].end_time,
	            events[index].description);


      // Shift the remaining events to fill the deleted event's position
        for (int i = index; i < *event_count - 1; i++) {
	         events[i] = events[i + 1];
	}
        (*event_count)--;
        printf ("Event deleted successfully.\n");
    }
  else
    {
        printf ("Invalid event index.\n");
    }

}

void load_events (Event events[], int *event_count) {
    FILE *file = fopen (FILE_NAME, "r");
    if (file == NULL) {
        printf
	("No existing calendar data found. Starting with an empty calendar.\n");
        return;
    }

    while (fscanf(file, "%d %d %d %d %d %[^\n]", &events[*event_count].day,
	       &events[*event_count].month, &events[*event_count].year,
	       &events[*event_count].start_time, &events[*event_count].end_time,
	       events[*event_count].description) == 6)
    {
        (*event_count)++;
    }
    fclose (file);

}

void save_events (const Event events[], int event_count) {
    FILE *file = fopen (FILE_NAME, "w");
    if (file == NULL) {
        printf ("Error: Unable to save calendar data.\n");
        return;
    }

    for (int i = 0; i < event_count; i++) {
        fprintf (file, "%d %d %d %d %d %s\n", events[i].day, events[i].month,
	             events[i].year, events[i].start_time, events[i].end_time,
	             events[i].description);
    }
    fclose (file);

}
