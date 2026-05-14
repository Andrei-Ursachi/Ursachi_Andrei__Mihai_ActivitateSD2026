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

Tramvai initializareTramvai(int numar, const char* traseu, float pretBilet, int nrStatii) {
	Tramvai t;
	t.numar = numar;
	t.pretBilet = pretBilet;
	t.nrStatii = nrStatii;
	t.traseu = (char*)malloc(strlen(traseu) + 1);
	strcpy_s(t.traseu, strlen(traseu) + 1, traseu);
	return t;
}

int maxim(int a, int b) {
	return (a > b ? a : b);
}

int calcInaltimeArbore(Nod* rad) {
	if (rad) {
		return maxim(calcInaltimeArbore(rad->stanga), calcInaltimeArbore(rad->dreapta)) + 1;
	}
	return 0;
}

int diferentaInaltimeArbore(Nod* rad) {
	if (rad) {
		return calcInaltimeArbore(rad->stanga) - calcInaltimeArbore(rad->dreapta);
	}
	else {
		return 0;
	}
}

void rotireStanga(Nod** rad) {
	Nod* aux = (*rad)->dreapta;
	aux->dreapta = aux->stanga;
	aux->stanga = (*rad);
	(*rad) = aux;
}

void rotireDreapta(Nod** rad) {
	Nod* aux = (*rad)->stanga;
	aux->stanga = aux->dreapta;
	aux->dreapta = (*rad);
	(*rad) = aux;
}

void adaugaTramvaiInArbore(Nod** rad, Tramvai tramvaiNou) {
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = tramvaiNou;
		nod->dreapta = NULL;
		nod->stanga = NULL;
		*rad = nod;
	}
	else {
		if ((*rad)->info.numar > tramvaiNou.numar) {
			adaugaTramvaiInArbore(&((*rad)->stanga), tramvaiNou);
		}
		if ((*rad)->info.numar < tramvaiNou.numar) {
			adaugaTramvaiInArbore(&((*rad)->dreapta), tramvaiNou);
		}
	}

	int diferentaInaltimi = calcInaltimeArbore(*rad);
	if (diferentaInaltimeArbore == 2) {
		if (calcInaltimeArbore((*rad)->stanga) == -1) {
			rotireStanga(&(*rad)->stanga);
		}
		rotireDreapta(rad);
	}
	if (diferentaInaltimeArbore == -2) {
		if (calcInaltimeArbore((*rad)->dreapta) == 1) {
			rotireDreapta(&(*rad)->dreapta);
		}
		rotireStanga(rad);
	}
}