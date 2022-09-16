//  CITS2002 Project 1 2022
//  Student1:   22982458   GOPCEVIC   NICOLAS
//  Student2:   21968333   ADLER   HARRY

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


#define MAX_LINES 100
#define MAX_LEN 100


struct Time_proc {
	char minute[50];	// 
	char hour[50];		// struct to hold all of the
	char day[50];		// time and date data when reading
	char month[50];		// from strings.
	char day_of_week[50];	//
};


struct Time {
	int minute;		// 
	int hour;		// struct to hold all of the
	int day;		// time and date data.
	int month;		//
	int day_of_week;
	int days_in_month;
};

struct Process {
	char  name[40];			// process name
	int   estimate;			// process length in minutes
   	int num_lines;			// number of processes
	struct Time_proc time_str;	// holding minutes, hours, day, month, day of week, days in month
	int num_calls;			// number of times process is invoked
};

struct Estimate {
	int minute;			// minutes left over for process
	int hour;			// hours left over for process
	int day;			// days left over for process
};

struct Concurrent {
	int arr[20];		// contains all processes running on current time tick
};

// read both files and store data in Process struct
struct Process * file_processing(char *crontab, char *estimates) {

	// storage for lines from file
	char cron_data[MAX_LINES][MAX_LEN];
	
	// open file
	FILE   *cron_file = fopen(crontab, "r");
	
	//  check if file was opened successfully
	if(cron_file == NULL) {
		printf( "cannot open file '%s'\n", crontab);
		exit(EXIT_FAILURE);
	}
	
	int cron_line = 0;
	
	// check for EOF or error while reading
	while (!feof(cron_file) && !ferror(cron_file)) {
		// check if number of lines < MAX_LINES
		if (fgets(cron_data[cron_line], MAX_LEN, cron_file) != NULL) {
			// increment line
			cron_line++;
		}
	}
	
	//  close file
	fclose(cron_file);
	
	// clean lines
	char cron_processes[MAX_LINES][MAX_LEN];
	
	int cron_clean_line = 0;
	// cleaning out comments
	for (int i=0;i<cron_line;i++) {
		for (int j = 0; j < MAX_LINES; j++) {
			if (cron_data[i][j] == ' ') {
				continue;
			}
			else if (cron_data[i][j] == '#') {
				break;
			}
			else if (cron_data[i][j] == '\n') {
  			        strcpy(cron_processes[cron_clean_line], cron_data[i]);
				cron_clean_line++;
			}
		}
	}
	// checking for empty lines in crontab-file
	for (int i=0;i<cron_clean_line;i++) {
		if (strlen(cron_processes[i]) == 1) {
			printf("\nempty line found\n");
			exit(EXIT_FAILURE);
		}
	}
	
	char cron_times[cron_clean_line][100];
	for (int z=0;z<cron_clean_line;z++) {
  		cron_times[z][0] = '\0';
	}
	// collecting start times from crontab-file
	for (int z=0;z<cron_clean_line;z++) {
		int x = 0;
		int space_counter = 0;
		while ( (cron_processes[z][x] != '\0') && (space_counter < 5) ) {
			if ( (cron_processes[z][x] == ' ') || (cron_processes[z][x] == '\t') ) {
				if (x==0) {
					x++;
					continue;
				}
				else if ( (cron_processes[z][x-1] != ' ') && (cron_processes[z][x-1] != '\t') ) {
					strcat(cron_times[z], "/");
					space_counter++;
					x++;
				}
				else if ( (cron_processes[z][x-1] == ' ' ) || (cron_processes[z][x-1] == '\t') ) {
					x++;
				}
			}
			else {
				strncat(cron_times[z], &cron_processes[z][x], 1);
				x++;
			}
    		}
    	}
	    	
