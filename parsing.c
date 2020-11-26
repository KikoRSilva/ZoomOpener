#include "parsing.h"

Week_t * initWeek() {
	Week_t * week = malloc(sizeof(Week_t));
	for(int i = 0; i < DAYS; i++){
		week->days[i] = initDay();
	}
    return week;
}

Day_t * initDay() {
	Day_t *day = malloc(sizeof(Day_t));
	day->weekday = malloc(sizeof(char));
    for(int i = 0; i< MAX_CLASSES_PER_DAY; i++) {
        day->classes[i] = initClass();
    }
	return day;
}

Class_t * initClass() {
    Class_t * class = malloc(sizeof(Class_t));
    class->name = malloc(sizeof(char)*10);
    class->start = 0;
    class->end = 0;
    class->link = malloc(sizeof(char)*1024);
    class->password = malloc(sizeof(char)*200);
    return class;
}