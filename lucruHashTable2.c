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
}

void afisareBere(Bere bere) {
	printf("Berea %s vine in recipient de %d mililitrii si are un volum de alcool de %.2f", bere.marca, bere.cantitate, bere.volumAcool);
}