    	char cron_names[cron_clean_line][40];
    	for (int z=0;z<cron_clean_line;z++) {
    		cron_names[z][0] = '\0';
    	}
    	// collecting process names from crontab-file
	for (int z=0;z<cron_clean_line;z++) {
		int x = 0;
		int space_counter = 0;
		while ( (cron_processes[z][x] != '\n') ) {
			if (space_counter == 5) {
				if ( (cron_processes[z][x] == ' ') || (cron_processes[z][x] == '\t') ) {
					if ( (cron_processes[z][x-1] != ' ') && (cron_processes[z][x-1] != '\t') ) {
						space_counter++;
						x++;
					}
					else {
						x++;
					}
				}
				else {
					strncat(cron_names[z], &cron_processes[z][x], 1);
					x++;
				}
			}
			else {
				if ( (cron_processes[z][x] == ' ') || (cron_processes[z][x] == '\t') ) {
					if (x==0) {
						x++;
						continue;
					}
					else if ( (cron_processes[z][x-1] != ' ') && (cron_processes[z][x-1] != '\t') ) {
						space_counter++;
						x++;
					}
					else if ( (cron_processes[z][x-1] == ' ' ) || (cron_processes[z][x-1] == '\t') ) {
						x++;
					}
				}
				else {
					x++;
				}
			}
    		}
    	}
	
	// storage for lines from file
	char esti_data[MAX_LINES][MAX_LEN];
	
	// open file
	FILE   *esti_file = fopen(estimates, "r");
	
	//  check if file was opened successfully
	if(esti_file == NULL) {
		printf( "cannot open file '%s'\n", estimates);
		exit(EXIT_FAILURE);
	}
	
	int esti_line = 0;
	
	// check for EOF or error while reading
	while (!feof(esti_file) && !ferror(esti_file)) {
		// check if number of lines < MAX_LINES
		if (fgets(esti_data[esti_line], MAX_LEN, esti_file) != NULL) {
			// increment line
			esti_line++;
		}
	}
	
	//  close file
	fclose(esti_file);

	// clean lines
	char esti_processes[MAX_LINES][MAX_LEN];
	
	int esti_clean_line = 0;
	// cleaning comments from estimates
	for (int i=0;i<esti_line;i++) {
		for (int j = 0; j < MAX_LINES; j++) {
			if (esti_data[i][j] == ' ') {
				continue;
			}
			else if (esti_data[i][j] == '#') {
				break;
			}
			else if (esti_data[i][j] == '\n') {
  			        strcpy(esti_processes[esti_clean_line], esti_data[i]);
				esti_clean_line++;
			}
		}
	}
	
	char esti_names[esti_clean_line][40];
    	for (int z=0;z<esti_clean_line;z++) {
    		esti_names[z][0] = '\0';
    	}
    	// collecting process names from estimates
	for (int z=0;z<esti_clean_line;z++) {
		int x = 0;
		int space_counter = 0;
		while ( (space_counter < 1) ) {
			if ( (esti_processes[z][x] == ' ') || (esti_processes[z][x] == '\t') ) {
				x++;
				space_counter++;
			}
			else {
				strncat(esti_names[z], &esti_processes[z][x], 1);
				x++;
			}
		}
	}
	
	char esti_times[esti_clean_line][40];
    	for (int z=0;z<esti_clean_line;z++) {
    		esti_times[z][0] = '\0';
    	}
    	// collecting estimates
	for (int z=0;z<esti_clean_line;z++) {
		int x = 0;
		int space_counter = 0;
		while ( (esti_processes[z][x] != '\n') ) {
			if (space_counter >= 1) {
				if ( (esti_processes[z][x] == ' ') || (esti_processes[z][x] == '\t') ) {
					if ( (esti_processes[z][x-1] != ' ') && (esti_processes[z][x-1] != '\t') ) {
						space_counter++;
						x++;
					}
					else {
						x++;
					}
				}
				else {
					strncat(esti_times[z], &esti_processes[z][x], 1);
					x++;
				}
			}
			else {
				if ( (esti_processes[z][x] == ' ') || (esti_processes[z][x] == '\t') ) {
					if ( (esti_processes[z][x-1] != ' ') && (esti_processes[z][x-1] != '\t') ) {
						space_counter++;
						x++;
					}
					else {
						x++;
					}
				}
				else {
					x++;
				}
			}
		}
	}
	// allocating memory for an array of structs and initialising below
	struct Process *all_proc = malloc(sizeof(struct Process) * cron_clean_line);
	
