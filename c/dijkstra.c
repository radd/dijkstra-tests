#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include "lib\cJSON.h" 
#include <time.h>
#include <sys\timeb.h> 
#include <windows.h> 


//https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
char* ReadFile2(char *filename)
{
	char *buffer = NULL;
	int string_size, read_size;
	FILE *handler = fopen(filename, "r");

	if (handler)
	{
		// Seek the last byte of the file
		fseek(handler, 0, SEEK_END);
		// Offset from the first to the last byte, or in other words, filesize
		string_size = ftell(handler);
		// go back to the start of the file
		rewind(handler);

		// Allocate a string that can hold it all
		buffer = (char*)malloc(sizeof(char) * (string_size + 1));

		// Read it all in one operation
		read_size = fread(buffer, sizeof(char), string_size, handler);

		// fread doesn't set it so put a \0 in the last position
		// and buffer is now officially a string
		buffer[read_size] = '\0';



		// Always remember to close the file.
		fclose(handler);
	}

	return buffer;
}

int** algorytm(int** graf, int s) 
{
	//printf("%d", graf[0][6]);
	//int time = GetTickCount();
	struct timeb start, end;
	int diff;
	ftime(&start);

	int wielkosc = s;

	int* dystans = malloc(wielkosc * sizeof(int));
	int* tab_wizytacji = malloc(wielkosc * sizeof(int));

	int** wynik;
	wynik = malloc(wielkosc * sizeof(int*));
	for (int i = 0; i < wielkosc; i++) {
		wynik[i] = malloc(wielkosc * sizeof(int));
	}

	for (int g = 0; g<wielkosc; ++g) {
		for (int k = 0; k<wielkosc; ++k) {
			wynik[k][g] = 0;
		}
	}

	int max = 99999;
	for (int i = 0; i < wielkosc; ++i) {

		for (int j = 0; j < wielkosc; ++j)
		{
			if (graf[i][j] == 0) {
				graf[i][j] = max;
			}
		}
	}

	int punkt_start = 0;
	int punkt_koniec = 0;

	for (int g = 0; g<wielkosc; ++g) {
		punkt_start = g;
		for (int k = 0; k<wielkosc; ++k) {
			punkt_koniec = k;

			for (int i = 0; i < wielkosc; ++i) {
				dystans[i] = max;
			}
			dystans[punkt_start] = 0;

			for (int i = 0; i < wielkosc; ++i) {
				tab_wizytacji[i] = 0;
			}

			for (int i = 0; i < wielkosc; ++i) {
				int aktualny = -1;
				for (int j = 0; j < wielkosc; ++j) {
					if (tab_wizytacji[j] == 1)
					{
						continue;
					}
					if (aktualny == -1 || dystans[j] < dystans[aktualny])
					{
						aktualny = j;
					}
				}

				tab_wizytacji[aktualny] = 1;

				for (int j = 0; j < wielkosc; ++j)
				{
					int droga = dystans[aktualny] + graf[aktualny][j];
					if (droga < dystans[j]) {
						dystans[j] = droga;
					}
				}
			}

			wynik[k][g] = dystans[k];
			wynik[g][k] = dystans[k];

		}
	}
	ftime(&end);
	//printf("%d", wynik[9][6]);
	//int timeElapsed = GetTickCount() - time;
	diff = (int)(1000.0 * (end.time - start.time)
		+ (end.millitm - start.millitm));

	//printf("\nOperation took %u milliseconds\n", timeElapsed);
	printf("%d", diff);

	return wynik;
}


int main(int argc, char *argv[]) {

	int size = 10;

	if(argc > 1)
		size = strtol(argv[1], NULL, 10);

	switch (size) {
		case 10: size = 10; break;
		case 100: size = 100; break;
		case 200: size = 200; break;
		case 300: size = 300; break;
		default: size = 10;
	}

	char path[256] = "";
	char name[4];

	sprintf_s(name, sizeof name, "%d", size);

	strcat_s(path, sizeof path, "../_grafy/");
	strcat_s(path, sizeof path, name);
	strcat_s(path, sizeof path, "/graf_");
	strcat_s(path, sizeof path, name);
	strcat_s(path, sizeof path, ".json");

	
	char *string = ReadFile2(path);

	//printf("%s", string);

	cJSON* root = cJSON_Parse(string);
		
	int** graf;
	graf = malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		graf[i] = malloc(size * sizeof(int));
	}
	
	for (int i = 0; i < size; i++) {
		cJSON* row = cJSON_GetArrayItem(root, i);
		for (int j = 0; j < size; j++) {
				graf[i][j] = cJSON_GetArrayItem(row, j)->valueint;
		}
	}
	
	int** wynik = algorytm(graf, size);
	
	if (argc > 2 && !strcmp(argv[2], "-r")) {
		int from = -1, to = -1;
		
		if(argc > 3)
			from = strtol(argv[3], NULL, 10);

		if(argc > 4)
			to = strtol(argv[4], NULL, 10);

		if(from < 0 || from >= size)
			from = 0;
		
		if(to < 0 || to >= size)
			to = 1;
		
		printf("\nWynik (od %d do %d): %d \n\n", from, to, wynik[from][to]);
	
	}
	

	//getchar();
	return 0;
}
