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
	aux = strtok(NULL, sep);
	t1.traseu = (char*)malloc(strlen(aux) + 1);
	strcpy_s(t1.traseu, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	t1.pretBilet = atof(aux);
	aux = strtok(NULL, sep);
	t1.nrStatii = atoi(aux);
	return t1;
}

void afisareTramvai(Tramvai tramvai) {
	printf("Numar: %d\n", tramvai.numar);
	printf("Traseu : %s\n", tramvai.traseu);
	printf("Pret: %.2f\n", tramvai.pretBilet);
	printf("Numar statii: %d\n", tramvai.nrStatii);
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
	(*rad)->dreapta = aux->stanga;
	aux->stanga = (*rad);
	(*rad) = aux;
}

void rotireDreapta(Nod** rad) {
	Nod* aux = (*rad)->stanga;
	(*rad)->stanga = aux->dreapta;
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

	int diferentaInaltimi = diferentaInaltimeArbore(*rad);
	if (diferentaInaltimi == 2) {
		if (diferentaInaltimeArbore((*rad)->stanga) == -1) {
			rotireStanga(&(*rad)->stanga);
		}
		rotireDreapta(rad);
	}
	if (diferentaInaltimi == -2) {
		if (diferentaInaltimeArbore((*rad)->dreapta) == 1) {
			rotireDreapta(&(*rad)->dreapta);
		}
		rotireStanga(rad);
	}
}

Nod* citireArboreTramvaieDinFisier(const char* numeFisier) {
	Nod* rad = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			Tramvai t = citireTramvaiDinFisier(f);
			adaugaTramvaiInArbore(&rad, t);
		}
	}
	fclose(f);
	return rad;
}

void afisareInOrdine(Nod* rad) {
	if (rad) {
		afisareInOrdine(rad->stanga);
		afisareTramvai(rad->info);
		afisareInOrdine(rad->dreapta);
	}
}

void afisarePostOrdine(Nod* rad) {
	if (rad) {
		afisarePostOrdine(rad->stanga);
		afisarePostOrdine(rad->dreapta);
		afisareTramvai(rad->info);
	}
}

void afisarePreOrdine(Nod* rad) {
	if (rad) {
		afisareTramvai(rad->info);
		afisarePreOrdine(rad->stanga);
		afisarePreOrdine(rad->dreapta);
	}
}

void dezalocareArbore(Nod** rad) {
	if (*rad) {
		dezalocareArbore(&(*rad)->stanga);
		dezalocareArbore(&(*rad)->dreapta);
		free((*rad)->info.traseu);
		free(*rad);
		*rad = NULL;
	}
}

int determinatNoduriArbore(Nod* rad) {
	if (rad) {
		return determinatNoduriArbore(rad->stanga) + determinatNoduriArbore(rad->dreapta) + 1;
	}
	else {
		return 0;
	}
}


int calculNrTotalStatii(Nod* rad) {
	if (rad) {
		return rad->info.nrStatii + calculNrTotalStatii(rad->stanga) + calculNrTotalStatii(rad->dreapta);
	}
	return 0;
}

void main() {
	

	Nod* rad = citireArboreTramvaieDinFisier("suportLucruAVL2.txt");
	afisareInOrdine(rad);

	dezalocareArbore(&rad);
}