	for (int i=0;i<cron_clean_line;i++) {
		strcpy( all_proc[i].name, cron_names[i]);
		all_proc[i].num_lines = cron_clean_line;
		all_proc[i].num_calls = 0;
		all_proc[i].estimate = 0;
	}
	
	
	for (int i=0;i<cron_clean_line;i++) {
		all_proc[i].time_str.minute[0] = '\0';
		all_proc[i].time_str.hour[0] = '\0';
		all_proc[i].time_str.day[0] = '\0';
		all_proc[i].time_str.month[0] = '\0';
		all_proc[i].time_str.day_of_week[0] = '\0';
	}
		
	
	for (int i=0;i<cron_clean_line;i++) {
		char str[100];
		strcpy( str, cron_times[i]);
		
		char *ptr = strtok(str, "/");
		for (int j=0;j<strlen(ptr);j++) {
			strncat(all_proc[i].time_str.minute, &ptr[j], 1);
		} 
		int slash = 1;

		while(ptr != NULL && slash <= 4) {
			if (slash==1) {

				slash++;
				ptr = strtok(NULL, "/");
				for (int z=0;z<strlen(ptr);z++) {
					strncat(all_proc[i].time_str.hour, &ptr[z], 1);
				}
			}
			else if (slash==2) {

				slash++;
				ptr = strtok(NULL, "/");
				for (int z=0;z<strlen(ptr);z++) {
					strncat(all_proc[i].time_str.day, &ptr[z], 1);
				}
			}
			else if (slash==3) {

				slash++;
				ptr = strtok(NULL, "/");
				for (int z=0;z<strlen(ptr);z++) {
					strncat(all_proc[i].time_str.month, &ptr[z], 1);
				}
			}
			else if (slash==4) {

				slash++;
				ptr = strtok(NULL, "/");
				for (int z=0;z<strlen(ptr);z++) {
					strncat(all_proc[i].time_str.day_of_week, &ptr[z], 1);
				}	
			}
		}
	}	
		
	for (int i=0;i<cron_clean_line;i++) {
		for (int j=0;j<esti_clean_line;j++) {
			if (strcmp(all_proc[i].name, esti_names[j]) == 0) {
				all_proc[i].estimate = atoi(esti_times[j]);
			}
		}
	}
	// checking if crontab process is found in estimates-file
	for (int i=0;i<cron_clean_line;i++) {
		if (all_proc[i].estimate == 0) {
			printf("\n'%s' is an unknown command\n", all_proc[i].name);
			exit(EXIT_FAILURE);
		}
	}
	// cleaning out empty lines
	int p=5;
	while ( (p>(cron_clean_line)-1) && (p<400) ) {
		strcpy(all_proc[p].name, "0");
		all_proc[p].estimate = 0;
		all_proc[p].num_lines = 0;
		strcpy(all_proc[p].time_str.minute, "0");		
		strcpy(all_proc[p].time_str.hour, "0");
		strcpy(all_proc[p].time_str.day, "0");
		strcpy(all_proc[p].time_str.month, "0");
		strcpy(all_proc[p].time_str.day_of_week, "0");
		all_proc[p].num_calls = 0;
		p++;
	}
	
	return all_proc;
}
	 
