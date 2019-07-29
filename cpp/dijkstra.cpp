#include <iostream>
#include <string>
#include <fstream>
#include "lib\json.hpp"
#include <sys\timeb.h> 

using namespace std;
using json = nlohmann::json;


int** algorytm(int** graf, int s) 
{
		
	struct timeb start, end;
	int diff;
	ftime(&start);

	int wielkosc = s;

	int* dystans = new int[wielkosc];
	int* tab_wizytacji = new int[wielkosc];

	int** wynik = new int*[wielkosc];
	for (int i = 0; i < wielkosc; i++) {
		wynik[i] = new int[wielkosc];
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
	diff = (int)(1000.0 * (end.time - start.time)
		+ (end.millitm - start.millitm));

	cout << diff;
	
	return wynik;
}


int main(int argc, char *argv[]) 
{
	int size = 10;

	if (argc > 1)
		size = strtol(argv[1], NULL, 10);

	switch (size) {
		case 10: size = 10; break;
		case 100: size = 100; break;
		case 200: size = 200; break;
		case 300: size = 300; break;
		default: size = 10;
	}

	string name = to_string(size);

	string path = "../_grafy/";
	path += name;
	path += "/graf_";
	path += name;
	path += ".json";

	//cout << path << endl;

	ifstream i(path, ifstream::binary);
	json js;
	i >> js;

	int** graf = new int*[size];

	for (int i = 0; i < size; i++) {
		graf[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			graf[i][j] = js[i][j];
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
		
		cout << endl << "Wynik (od " << from << " do " << to << "): " << wynik[from][to] << endl;
		cout << endl;
	}
		
	//getchar();
    return 0;
}
