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
