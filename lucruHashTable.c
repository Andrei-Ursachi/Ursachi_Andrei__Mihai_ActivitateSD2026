#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct Avion Avion;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Avion {
	char* model;
	int nrPasageri;
	float greutate;
};

struct Nod {
	Avion info;
	Nod* next;
};

struct HashTable {
	int dimensiune;
	Nod** vector;
};

//fac o initializare (aka constructor)
Avion initializare(const char* model, int nrPasageri, float greutate) {
	Avion avion;
	avion.model = (char*)malloc(sizeof(char) * (strlen(model) + 1));
	strcpy(avion.model, model);
	avion.nrPasageri = nrPasageri;
	avion.greutate = greutate;
	return avion;
}

//functie de afisare
void afisareAvion(Avion avion) {
	printf("Avionul %s va decola cu %d pasageri iar greutatea aproximativa va fi de %.2f."
		,avion.model, avion.nrPasageri, avion.greutate);
}

//functie de afisare a listei de avioane
void afisareListaAvioane(Nod* cap) {
	while (cap != NULL) {
		afisareAvion(cap->info);
		cap = cap->next;
	}
	
}

//functie de inserare 
void inserareSfarsit(Nod** cap, Avion avion) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = avion;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		Nod* aux = *cap;
		while (aux->next = NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}
