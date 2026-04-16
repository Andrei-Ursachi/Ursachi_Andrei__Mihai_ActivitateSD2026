#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structura de prezentare obiect
typedef struct {
	int id;
	char* denumire;
	int stoc;
	float pret;
}produs;

//aici am de facut nodul pt ABC
// are info - care e un produs; pointer la stanga si pointer la dreapta
typedef struct {
	produs info;
	struct nodArb* stanga;
	struct nodArb* dreapta;
}nodArb;

//urmatorul pas e sa imi fac o functie care creaza un nod, aici dau produsul si apoi cei doi pointeri - unul pt stanga unul pt dreapta
//e ca un constructor de la poo
nodArb* creareNod(produs p, nodArb* stanga, nodArb* dreapta) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.id = p.id;
	nou->info.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy_s(nou->info.denumire, strlen(p.denumire) + 1, p.denumire);
	nou->info.stoc = p.stoc;
	nou->info.pret = p.pret;
	nou->stanga = stanga;
	nou->dreapta = dreapta;
	return nou;
}