// A utility function to provide the number of days from the command line argv[] input.
int getMonthDays(char *argv, int size) {
	
	int num = atoi(argv);
	
	bool isChar = false;
	
	bool isUp = false;
	
	bool isNum = false;

	for (int i=0;i<size;i++) {
		if (isalpha(argv[i]) != 0) {
			isChar = true;
		}
		if (isupper(argv[i]) != 0) {
			isUp = true;
		}
		if (isdigit(argv[i]) != 0) {
			isNum = true;
		}
	}

	if (isUp==true) {
		printf("\n'%s' is an invalid month\n", argv);
		exit(EXIT_FAILURE);
	}
	if ( (isNum==true) && (isChar==true) ) {
		printf("\n'%s' is an invalid month\n", argv);
		exit(EXIT_FAILURE);
	}
	
	if (isChar==true) {

		// do check for 3 letter abbreviation of month. eg. "feb".
		if (size == 3) {
			char str[3];
			int i = 0;
			
			while (argv[i]) { 
				str[i] = toupper(argv[i]);  
				i++; 
		    	}
		    	
		    	if (strcmp(str, "JAN") == 0)
				return 31;
			else if (strcmp(str, "FEB") == 0)	
				return 28;		
			else if (strcmp(str, "MAR") == 0)		
				return 31;
			else if (strcmp(str, "APR") == 0)
				return 30;
			else if (strcmp(str, "MAY") == 0)
				return 31;
			else if (strcmp(str, "JUN") == 0)
				return 30;
			else if (strcmp(str, "JUL") == 0)
				return 31;
			else if (strcmp(str, "AUG") == 0)
				return 31;
			else if (strcmp(str, "SEP") == 0)
				return 30;
			else if (strcmp(str, "OCT") == 0)
				return 31;
			else if (strcmp(str, "NOV") == 0)
				return 30;
			else if (strcmp(str, "DEC") == 0)
				return 31;
		}
		else {
			printf("\n'%s' is an invalid month\n", argv);
			exit(EXIT_FAILURE);
		}
	}
	else {
		// do check for numerial month. eg. "9".
		if ( (size == 1) || (size == 2) ) {
			if ( (0 > num) || (11 < num) ) {
				printf("\n'%i' is an invalid month\n", num);
				exit(EXIT_FAILURE);
			}
			else {
				switch (num) {          
				  case 0 :
				  	return 31;
				  case 1 :
				  	return 28;
				  case 2 :
				  	return 31;
				  case 3 :
				  	return 30;
				  case 4 :
				  	return 31;
				  case 5 :
				  	return 30;
				  case 6 :
				  	return 31;
				  case 7 :
				  	return 31;
				  case 8 :
				  	return 30;
				  case 9 :
				  	return 31;
				  case 10 :
				  	return 30;
				  case 11 :
				  	return 31;			  	
				}
			}
		}
		else {
			printf("\n'%s' is an invalid month\n", argv);
			exit(EXIT_FAILURE);
		}
	}
			
	return 0;
}

