#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_LINES 100
#define MAX_LEN 100


struct Process {
   char  name[40];		// process name
   char  start_time[15];	// in format: (string) s/m/h/m/d
   int   estimate;		// process length in minutes
};


struct Process *file_processing(char *filename) {

	// storage for lines from file
	char data[MAX_LINES][MAX_LEN];
	
	// open file
	FILE   *file = fopen(filename, "r");
	
	//  check if file was opened successfully
	if(file == NULL) {
		printf( "cannot open file '%s'\n", filename);
		exit(EXIT_FAILURE);
	}
	
	int line = 0;
	
	// check for EOF or error while reading
	while (!feof(file) && !ferror(file)) {
		// check if number of lines < MAX_LINES
		if (fgets(data[line], MAX_LEN, file) != NULL) {
			// increment line
			line++;
		}
	}
	
	//  close file
	fclose(file);
	
	// clean lines
	char processes[MAX_LINES][MAX_LEN];
	
	int clean_line = 0;
	
	for (int i=0;i<line;i++) {
		for (int j = 0; j < MAX_LINES; j++) {
			if (data[i][j] == ' ') {
				continue;
			}
			else if (data[i][j] == '#') {
				break;
			}
			else if (data[i][j] == '\n') {
  			        strcpy(processes[clean_line], data[i]);
				clean_line++;
			}
		}
	}
	
	char times[clean_line][100];
	for (int z=0;z<clean_line;z++) {
  		times[z][0] = '\0';
	}
	
	for (int z=0;z<clean_line;z++) {
		int x = 0;
		int space_counter = 0;
		while ( (processes[z][x] != '\0') && (space_counter < 5) ) {
			if (processes[z][x] == ' ') {
				strcat(times[z], "/");
				space_counter++;
				x++;
			}
			else {
				strncat(times[z], &processes[z][x], 1);
				x++;
			}
    		}
    	}
    	
    	char names[clean_line][40];
    	for (int z=0;z<clean_line;z++) {
    		names[z][0] = '\0';
    	}
    	
	for (int z=0;z<clean_line;z++) {
		int x = 0;
		int space_counter = 0;
		while ( (processes[z][x] != '\n') ) {
			if (space_counter > 5) {
				if (processes[z][x] == ' ') {
					x++;
					space_counter++;
					continue;
				}
				else {
					strncat(names[z], &processes[z][x], 1);
					x++;
				}
			}
			else {
				if (processes[z][x] == ' ') {
					x++;
					space_counter++;
				}
				else {
					x++;
				}
			}
    		}
    	}

	struct Process *all_proc = malloc(sizeof(struct Process) * clean_line);       
	
	for (int i=0;i<clean_line;i++) {
		strcpy( all_proc[i].name, names[i]);
		strcpy( all_proc[i].start_time, times[i]);
		all_proc[i].estimate = 0;
	}
		
	return all_proc;
}


	 
// A utility function to provide the number of days from the command line month input.
int getMonthDays(int month) { // Need to provide appropriate parameter
	if (month == 0)
		return 31;
	if (month == 1)
		return 28;
	if (month == 2)
		return 31;
	if (month == 3)
		return 30;
	if (month == 4)
		return 31;
	if (month == 5)
		return 30;
	if (month == 6)
		return 31;
	if (month == 7)
		return 31;
	if (month == 8)
		return 30;
	if (month == 9)
		return 31;
	if (month == 10)
		return 30;
	if (month == 11)
		return 31;	
	return 0;
}

// A function that will tick through all the days of a given month by second.
void timeTick(int monthDays) {
	int d = 0;
	int h = 0;
	int m = 0;
	int s = 0;

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
// At the end of each we want to output a string s/m/h/m/d to compare to contents of crontab-file string?


int main(int argc, char *argv[]) {

	if (argc != 4) {
		printf("incorrect number of arguments: 4 required ---> %d provided", argc);
		exit(EXIT_FAILURE);
	}
	if (argc == 4) {
		
		printf("\n");
		
		struct Process *all_proc = file_processing(argv[2]); 		
				
		for (int i=0;i<5;i++) {
			printf("##   %s   ##   %s   ##   %i   ##\n\n", all_proc[i].name, 
							       	       all_proc[i].start_time, 
						                       all_proc[i].estimate);
		}

		free(all_proc);
		
		//file_processing(argv[2]);
		
		printf("\n\n");
		
		//file_processing(argv[3]);
		
		printf("\n");
	
		exit(EXIT_SUCCESS);
	}

	return 0;
}
