#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Avion Avion;
typedef struct Nod Nod;

struct Avion {
	char* model;
	int nrPasageri;
	float greutate;
};

struct Nod {
	Avion info;
	Nod* next;
};

Avion initializare(const char* model, int nrPasageri, float greutate) {
	Avion avion;
	avion.greutate = greutate;
	avion.nrPasageri = nrPasageri;
	avion.model = (char*)malloc(sizeof(char) * (strlen(model) + 1));
	strcpy_s(avion.model, strlen(model) + 1, model);
	return avion;
}

void afisare(Avion avion) {
	printf("Avionul %s va decola cu %d pasageri iar greutatea aproximativa este de %.2f.", avion.model, avion.nrPasageri, avion.greutate);
}

//functia de inserare in stiva, var varf o sa-mi fie ADRESA pointer catre primul nod din stiva
//fac nod** pt ca vreau sa mofic pointerul original
void push(Nod** varf, Avion avion) {
	Nod* nou = (Nod*)malloc(sizeof(Nod)); //creez nod nou
	nou->next = *varf; //nod nou pointeaza catre varf vechi
	nou->info = avion; //copiez informatia in nod nou
	*varf = nou; //aici varful devine noul noud al stivei
}

//functie de scoaterea unui element din inceputul listei
//pt lista e LIFO pt coada FIFO
Avion pop(Nod** varf) {
	if (*varf == NULL) {
		return initializare(NULL, 0, 0);
	}
	Avion avion;
	avion = (*varf)->info; //retin informatia din primul nod
	Nod* aux = *varf; //pastrez adresa nodului care va fi sters
	*varf = (*varf)->next; //mut inceputul liste la urmatorul nod
	free(aux);
	return avion;
}

//functie de inserare la sfarsit
void put(Nod** coada, Avion avion) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL; //fac nod nou care o sa fie ultimul
	nou->info = avion;
	if (*coada == NULL) {
		*coada = nou; //daca lista e goala, nou devine primul
	}
	else {
		Nod* aux = *coada;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next=nou; //daca nu e goala, pornesc de la primul ajung pana la ultimul unde leg ultimul nod de primul
	}
}

void main() {
	Nod* stiva = NULL;
	push(&stiva, initializare("A320", 300, 420.6));
	push(&stiva, initializare("A220", 100, 220.6));
	push(&stiva, initializare("A350F", 50, 1420.6));

	Avion avion;
	printf("\nParcurgere stiva: \n");
	while (stiva != NULL) {
		avion = pop(&stiva);
		afisare(avion);
		free(avion.model);
	}

	Nod* coada = NULL;
	push(&coada, initializare("A320", 300, 420.6));
	push(&coada, initializare("A220", 100, 220.6));
	push(&coada, initializare("A350F", 50, 1420.6));
	printf("\nParcurgere coada: \n");
	while (coada != NULL) {
		avion = pop(&coada);
		afisare(avion);
		free(avion.model);
	}
}