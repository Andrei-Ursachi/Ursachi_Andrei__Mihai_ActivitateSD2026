#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<malloc.h>
#include<stdio.h>

struct Biblioteca {
	int id;
	char* denumire;
	int nrAngajati;
	char* locatie;
	float valoareMarfa;
};

struct Biblioteca initializare(int id, const char* denumire, int nrAngajati, const char* locatie, float valoareMarfa) {
	struct Biblioteca b;
	b.id = id;
	b.denumire = (char*)malloc((strlen(denumire) + 1) * sizeof(char));
	strcpy_s(b.denumire, strlen(denumire) + 1, denumire);
	b.nrAngajati = nrAngajati;
	b.locatie = (char*)malloc((strlen(locatie)+1)*sizeof(char));
	strcpy_s(b.locatie, strlen(locatie) + 1, locatie);
	b.valoareMarfa = valoareMarfa;
	return b;
}

//functie de afisare
void afisareBiblioteca(struct Biblioteca b) {
	printf("ID bibliotecii este %d, se numeste %s, are un total de %d angajati, se afla in %s, contine o valoare a cartilor de aprox %5.2f milioane lei."
		, b.id, b.denumire, b.nrAngajati, b.locatie, b.valoareMarfa);
}

void dezalocareBiblioteca(struct Biblioteca* b) {
	if (!b) {
		return;
	}
	free(b->denumire);
	free(b->locatie);
	b->denumire = NULL;
	b->locatie = NULL;
}

void main() {
	struct Biblioteca bib1 = initializare(1, "Carturesti", 13, "Bacau", 13.5);
	afisareBiblioteca(bib1);
	dezalocareBiblioteca(&bib1);
}