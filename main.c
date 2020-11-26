/*
* Custom Zoom Opener - 11/2020
* This program opens and process your schedule. Then opens automatically your classes by processing the current time and knowing the current class.
* Author: Francisco Ribeiro e Silva
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "parsing.h"

#define DEBUG 0 // '0' no debug or '1' debug
#define TRUE 1

char* week_day;
int hour;
int minute;

void parseError(char* text) {
	fprintf(stderr, "%s", text);
	exit(EXIT_FAILURE);
}

void processSchedule(FILE* file, Week_t * week) {

	char *token, *classes, *class;
	char line[200];	
	int i = 0; 		// Monday = 0, Tuesday = 1 ...

	while (fgets(line, sizeof(line)/sizeof(char), file) != NULL && i < DAYS) {

		int j = 0;

		if (DEBUG)
			printf("(PROCESSSCHEDULE) LINE: %s\n", line);

		token = strtok(line, "=");
		strcpy(week->days[i]->weekday, token);
		classes = strtok(NULL, "=");
		class = strtok(classes, ",");
		while (class != NULL && j < MAX_CLASSES_PER_DAY) {
			strcpy(week->days[i]->classes[j++]->name, class);
;			class = strtok(NULL, ",");
		}
		i++;
	}
}

char * getDayFile(Week_t * week, int day) {
	char * filename = malloc(sizeof(char) * 100);
	// strcpy(filename, "~/Developments/ZoomOpener/src/");
	sprintf(filename,"/home/francisco/Developments/ZoomOpener/src/%s.txt",week->days[day]->weekday);
	if (DEBUG)
		printf("GETDAYFILE) filename: %s\n", filename);
	if (DEBUG) {
		printf("(GETDAYFILE) day: %d\n", day);
		printf("(GETCLASSFILE) current: %s\n", week->days[day]->weekday);
	}

	// char* current_week_day = week->days[day]->weekday;
	// strcat(filename, current_week_day);
	// strcat(filename, ".txt");
	return filename;
}


int getClassNumber(char *name, Week_t * week, int weekday) {
	if (DEBUG)
		printf("(GETCLASSNUMBER) name: %s\n", name);
	for (int i = 0; i < MAX_CLASSES_PER_DAY; i++) {
		if (DEBUG)
			printf("(GETCLASSNUMBER) name: %s == classname: %s\n", name, week->days[weekday]->classes[i]->name);
		if (strcmp(name, week->days[weekday]->classes[i]->name) >= 0) {
			if (DEBUG)
				printf("(GETCLASSNUMBER) Encontrei uma classe com o mesmo nome! O seu number: %d\n", i);
			return i;
		}			
	}
	return -1;
}


int processClasses(Week_t * week, struct tm * ptm, FILE* file) {

	char line[200];
	char *class, *start, *end, *link, *pswd;
	int current_weekday = ptm->tm_wday;
	int current_hour = ptm->tm_hour;
	int current_minute = ptm->tm_min;

	if (DEBUG) {
		printf("==========================\n");
		printf("(PROCESSCLASSES) LET'S PROCESS\n");
	}

	while (fgets(line, sizeof(line)/sizeof(char), file) != NULL) {

		if (DEBUG)
			printf("(PROCESSCLASSES) NEW LINE\n");

		class = strtok(line, "|");
		start = strtok(NULL, "|");
		end = strtok(NULL, "|");
		link = strtok(NULL, "|");
		pswd = strtok(NULL, "|");

		if(DEBUG) {
			printf("==========================\n");
			printf("(PROCESSCLASSES) Class: %s\n", class);
			printf("(PROCESSCLASSES) Start: %s\n", start);
			printf("(PROCESSCLASSES) End: %s\n", end);
		}

		char* start_hour_c = strtok(start, ":");
		int start_hour = atoi(start_hour_c);
		char* start_minute_c = strtok(NULL, ":");
		int start_minute = atoi(start_minute_c);
		// char* start_second_c = strtok(NULL, ":");
		// int start_second = atoi(start_second_c);

		if (DEBUG) {
			printf("==========================\n");
			printf("(PROCESSCLASSES) PARSING START HOUR:MINUTE\n");
			printf("(PROCESSCLASSES) Start hour: %d\n", start_hour);
			printf("(PROCESSCLASSES) Start minute: %d\n", start_minute);
		}

		char* end_hour_c = strtok(end, ":");
		int end_hour = atoi(end_hour_c);
		char* end_minute_c = strtok(NULL, ":");
		int end_minute = atoi(end_minute_c);
		// char* end_second_c = strtok(NULL, ":");
		// int end_second = atoi(end_second_c);

		if (DEBUG) {
			printf("==========================\n");
			printf("(PROCESSCLASSES) PARSING END HOUR:MINUTE\n");
			printf("(PROCESSCLASSES) End hour: %d\n", end_hour);
			printf("(PROCESSCLASSES) End minute: %d\n", end_minute);
		}

		if ((current_hour == start_hour && current_minute >= start_minute) || (current_hour > start_hour && 
			(current_hour < end_hour || (current_hour == end_hour && current_minute < end_minute)))) {

			if (DEBUG) {
				printf("==========================\n");
				printf("(PROCESSCLASSES) FOUND ONE\n");
			}

			if (DEBUG) {
				printf("(PROCESSCLASSES) Link: %s\n", link);
				printf("(PROCESSCLASSES) pswd: %s\n", pswd);
			}

			int class_number = getClassNumber(class, week, current_weekday);
			if (DEBUG)
				printf("(PROCESSCLASSES) ANTES link: %s & password: %s\n", week->days[current_weekday]->classes[class_number]->link, week->days[current_weekday]->classes[class_number]->password);
			strcpy(week->days[current_weekday]->classes[class_number]->link, link);
			if (DEBUG)
				printf("(PROCESSCLASSES) DEPOIS link: %s & password: %s\n", week->days[current_weekday]->classes[class_number]->link, week->days[current_weekday]->classes[class_number]->password);
			if (pswd && !pswd[0])
				strcpy(week->days[current_weekday]->classes[class_number]->password, pswd);
			if (DEBUG)
				printf("link: %s & password: %s\n", week->days[current_weekday]->classes[class_number]->link, week->days[current_weekday]->classes[class_number]->password);

			return class_number;
		}
	}
	return -1;
}

void openClass(Week_t * week, struct tm * ptm, int class_number) {
	char buf[1024];
	sprintf(buf, "xdg-open %s", week->days[ptm->tm_wday]->classes[class_number]->link);
	system(buf);	
}

int main() {

	// get current time
	time_t rawtime = time(NULL);
	if (rawtime == -1)
		parseError("A função time() falhou!\n");
	struct tm *ptm = localtime(&rawtime);
	if (ptm == NULL)
		parseError("A função localtime() falho\n");
	
	// eh fim de semana -> termina o programa
	if (ptm->tm_wday >= 6) {
		fprintf(stdout, "É fim de semana! Não há aulas!\n");
		exit(EXIT_SUCCESS);
	}

	FILE* horario_f;

	horario_f = fopen("/home/francisco/Developments/ZoomOpener/src/HORARIO.txt", "r");

	if (horario_f == NULL)
		parseError("Não abriu o ficheiro HORARIO.txt\n");
	
	Week_t * week = initWeek();

	processSchedule(horario_f, week);

	char* day_file;
	day_file = getDayFile(week, ptm->tm_wday);

	if (DEBUG)
		printf("day_file: %s\n", day_file);
	
	FILE* day_f = fopen(day_file, "r");

	if (day_f == NULL)
		parseError("Não abriu o ficheiro deste dia\n");

	int class_number = processClasses(week, ptm, day_f);
	if (class_number == -1) {
		fprintf(stdout, "Não estás no período de aulas!\n");
		exit(EXIT_SUCCESS);
	}
	openClass(week, ptm, class_number);
	free(week);
	free(day_file);
	fclose(day_f);
	fclose(horario_f);
	return 0;
}
