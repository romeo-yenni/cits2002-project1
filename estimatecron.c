#include <stdlib.h>
#include <stdio.h>


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
	
	for (int i=0;i<line;i++) {
		printf("%s", data[i]);
	}
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
}

// A function that will tick through all the days of a given month by second.
void timeTick(int monthDays) {
	int d,h,m,s = 0;

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
		exit(EXIT_SUCCESS)
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
		file_processing(argv[2]);
		printf("\n\n");
		file_processing(argv[3]);
		printf("\n");
		exit(EXIT_SUCCESS);
	}

	return 0;
	
	
	
	
}
