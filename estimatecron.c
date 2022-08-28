#include <stdlib.h>
#include <stdio.h>


void file_processing(char *filename) {
	// open file
	FILE   *file = fopen(filename, "r");


	//  check if file was opened successfully
	if(file == NULL) {
		printf( "cannot open file '%s'\n", filename);
		exit(EXIT_FAILURE);
	}
	
	char    line[BUFSIZ];
	
	//  reading each line from file
	//  stops at end of file or error
    	while( fgets(line, sizeof line, file) != NULL ) {  
        	printf("%s", line);
    	}	
	//  close file
	fclose(file);
}
	 


int main(int argc, char *argv[]) {

	if (argc != 4) {
		printf("incorrect number of arguments: 4 required ---> %d provided", argc);
		exit(EXIT_FAILURE);
	}
	if (argc == 4) {
		file_processing(argv[2]);
		printf("\n\n");
		file_processing(argv[3]);
		exit(EXIT_SUCCESS);
	}
	return 0;
	
	
	
	
}
