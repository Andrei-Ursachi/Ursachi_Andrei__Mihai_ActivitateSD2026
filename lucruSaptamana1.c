#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<malloc.h>
#include<stdio.h>

struct Biblioteca {
	int id;
	char* denumire;
	int nrAngajati;
	char locatie;
	float valoareMarfa;
};

struct Biblioteca initializare(int id, const char* denumire, int nrAngajati, char locatie, float valoareMarfa) {
	struct Biblioteca b;
	b.id = id;
	b.denumire = (char*)malloc((strlen(denumire) + 1) * sizeof(char));
	strcpy_s(b.denumire, (strlen(denumire) + 1, denumire);
	b.nrAngajati = nrAngajati;
	b.locatie = locatie;
	b.valoareMarfa = valoareMarfa;
	return b;
}