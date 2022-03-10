// D.1 listc.cpp: Fig 2.2

// program using C streams to read characters from a file 
// and write them to the terminal screen 
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
int main(void) {
	char ch;
	FILE * file; // file descriptor
	char filename[20];
	printf("Enter the name of the file: ");	// Step 1
	//visual studio는  gets()를 사용하지 않고 gets_s()를 사용
	gets_s(filename);					// Step 2
	puts(filename);
	FILE* pFile = fopen(filename, "w");
	fprintf(pFile, "file structure");
	fclose(pFile);
	file =fopen(filename, "r");			// Step 3
	while (fread(&ch, 1, 1, file) != 0)		// Step 4a
		fwrite(&ch, 1, 1, stdout);		// Step 4b
	fclose(file);					// Step 5
	system("pause");
	return 1;
}
