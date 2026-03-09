#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<malloc.h>
#include<stdio.h>
typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	int nrUsi;
	char* marca;
};

struct Nod {
	Masina info;
	Nod* next;
};

//constructor obiecte
Masina initializare(const char* marca, int nrUsi) {
	Masina masina;
	if (nrUsi > 1) {
		masina.nrUsi = nrUsi;
	}
	masina.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy_s(masina.marca, strlen(marca) + 1, marca);
	return masina;
}

Nod* creareNod(Masina masina, Nod* next) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masina;
	nou->next = next;
	return nou;
}

Nod* inserareSfarsit(Nod* cap, Masina masina) {
	Nod* nou = creareNod(masina, NULL);
	if (cap) {
		Nod* temp = cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		cap = nou;
	}
	return cap;
}

Nod* inserareInceput(Nod* cap, Masina masina) {
	Nod* nou = creareNod(masina, cap);
	return nou;
}

void afisareMasina(Masina masina) {
	printf("Masina %s are %d portiere. \n", masina.marca, masina.nrUsi);
}

void afisareListaMasini(Nod* cap) {
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void stergereLista(Nod* cap) {
	while (cap) {
		Nod* aux = cap;
		cap = cap->next;
		free(aux->info.marca);
		free(aux);
	}
	return cap;
}

void main() {
	Masina masina = initializare("volvo", 5);
	Nod* node = creareNod(masina, NULL);
	Nod* cap = NULL;
	cap = inserareSfarsit(cap, initializare("Mercedes", 5));
	cap = inserareSfarsit(cap, initializare("BMW", 2));
	cap = inserareSfarsit(cap, initializare("Dacia", 6));
	cap = inserareSfarsit(cap, initializare("KIA", 3));

	afisareListaMasini(cap);
	cap = inserareInceput(cap, initializare("Renault", 5));
	afisareListaMasini(cap);

}