//A function to calculate the day of the week based on a given day/month/year.
int get_day_of_week(int d, int m, int y) {
	return (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
}

// A function that will tick through all the days of a given month argv[] by minute.
struct Time timeTick(struct Time time) {

	if (time.hour >= 24 || time.minute >= 60) {
		printf("This is not a valid time\n");
		exit(EXIT_FAILURE);
	}
	
	time.minute++;
	
	if (time.minute == 60) {
		time.hour++;
		time.minute = 0;
	}
	if (time.hour == 24) {
		time.day++;
		time.hour = 0;
	}
	if (time.day > time.days_in_month) {
		exit(EXIT_SUCCESS);
	}
	
	time.day_of_week = get_day_of_week(time.day, time.month+1, 2022);
	
	return time;
}

// A function to check command line inputs for strings, test if they are valid and convert to numerical representation.
struct Process * text_to_num(struct Process *processes) {
	
	for (int i=0;i<processes[i].num_lines;i++) {
		
		int size = strlen(processes[i].time_str.month);
		
		if (size >= 3) {
			
			if (strcmp(processes[i].time_str.month, "jan") == 0)
				strcpy(processes[i].time_str.month, "0");
			else if (strcmp(processes[i].time_str.month, "feb") == 0)	
				strcpy(processes[i].time_str.month, "1");		
			else if (strcmp(processes[i].time_str.month, "mar") == 0)		
				strcpy(processes[i].time_str.month, "2");
			else if (strcmp(processes[i].time_str.month, "apr") == 0)
				strcpy(processes[i].time_str.month, "3");
			else if (strcmp(processes[i].time_str.month, "may") == 0)
				strcpy(processes[i].time_str.month, "4");
			else if (strcmp(processes[i].time_str.month, "jun") == 0)
				strcpy(processes[i].time_str.month, "5");
			else if (strcmp(processes[i].time_str.month, "jul") == 0)
				strcpy(processes[i].time_str.month, "6");
			else if (strcmp(processes[i].time_str.month, "aug") == 0)
				strcpy(processes[i].time_str.month, "7");
			else if (strcmp(processes[i].time_str.month, "sep") == 0)
				strcpy(processes[i].time_str.month, "8");
			else if (strcmp(processes[i].time_str.month, "oct") == 0)
				strcpy(processes[i].time_str.month, "9");
			else if (strcmp(processes[i].time_str.month, "nov") == 0)
				strcpy(processes[i].time_str.month, "10");
			else if (strcmp(processes[i].time_str.month, "dec") == 0)
				strcpy(processes[i].time_str.month, "11");
			
			else {
				printf("\n'%s' is an invalid month\n", processes[i].time_str.month);
				exit(EXIT_FAILURE);
			}
		}
	}
	
	for (int i=0;i<processes[i].num_lines;i++) {
	
		int size = strlen(processes[i].time_str.day_of_week);
	
		bool isChar = false;
		
		bool isUp = false;
		
		bool isNum = false;

		for (int j=0;j<size;j++) {
			if (isalpha(processes[i].time_str.day_of_week[j]) != 0) {
				isChar = true;
			}
			if (isupper(processes[i].time_str.day_of_week[j]) != 0) {
				isUp = true;
			}
			if (isdigit(processes[i].time_str.day_of_week[j]) != 0) {
				isNum = true;
			}
		}
		
		if (isUp==true) {
			printf("\n'%s' is an invalid day of week\n", processes[i].time_str.day_of_week);
			exit(EXIT_FAILURE);
		}
		if ( (isNum==true) && (isChar==true) ) {
			printf("\n'%s' is an invalid day of week\n", processes[i].time_str.day_of_week);
			exit(EXIT_FAILURE);
		}
		
		if (isChar == true) {
			
			if (size == 3) {

				if (strcmp(processes[i].time_str.day_of_week, "sun") == 0)
					strcpy(processes[i].time_str.day_of_week, "0");
				else if (strcmp(processes[i].time_str.day_of_week, "mon") == 0)	
					strcpy(processes[i].time_str.day_of_week, "1");		
				else if (strcmp(processes[i].time_str.day_of_week, "tue") == 0)		
					strcpy(processes[i].time_str.day_of_week, "2");
				else if (strcmp(processes[i].time_str.day_of_week, "wed") == 0)
					strcpy(processes[i].time_str.day_of_week, "3");
				else if (strcmp(processes[i].time_str.day_of_week, "thu") == 0)
					strcpy(processes[i].time_str.day_of_week, "4");
				else if (strcmp(processes[i].time_str.day_of_week, "fri") == 0)
					strcpy(processes[i].time_str.day_of_week, "5");
				else if (strcmp(processes[i].time_str.day_of_week, "sat") == 0)
					strcpy(processes[i].time_str.day_of_week, "6");
			}
			else {
				printf("\n'%s' is an invalid day of the week\n", processes[i].time_str.day_of_week);
				exit(EXIT_FAILURE);
			}
			
		}
	}
	
	return processes;
}

//A function to count the number of times each process is called in a given minute.
struct Process * number_of_calls(struct Time time, struct Process *processes) {

	for (int i=0;i<processes[i].num_lines;i++) {
	
		if (strcmp(processes[i].name, "0") != 0 ) {
		
			if ( (time.day_of_week == atoi(processes[i].time_str.day_of_week)) || strcmp(processes[i].time_str.day_of_week, "*") == 0) {
			
				if ( (time.month == atoi(processes[i].time_str.month)) || strcmp(processes[i].time_str.month, "*") == 0) {
				
					if ( (time.day == atoi(processes[i].time_str.day)) || (strcmp(processes[i].time_str.day, "*") == 0) ) {
					
						if ( (time.hour == atoi(processes[i].time_str.hour)) || (strcmp(processes[i].time_str.hour, "*") == 0) ) {
						
							if ( (time.minute == atoi(processes[i].time_str.minute)) || (strcmp(processes[i].time_str.minute, "*") == 0) ) {
								processes[i].num_calls++;	
							}
						}
					}						  
				}
			}
		}
	}
	
	return processes;
}

//A function to check the validity of a given time layout in a struct time_str.
void time_error(struct Process *processes) {

	for (int i=0;i<processes[i].num_lines;i++) {
	
		int size_min = strlen(processes[i].time_str.minute);

		for (int j=0;j<size_min;j++) {
			if (isalpha(processes[i].time_str.minute[j]) != 0) {
				printf("\n'%s' is an invalid minute\n", processes[i].time_str.minute);
				exit(EXIT_FAILURE);
			}
		}
		
		int size_hour = strlen(processes[i].time_str.hour);

		for (int j=0;j<size_hour;j++) {
			if (isalpha(processes[i].time_str.hour[j]) != 0) {
				printf("\n'%s' is an invalid hour\n", processes[i].time_str.hour);
				exit(EXIT_FAILURE);
			}
		}
		
		int size_day = strlen(processes[i].time_str.day);

		for (int j=0;j<size_day;j++) {
			if (isalpha(processes[i].time_str.day[j]) != 0) {
				printf("\n'%s' is an invalid day\n", processes[i].time_str.day);
				exit(EXIT_FAILURE);
			}
		}
	
		if ( ( 0 > atoi(processes[i].time_str.minute) || atoi(processes[i].time_str.minute) > 59) && (strcmp(processes[i].time_str.minute, "*") != 0) ) {
			printf("\n'%s' is an invalid minute\n", processes[i].time_str.minute);
			exit(EXIT_FAILURE);
		}
		if ( ( 0 > atoi(processes[i].time_str.hour) || atoi(processes[i].time_str.hour) > 23) && (strcmp(processes[i].time_str.hour, "*") != 0) ) {
			printf("\n'%s' is an invalid hour\n", processes[i].time_str.hour);
			exit(EXIT_FAILURE);
		}
		if ( ( 1 > atoi(processes[i].time_str.day) || atoi(processes[i].time_str.day) > 31) && (strcmp(processes[i].time_str.day, "*") != 0) ) {
			printf("\n'%s' is an invalid day\n", processes[i].time_str.day);
			exit(EXIT_FAILURE);
		}
		if ( ( 0 > atoi(processes[i].time_str.month) || atoi(processes[i].time_str.month) > 11) && (strcmp(processes[i].time_str.month, "*") != 0) ) {
			printf("\n'%s' is an invalid month\n", processes[i].time_str.month);
			exit(EXIT_FAILURE);
		}
		if ( ( 0 > atoi(processes[i].time_str.day_of_week) || atoi(processes[i].time_str.day_of_week) > 6) && (strcmp(processes[i].time_str.day_of_week, "*") != 0) ) {
			printf("\n'%s' is an invalid day of week\n", processes[i].time_str.day_of_week);
			exit(EXIT_FAILURE);
		}
		
		if (strcmp(processes[i].time_str.month, "*") != 0) {
			if ( atoi(processes[i].time_str.day) > getMonthDays(processes[i].time_str.month, strlen(processes[i].time_str.month)) ) {
				printf("\n'%s' is an invalid day for given month: '%s'\n", processes[i].time_str.day, processes[i].time_str.month);
				exit(EXIT_FAILURE);
			}
		}
	}
}

//A function to convert a given estimate in total minutes into struct broken down into days, hours and minutes.
struct Estimate estimate_to_time(int estimate, int days_in_month) {
	
	struct Estimate time_left;
	
	
	if (estimate < (60)) {
		time_left.minute = estimate;
		time_left.hour = 0;
		time_left.day = 0;
	}
	if ( (estimate < (60*24)) && (estimate > 60) ) {
		time_left.hour = ( estimate / 60 );
		time_left.minute = ( estimate - (time_left.hour*60) );
		time_left.day = 0;
	}
	if ( (estimate < (60*24*days_in_month)) && (estimate > (60*24)) ) {		
		time_left.day = ( estimate / (60*24) );
		time_left.hour = ( (estimate - (time_left.day*24*60)) / 60 );
		time_left.minute = ( estimate - ( (time_left.day*24*60) + (time_left.hour*60) ) );
	}
	if ( estimate > (60*24*days_in_month) ) {
		printf("\n '%i' is too large of an estimate for given month\n", estimate);
		exit(EXIT_FAILURE);
	}
	
	return time_left;
}

//A function to check the number of concurrently running processes in a given minute.
struct Concurrent concurrent_count(struct Concurrent concurrent, struct Time time, struct Process *processes) {
	
	for (int i=0;i<processes[i].num_lines;i++) {
	
		if (strcmp(processes[i].name, "0") != 0 ) {
		
			if ( (time.day_of_week == atoi(processes[i].time_str.day_of_week)) || strcmp(processes[i].time_str.day_of_week, "*") == 0) {
			
				if ( (time.month == atoi(processes[i].time_str.month)) || strcmp(processes[i].time_str.month, "*") == 0) {
				
					if ( (time.day == atoi(processes[i].time_str.day)) || (strcmp(processes[i].time_str.day, "*") == 0) ) {
					
						if ( (time.hour == atoi(processes[i].time_str.hour)) || (strcmp(processes[i].time_str.hour, "*") == 0) ) {
						
							if ( (time.minute == atoi(processes[i].time_str.minute)) || (strcmp(processes[i].time_str.minute, "*") == 0) ) {
								for (int j=0;j<20;j++) {
									if (concurrent.arr[j] == -1) {
										concurrent.arr[j] = processes[i].estimate;
										break;
									}
								}						
							}
						}
					}						  
				}
			}
		}
	}
	
	return concurrent;
}

/*The driver function to simulate the processes running in a given month, 
outputting the name of the most frequently used command, the total number of commands invoked, 
and the maximum number of commands running at any given time.*/
int main(int argc, char *argv[]) {

	if (argc != 4) {
		printf("incorrect number of arguments: 4 required ---> %d provided", argc);
		exit(EXIT_FAILURE);
	}
	if (argc == 4) {
	
		int num_days = getMonthDays(argv[1], strlen(argv[1]));
		
		struct Process *all_proc = file_processing(argv[2], argv[3]); 		
		
		all_proc = text_to_num(all_proc);

		struct Time time;
		
		time.minute = 0;
		time.hour = 0;
		time.day = 1;
		time.month = atoi(argv[1]);
		time.days_in_month = num_days;
		
		int max_concurrent = 0;
		
		struct Concurrent concurrent;
		for (int i=0;i<20;i++) {
			concurrent.arr[i] = -1;
		}
		
		all_proc = number_of_calls(time, all_proc);
		
		concurrent = concurrent_count(concurrent, time, all_proc);
		
		for (int x=0;x<20;x++) {
			if (concurrent.arr[x] == 0) {
				concurrent.arr[x] = -1;
			}
		}
			
		for (int j=0;j<20;j++) {
			if (concurrent.arr[j]!=-1) {
					concurrent.arr[j]--;
			}
		}
		
		for (int i=0;i<((num_days*24*60)-1);i++) {
		
			int temp = 0;

			time = timeTick(time);

			all_proc = number_of_calls(time, all_proc);
			
			concurrent = concurrent_count(concurrent, time, all_proc);
			
			for (int x=0;x<20;x++) {
				if (concurrent.arr[x] == 0) {
					concurrent.arr[x] = -1;
				}
			}
			
			for (int j=0;j<20;j++) {
				if (concurrent.arr[j]!=-1) {
					concurrent.arr[j]--;
				}
			}
			
			for (int z=0;z<20;z++) {
				if (concurrent.arr[z]!=-1) {
					temp++;
				}
			}
			
			if (temp>max_concurrent) {
				max_concurrent = temp;
			}

			if (time.minute==59 && time.hour==59 && time.day==num_days) {
				break;
			}
		}
		
		int total_invoked = 0;
		
		char most_calls[100] = "\0";
		
		int max = 0;
		
		for (int i=0;i<all_proc[i].num_lines;i++) {
		
			total_invoked = total_invoked + all_proc[i].num_calls;
			
			if (all_proc[i].num_calls > max) {
				strcpy(most_calls, all_proc[i].name);
				max = all_proc[i].num_calls;
			}
		}
		
		time_error(all_proc);
		
		printf("\n%s	%i	%i\n", most_calls, total_invoked, max_concurrent);
		
		free(all_proc);
	
		exit(EXIT_SUCCESS);
	}

	return 0;
}
