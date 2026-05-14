#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tramvai {
	int numar;
	char* traseu;
	float pretBilet;
	int nrStatii;
};
typedef struct Tramvai Tramvai;

struct Nod {
	Tramvai info;
	struct Nod* stanga;
	struct Nod* dreapta;
};
typedef struct Nod Nod;

Tramvai citireTramvaiDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Tramvai t1;
	aux = strtok(buffer, sep);
	t1.numar = atoi(aux);
	t1.nrStatii = atoi(strtok(NULL, sep));
	t1.pretBilet = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	t1.traseu = malloc(strlen(aux) + 1);
	strcpy_s(t1.traseu, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	return t1;
}

void afisareTramvai(Tramvai tramvai) {
	printf("Id: %d\n", tramvai.numar);
	printf("Nr. usi : %d\n", tramvai.nrStatii);
	printf("Pret: %.2f\n", tramvai.pretBilet);
	printf("Model: %s\n", tramvai.traseu);
}