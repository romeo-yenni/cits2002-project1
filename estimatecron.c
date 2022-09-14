#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


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
		all_proc[i].num_lines = cron_clean_line;
		all_proc[i].num_calls = 0;
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
	
	int p=5;
	while ( (p>(cron_clean_line)-1) && (p<440) ) {
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

int get_day_of_week(int d, int m, int y) {
	return (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
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
	
	time.day_of_week = get_day_of_week(time.day, time.month+1, 2022);
	
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

struct Process * text_to_num(struct Process *processes) {
	
	for (int i=0;i<processes[i].num_lines;i++) {
		
		int size = strlen(processes[i].time_str.month);
		
		if (size == 3) {
			
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
		}
	}
	
	for (int i=0;i<processes[i].num_lines;i++) {
		
		int size = strlen(processes[i].time_str.day_of_week);
		
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
	}
	
	return processes;
}


struct Process * number_of_calls(struct Time time, struct Process *processes) {

	for (int i=0;i<processes[i].num_lines;i++) {
	
		if (strcmp(processes[i].name, "0") != 0 ) {
		
			if ( (time.day_of_week == atoi(processes[i].time_str.day_of_week)) || strcmp(processes[i].time_str.day_of_week, "*") == 0) {
			
				if ( (time.month == atoi(processes[i].time_str.month)) || strcmp(processes[i].time_str.month, "*") == 0) {
				
					if ( (time.day == atoi(processes[i].time_str.day)) || (strcmp(processes[i].time_str.day, "*") == 0) ) {
					
						if ( (time.hour == atoi(processes[i].time_str.hour)) || (strcmp(processes[i].time_str.hour, "*") == 0) ) {
						
							if ( (time.minute == atoi(processes[i].time_str.minute)) || (strcmp(processes[i].time_str.minute, "*") == 0) ) {
								
								processes[i].num_calls++;	
								/**
								printf("\n %i, %i, %i, %i, %i  //  %s, %s, %s, %s, %s  --  %s\n", time.minute, 
															  time.hour, 
															  time.day,
															  time.month, 
															  time.day_of_week,
															  processes[i].time_str.minute,
															  processes[i].time_str.hour,
															  processes[i].time_str.day,
															  processes[i].time_str.month,
															  processes[i].time_str.day_of_week,
															  processes[i].name);
								**/
							}
						}
					}						  
				}
			}
		}
	}
	
	return processes;
}



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
		
		
		for (int i=0;i<((num_days*24*60)-1);i++) {
			time = timeTick(time);

			all_proc = number_of_calls(time, all_proc);

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
		
		int arr[20];
		int most_concurrent = 0;

		for (int i=0;i<((num_days*24*60)-1);i++) {
			time = timeTick(time);
			
			int tick_concurrent = 0;								//tick_concurrent is re-initialized to 0 for the new tick.

			for(int i = 0;i < 20;i++) {								//Decrements all running processes as the tick begins.
				if (arr[i] != 0) {
					arr[i]--;
				}
			}

			all_proc = number_of_calls(time, all_proc);				//If a process runs on a given tick, its estimate value is initialised in arr[] in an element not containing a running process.
			if (all_proc[i].num_calls > 0) {
				for(int j = 0;j < 20;j++) {
					if (j == 0) {
						arr[j] = all_proc[i].estimate;
					}
				}
				for(int j = 0;j < 20;j++) {							//For each running process, tick_concurrent is incremented.
					if (j != 0) {
						tick_concurrent++;
						if (most_concurrent < tick_concurrent) {	//If it's value is greater than max_concurrent, max_concureent is overwritten.
							most_concurrent = tick_concurrent;
						}
					}
				}
			}
		
			if (time.minute==59 && time.hour==59 && time.day==num_days) {
				break;
			}
		}

		printf("\n%s	%i	%i\n", most_calls, total_invoked, most_concurrent);
		
		free(all_proc);
	
		exit(EXIT_SUCCESS);
	}

	return 0;
}