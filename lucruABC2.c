// lucru din AT poate fi ignorat la activitate
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-un arbore binar de cautare
struct Nod {
	Masina info;
	struct Nod* stanga;
	struct Nod* dreapta;
};
typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}


void adaugaMasinaInArbore(Nod** rad, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = masinaNoua;
		nod->dreapta = NULL;
		nod->stanga = NULL;
		*rad = nod;
	}
	else {
		if ((*rad)->info.id > masinaNoua.id) {
			adaugaMasinaInArbore(&(*rad)->stanga, masinaNoua);
		}
		if ((*rad)->info.id < masinaNoua.id) {
			adaugaMasinaInArbore(&(*rad)->dreapta, masinaNoua);
		}
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	Nod* rad = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			Masina m = citireMasinaDinFisier(f);
			adaugaMasinaInArbore(&rad, m);
		}
		fclose(f);
	}
	return rad;
}

//pre ordine pt ca R S D
//in ordine pt ca S R D
//post ordine pt ca S D R

void afisareMasiniDinArbore(Nod* rad) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
	if (rad) {
		afisareMasiniDinArbore(rad->stanga);
		afisareMasina(rad->info);
		afisareMasiniDinArbore(rad->stanga);
	}
}

void afisarePreordine(Nod* rad) {
	if (rad) {
		afisareMasina(rad->info);
		afisarePreordine(rad->stanga);
		afisarePreordine(rad->stanga);
	}
}


void dezalocareArboreDeMasini(Nod** rad) {
	//sunt dezalocate toate masinile si arborele de elemente
	if (*rad) {
		dezalocareArboreDeMasini(&(*rad)->stanga);
		dezalocareArboreDeMasini(&(*rad)->dreapta);
		free((*rad)->info.model);
		free((*rad)->info.numeSofer);
		free(*rad);
		*rad = NULL;
	}
}

Masina getMasinaByID(Nod* rad, int id) {
	Masina m;
	m.id = -1;
	if(rad) {
		if (rad->info.id == id) {
			m = rad->info;
			m.model = malloc(sizeof(char) * (strlen(rad->info.model) + 1));
			strcpy_s(m.model, strlen(rad->info.model) + 1,rad->info.model);

			m.numeSofer = malloc(sizeof(char) * (strlen(rad->info.numeSofer) + 1));
			strcpy_s(m.model, strlen(rad->info.numeSofer) + 1, rad->info.numeSofer);
		}
		if (id < rad->info.id) {
			m = getMasinaByID(rad->stanga, id);
		}

		if (id > rad->info.id) {
			m = getMasinaByID(rad->dreapta, id);
		}
	}
	return m;
}

int determinaNumarNoduri(Nod* rad) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	if (rad) {
		return determinaNumarNoduri(rad->stanga) + determinaNumarNoduri(rad->dreapta) + 1;
	}
	else {
		return 0;
	}
}

int maxim(int a, int b) {
	return (a > b ? a : b);
}

int calculeazaInaltimeArbore(Nod* rad) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	if (rad) {
		return maxim(calculeazaInaltimeArbore(rad->stanga), calculeazaInaltimeArbore(rad->dreapta)) + 1;
	}
	return 0;
}

float calculeazaPretTotal(Nod* rad) {
	//calculeaza pretul tuturor masinilor din arbore.
	if (rad) {
		return rad->info.pret + calculeazaPretTotal(rad->stanga) + calculeazaPretTotal(rad->dreapta);
	}
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* rad, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	if (rad) {
		float suma = calculeazaPretulMasinilorUnuiSofer(rad->stanga, numeSofer) + calculeazaPretulMasinilorUnuiSofer(rad->dreapta, numeSofer);
		if (strcmp(rad->info.numeSofer, numeSofer) == 0) {
			suma += rad->info.pret;
		}
		return suma;
	}
	return 0;
}

int main() {
	Nod* rad = citireArboreDeMasiniDinFisier("suportLucruHeap2.txt");
	afisarePreordine(rad);

	printf("Masina cautata: \n");
	afisareMasina(getMasinaByID(rad, 10));

	printf("Numar noduri: %d \n", determinaNumarNoduri(rad));

	printf("Inaltime arbore: %d \n", calculeazaInaltimeArbore(rad));
	printf("Pret total: %.2f \n", calculeazaPretTotal(rad));
	printf("Suma preturilor masinilor unui sofer: %.2f \n", calculeazaPretulMasinilorUnuiSofer(rad, "Ionescu"));

	dezalocareArboreDeMasini(&rad);


	return 0;
}