#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX_LINES 100
#define MAX_LEN 100


struct Process {
	char  name[40];		// process name
	char  start_time[15];	// in format: (string) s/m/h/m/d
	int   estimate;		// process length in minutes
   	int num_lines;		// number of processes
};

struct Time {
	int minute;		// 
	int hour;		// struct to hold all of the
	int day;		// time and date data.
	int month;		//
	int day_of_week;
	int days_in_month;
};	


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
	
	char cron_times[cron_clean_line][100];
	for (int z=0;z<cron_clean_line;z++) {
  		cron_times[z][0] = '\0';
	}
	
	for (int z=0;z<cron_clean_line;z++) {
		int x = 0;
		int space_counter = 0;
		while ( (cron_processes[z][x] != '\0') && (space_counter < 5) ) {
			if (cron_processes[z][x] == ' ') {
				strcat(cron_times[z], "/");
				space_counter++;
				x++;
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
    	
	for (int z=0;z<cron_clean_line;z++) {
		int x = 0;
		int space_counter = 0;
		while ( (cron_processes[z][x] != '\n') ) {
			if (space_counter > 5) {
				if (cron_processes[z][x] == ' ') {
					x++;
					space_counter++;
					continue;
				}
				else {
					strncat(cron_names[z], &cron_processes[z][x], 1);
					x++;
				}
			}
			else {
				if (cron_processes[z][x] == ' ') {
					x++;
					space_counter++;
				}
				else {
					x++;
				}
			}
    		}
    	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
	
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
    	
	for (int z=0;z<esti_clean_line;z++) {
		int x = 0;
		int space_counter = 0;
		while ( (space_counter < 1) ) {
			if (esti_processes[z][x] == ' ') {
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
    	
	for (int z=0;z<esti_clean_line;z++) {
		int x = 0;
		int space_counter = 0;
		while ( (esti_processes[z][x] != '\n') ) {
			if (space_counter >= 1) {
				if (esti_processes[z][x] == ' ') {
					x++;
					space_counter++;
				}
				else {
					strncat(esti_times[z], &esti_processes[z][x], 1);
					x++;
				}
			}
			else {
				if (esti_processes[z][x] == ' ') {
					x++;
					space_counter++;
				}
				else {
					x++;
				}
			}
		}
	}

	struct Process *all_proc = malloc(sizeof(struct Process) * cron_clean_line);       
	
	for (int i=0;i<cron_clean_line;i++) {
		strcpy( all_proc[i].name, cron_names[i]);
		strcpy( all_proc[i].start_time, cron_times[i]);
		all_proc[i].num_lines = cron_clean_line;
	}
	
	for (int i=0;i<cron_clean_line;i++) {
		for (int j=0;j<esti_clean_line;j++) {
			if (strcmp(all_proc[i].name, esti_names[j]) == 0) {
				all_proc[i].estimate = atoi(esti_times[j]);
			}
		}
	}
		
	return all_proc;
}
	 
// A utility function to provide the number of days from the command line argv[] input.
int getMonthDays(char *argv, int size) {
	
	int num = atoi(argv);
		
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
	
	// do check for numerial month. eg. "9".
	else if ( (size == 1) || (size == 2) ) {
		if ( (0 > num) || (12 < num) ) {
			printf("month is not valid");
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
			
	return 0;
}

// A function that will tick through all the days of a given month argv[] by second.
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
	
	return time;
}

// Combine int values to output string time[] to compare to processes[].

int processChecker(char *time[],char *processes[]) {
	//char current[20];
	//char process[20];
	int value;
	//value = strcmp(current, process);
	if (value == 0) {
		//process is running. Add 1 to total processes. 
		//Add one to this processCounter. Add to concurrent processes.
	}
	else {
		// process is not running. continue to next process/time.
	}
	
	return 0;
}

// loop this process in main for each process string then move to next time.
// pretty naive, better solution? Just use strcmp() in main()?


int get_day_of_week(int d, int m, int y) {
	return (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
}


int main(int argc, char *argv[]) {

	if (argc != 4) {
		printf("incorrect number of arguments: 4 required ---> %d provided", argc);
		exit(EXIT_FAILURE);
	}
	if (argc == 4) {
	
		int num_days = getMonthDays(argv[1], strlen(argv[1]));
		printf("\nnumber of days: %i\n", num_days);
		
		printf("\n");
		
		struct Process *all_proc = file_processing(argv[2], argv[3]); 		
				
		for (int i=0;i<all_proc[i].num_lines;i++) {
			printf("##   %s   ##   %s   ##   %i   ##   %i   ##\n\n", all_proc[i].name, 
							       	                 all_proc[i].start_time, 
						                                 all_proc[i].estimate,
						                                 all_proc[i].num_lines);
		}
		
		struct Time time;
		
		time.minute = 0;
		time.hour = 0;
		time.day = 1;
		time.month = atoi(argv[1]);
				
		for (int i=0;i<(42823);i++) {
			time = timeTick(time);
		}
				
		time.day_of_week = get_day_of_week(time.day, atoi(argv[1])+1, 2022);

		time.days_in_month = num_days;
					      
		char time_str[20] = "\0";
	
		char minute_str[3] = "\0";
		char hour_str[3] = "\0";
		char day_str[3] = "\0";
		char month_str[3] = "\0";
		char day_of_the_week_str[3] = "\0";
		
		
		sprintf(minute_str, "%d", time.minute);
		sprintf(hour_str, "%d", time.hour);
		sprintf(day_str, "%d", time.day);
		strcat(month_str, argv[1]);
		sprintf(day_of_the_week_str, "%d", time.day_of_week);
		
		strcat(time_str, minute_str);
		strcat(time_str, "/");
		strcat(time_str, hour_str);
		strcat(time_str, "/");
		strcat(time_str, day_str);
		strcat(time_str, "/");
		strcat(time_str, month_str);
		strcat(time_str, "/");
		strcat(time_str, day_of_the_week_str);
		strcat(time_str, "/");
		
		printf("\n%s\n", time_str);
		
		free(all_proc);
	
		exit(EXIT_SUCCESS);
	}

	return 0;
}
