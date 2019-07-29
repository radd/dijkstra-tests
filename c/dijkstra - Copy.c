#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h" 
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

int main(int argc, char *argv[]) {


	int size = 10;
	// argument - wielksoc grafu
	if(argv[1])
		size = strtol(argv[1], NULL, 10);

	switch (size) {
		case 10: size = 10; break;
		case 100: size = 100; break;
		case 200: size = 200; break;
		case 300: size = 300; break;
		default: size = 10;
	}

	char path[256] = "";
	char name[100] = "";
	char temp[4];

	sprintf_s(temp, sizeof temp, "%d", size);

	strcat_s(name, sizeof name, temp);
	strcat_s(name, sizeof name, "x");
	strcat_s(name, sizeof name, temp);

	strcat_s(path, sizeof path, "../grafy/");
	strcat_s(path, sizeof path, name);
	strcat_s(path, sizeof path, "/graf_");
	strcat_s(path, sizeof path, name);
	strcat_s(path, sizeof path, ".json");

	//printf("Path: %s", path);
	
	char *string = ReadFile2(path);

	//printf("%s", string);

	//char *strJson2 = "[[ 0, 0, 0, 1, 90, 35, 89, 2, 0, 28],[ 0, 0, 1, 19, 0, 0, 0, 0, 2, 85],[ 0, 1, 0, 0, 7, 0, 0, 0, 0, 0],[ 1, 19, 0, 0, 0, 0, 91, 0, 0, 0],[ 90, 0, 7, 0, 0, 0, 78, 0, 15, 61],[ 35, 0, 0, 0, 0, 0, 0, 0, 81, 0],[ 89, 0, 0, 91, 78, 0, 0, 0, 0, 0],[ 2, 0, 0, 0, 0, 0, 0, 0, 0, 3],[ 0, 2, 0, 0, 15, 81, 0, 0, 0, 0],[ 28, 85, 0, 0, 61, 0, 0, 3, 0, 0]]";


	cJSON* root = cJSON_Parse(string);
	
	//printf("%d", first);
	
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
	
	//printf("%d", graf[0][6]);
	//int time = GetTickCount();
	struct timeb start, end;
	int diff;
	ftime(&start);

	int wielkosc = size;

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
				dystans[i] = max; // wielkosc maksymalna
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

	//getchar();
	return 0;
}
