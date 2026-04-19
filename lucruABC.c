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

//functie pt inserare in arbore, ca regula ar fi daca id la produs inserat e mai mic decat id din nod curent => inserez in stanga
//daca e mai mare inserez in dreapta si daca e egal inseamna ca am duplicat
nodArb* inserareNod(nodArb* rad, produs p) {
	if (rad != NULL) {
		if (p.id < rad->info.id) {
			rad->stanga = inserareNod(rad->stanga, p);
			return rad;
		}
		else if(p.id > rad->info.id){
			rad->dreapta = inserareNod(rad->dreapta, p);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNod(p, NULL, NULL);
	}
}

//trebuie sa imi fac o functie de ordine radacina->stanga->dreapta
void preOrdine(nodArb* rad) {
	if (rad != NULL) {
		printf("\nCod=%d, Denumire=%s, Stoc=%d, Pret=%5.2f", rad->info.id, rad->info.denumire, rad->info.stoc, rad->info.pret);
		preOrdine(rad->stanga);
		preOrdine(rad->dreapta);
	}
}

//inca una dar de data asta cu ordine stanga->radacina->dreapta
void inOrdine(nodArb* rad) {
	if (rad != NULL) {
		inOrdine(rad->stanga);
		printf("\nCod=%d, Denumire=%s, Stoc=%d, Pret=%5.2f", rad->info.id, rad->info.denumire, rad->info.stoc, rad->info.pret);
		inOrdine(rad->dreapta);
	}
}

//si ultima in ordine stanga->dreapta->radacina
void postOrdine(nodArb* rad) {
	if (rad != NULL) {
		postOrdine(rad->stanga);
		postOrdine(rad->dreapta);
		printf("\nCod=%d, Denumire=%s, Stoc=%d, Pret=%5.2f", rad->info.id, rad->info.denumire, rad->info.stoc, rad->info.pret);
	}
}

//dezalocare arbore
void dezalocare(nodArb* rad) {
	if (rad != NULL) {
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->info.denumire);
		free(rad);
	}
}

//functie de numarare a produselor care sunt mai mari decat un prag anume
void nrProduseStoc(nodArb* rad, int* nr, int prag) {
	if (rad != NULL) {
		if (rad->info.stoc > prag) {
			(*nr)++;
			nrProduseStoc(rad->stanga, nr, prag);
			nrProduseStoc(rad->dreapta, nr, prag);
		}
	}
}

//salvare in vector a nodurilor frunza care au pret mai mare decat un prag anume
void salvareProduse(nodArb* rad, produs* vect, int* nr, float pretPrag) {
	if (rad != NULL) {
		if (rad->stanga == NULL && rad->dreapta == NULL && rad->info.pret > pretPrag) {
			vect[*nr].id = rad->info.id;
			vect[*nr].denumire = (char*)malloc((strlen(rad->info.denumire) + 1) * sizeof(char));
			strcpy_s(vect[*nr].denumire, strlen(rad->info.denumire, rad->info.denumire);
			vect[*nr].stoc = rad->info.stoc;
			vect[*nr].pret = rad->info.pret;
			(*nr)++;
		}
		salvareProduse(rad->stanga, vect, nr, pretPrag);
		salvareProduse(rad->dreapta, vect, nr, pretPrag);
	}
}

//functie de cautat max dintre 2 valori
int maxim(int a, int b) {
	int max = a;
	if (max < b) {
		max = b;
	}
	return max;
}


void main() {

}