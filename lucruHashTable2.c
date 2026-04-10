#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct Bere Bere;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Bere {
	char* marca;
	int cantitate;
	float volumAcool;
};

struct Nod {
	Bere info;
	Nod* next;
};

struct HashTable {
	int dimensiune;
	Nod** vector;
};

Bere initializare(const char* marca, int cantitate, float volumAcool) {
	Bere bere;
	bere.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy_s(bere.marca, strlen(marca) + 1, marca);
	bere.cantitate = cantitate;
	bere.volumAcool = volumAcool;
	return bere;
}

void afisareBere(Bere bere) {
	printf("Berea %s vine in recipient de %d mililitrii si are un volum de alcool de %.2f", bere.marca, bere.cantitate, bere.volumAcool);
}

void afisareListaBere(Nod* cap) {
	while (cap != NULL) {
		afisareBere(cap->info);
		cap = cap->next;
	}
}

void inserareLaSfarsit(Nod** cap, Bere bere) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = bere;
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

HashTable initiializareHash(int size) {
	HashTable table;
	table.dimensiune = size;
	table.vector = (Nod**)malloc(sizeof(Nod*) * size);
	for (int i = 0; i < size;i++) {
		table.vector[i] = NULL;
	}
	return table;
}

void afisareTabelaHash(HashTable table) {
	for (int i = 0;i < table.dimensiune; i++) {
		printf("\nPozitia %d", i);
		printf(": ");
		afisareListaBere(table.vector[i]);
	}
}

int hash(int dim, int cantitate) {
	return cantitate % dim;
}

void inserareTabelaHash(HashTable table, Bere bere) {
	if (table.dimensiune > 0) {
		int poz = hash(table.dimensiune, bere.cantitate);
		if (poz >= 0 && poz < table.dimensiune) {
			inserareLaSfarsit(&(table.vector[poz]), bere);
		}
	}
}

void dezalocareLista(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.marca);
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie);
	}
}

void dezalocareHash(HashTable table) {
	for (int i = 0; i < table.dimensiune;i++) {
		dezalocareLista(&(table.vector[i]));
	}
	free(table.vector);
}

void main() {
	HashTable table1 = initiializareHash(3);
	inserareTabelaHash(table1, initializare("Ursus", 500, 5));
	inserareTabelaHash(table1, initializare("Heineken", 330, 4));
	inserareTabelaHash(table1, initializare("Ciucas", 1000, 7.2));

	afisareTabelaHash(table1);
	dezalocareHash(table1);
}