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
	strcpy_s(avion.model, strlen(model) + 1,model);
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

//creare tabela hash
HashTable initializareHash(int size) {
	HashTable table;
	table.dimensiune = size;
	table.vector = (Nod**)malloc(sizeof(Nod*) * size);
	for (int i = 0; i < size; i++) {
		table.vector[i] = NULL;
	}
	return table;
}

int hash(int dim, int nrStudenti) {
	return nrStudenti % dim;
}

//functie de inserare in tabela hash
void inserareTabelaHash(HashTable table, Avion avion) {
	if (table.dimensiune > 0) {
		int poz = hash(table.dimensiune, avion.nrPasageri);
		if (poz >= 0 && poz < table.dimensiune) {
			inserareSfarsit(&(table.vector[poz]), avion);
		}
	}
}

//functie de afisarea tabelei hash
void afisareTabelaHash(HashTable table) {
	for (int i = 0; i < table.dimensiune; i++) {
		printf("\nPozitia %d", i);
		printf(": ");
		afisareListaAvioane(table.vector[i]);
	}
}

//functie pentru dezalocarea memoriei aferente 
void dezalocareLista(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.model);
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie);
	}
}

//dezalocare memorie alocata tabelei hash
void dezalocareHash(HashTable table) {
	for (int i = 0; i < table.dimensiune; i++) {
		dezalocareLista(&(table.vector[i]));
	}
	free(table.vector);
}

void main() {
	HashTable table1 = initializareHash(4);
	inserareTabelaHash(table1, initializare("A320", 300, 420.6));
	inserareTabelaHash(table1, initializare("A330", 111, 40.6));
	inserareTabelaHash(table1, initializare("A3440", 222, 4210.6));
	inserareTabelaHash(table1, initializare("A3220", 333, 5000.6));

	afisareTabelaHash(table1);

	dezalocareHash(table1);
}