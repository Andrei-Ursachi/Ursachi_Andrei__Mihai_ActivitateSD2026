#define CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Produs Produs;
struct Produs{
	int cod;
	char* denumire;
	float pret;
	float cantitate;
};

typedef struct Nod Nod;
struct Nod {
	Produs info;
	Nod* next;
};


Produs creareProdus(int cod, const char* denumire, float pret, float cantitate) {
	Produs produs;
	produs.cod = cod;
	produs.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy_s(produs.denumire, strlen(denumire) + 1,denumire);
	produs.pret = pret;
	produs.cantitate = cantitate;
	return produs;
}

Nod* creareNod(Produs produs, Nod* next) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = produs;
	nou->next = next;
	return nou;
}

void afisareProdus(Produs produs) {
	printf("Codul: %d", produs.cod);
	printf("Denumire: %d", produs.denumire);
	printf("Pret: %d", produs.pret);
	printf("Cantitate: %d", produs.cantitate);
};


void main() {
	Produs produs1 = creareProdus(1, "Bicicleta", 200, 15);
	afisareProdus(produs1);
}