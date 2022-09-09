#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_LINES 100
#define MAX_LEN 100


struct Process {
   char  name[40];		// process name
   char  start_time[15];	// in format: (string) s/m/h/m/d
   int   estimate;		// process length in minutes
   int num_lines;		// number of processes
};


struct Process *file_processing(char *crontab, char *estimates) {

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

/**
	 
// A utility function to provide the number of days from the command line argv[] input.
int getMonthDays(char *argv[]) {
	if (argv[1] == 0 || argv[1] == "JAN")
		return 31;
	if (argv[1] == 1 || argv[1] == "FEB")
		return 28;
	if (argv[1] == 2 || argv[1] == "MAR")
		return 31;
	if (argv[1] == 3 || argv[1] == "APR")
		return 30;
	if (argv[1] == 4 || argv[1] == "MAY")
		return 31;
	if (argv[1] == 5 || argv[1] == "JUN")
		return 30;
	if (argv[1] == 6 || argv[1] == "JUL")
		return 31;
	if (argv[1] == 7 || argv[1] == "AUG")
		return 31;
	if (argv[1] == 8 || argv[1] == "SEP")
		return 30;
	if (argv[1] == 9 || argv[1] == "OCT")
		return 31;
	if (argv[1] == 10 || argv[1] == "NOV")
		return 30;
	if (argv[1] == 11 || argv[1] == "DEC")
		return 31;	
	return 0;
}

// A function that will tick through all the days of a given month argv[] by second.
void timeTick(int monthDays) {
	int d = 0;
	int h = 0;
	int m = 0;
	int s = 0;
	// need to track days?

	if (h >= 24 || m >= 60 || s >= 60)
		{
			printf("This is not a valid time\n");
			exit(EXIT_FAILURE);
		}
	s++;
	if (s == 60) {
		m++;
		s = 0;
	}
	if (m == 60) {
		h++;
		m =0;
	}
	if (h == 24) {
		d++;
		h = 0;
	}
	if (d > monthDays) {
		exit(EXIT_SUCCESS);
	}
}
**/
// Combine int values to output string time[] to compare to processes[].
/**
int processChecker(char *time[],char *processes[]) {
	char current[20];
	char process[20];
	int value;
	value = strcmp(current, process);
	if (value == 0) {
		//process is running. Add 1 to total processes. 
		//Add one to this processCounter. Add to concurrent processes.
	}
	else {
		// process is not running. continue to next process/time.
	}
}
**/
// loop this process in main for each process string then move to next time.
// pretty naive, better solution? Just use strcmp() in main()?


int main(int argc, char *argv[]) {

	if (argc != 4) {
		printf("incorrect number of arguments: 4 required ---> %d provided", argc);
		exit(EXIT_FAILURE);
	}
	if (argc == 4) {
		
		printf("\n");
		
		struct Process *all_proc = file_processing(argv[2], argv[3]); 		
				
		for (int i=0;i<all_proc[i].num_lines;i++) {
			printf("##   %s   ##   %s   ##   %i   ##   %i   ##\n\n", all_proc[i].name, 
							       	                 all_proc[i].start_time, 
						                                 all_proc[i].estimate,
						                                 all_proc[i].num_lines);
		}

		free(all_proc);
	
		exit(EXIT_SUCCESS);
	}

	return 0;
}
