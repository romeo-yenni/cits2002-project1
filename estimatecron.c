#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_LINES 100
#define MAX_LEN 100

void file_processing(char *filename) {

	// storage for lines from file
	static char data[MAX_LINES][MAX_LEN];
	
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
	char processes[line][MAX_LEN];
	
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
	
	printf("\n\n\n");
	
	for (int a = 0; a < clean_line; a++) {
		printf("%s", processes[a]);
	}
}
	 
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
// Combine int values to output string time[] to compare to processes[].

int processChecker(char *time[],char *processes[]) {
	char current[20];
	char process[20];
	int value;
	value = strcmp(current, process);
	if (value == 0) {
		/* process is running. Add 1 to total processes. 
		Add one to this processCounter. Add to concurrent processes. */
	}
	else {
		// process is not running. continue to next process/time.
	}
}
// loop this process in main for each process string then move to next time.
// pretty naive, better solution? Just use strcmp() in main()?

int main(int argc, char *argv[]) {

	if (argc != 4) {
		printf("incorrect number of arguments: 4 required ---> %d provided", argc);
		exit(EXIT_FAILURE);
	}
	if (argc == 4) {
		printf("\n");
		file_processing(argv[2]);
		printf("\n\n");
		file_processing(argv[3]);
		printf("\n");
		exit(EXIT_SUCCESS);
	}

	return 0;
}