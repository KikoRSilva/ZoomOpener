#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_CLASSES_PER_DAY 5
#define DAYS 7

typedef struct Class {
    char* name;
    int start;
    int end;
    char* link;
    char* password;
} Class_t;

typedef struct Day {
    char * weekday;
    Class_t * classes[MAX_CLASSES_PER_DAY];
} Day_t;

typedef struct Week {
    Day_t * days[DAYS];
} Week_t;

Week_t * initWeek();
Day_t * initDay();
Class_t * initClass();

