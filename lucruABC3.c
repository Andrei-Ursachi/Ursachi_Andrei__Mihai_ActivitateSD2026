#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Camion {
	int idCamion;
	int nrLocuri;
	float capacitateRezervor;
	char* nrInmatriculare;
	char* serieSasiu;
	int kilometraj;
};
typedef struct Camion Camion;

struct Nod {
	Camion info;
	struct Nod* stanga;
	struct Nod* dreapta;
};
typedef struct Nod Nod;

Camion citireCamionDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Camion c1;
	aux = strtok(buffer, sep);
	c1.idCamion = atoi(aux);
	c1.nrLocuri = atoi(strtok(NULL, sep));
	c1.capacitateRezervor = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	c1.nrInmatriculare = malloc(strlen(aux) + 1);
	strcpy_s(c1.nrInmatriculare, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	c1.serieSasiu = malloc(strlen(aux) + 1);
	strcpy_s(c1.serieSasiu, strlen(aux) + 1, aux);
	c1.kilometraj = atoi(strtok(NULL, sep));
	return c1;
}

void afisareCamion(Camion camion) {
	printf("Id camion: %d\n", camion.idCamion);
	printf("Nr locuri: %d\n", camion.nrLocuri);
	printf("Capacitate: %.2f\n", camion.capacitateRezervor);
	printf("Nr inmatriculare: %s\n", camion.nrInmatriculare);
	printf("Serie sasiu: %s\n", camion.serieSasiu);
	printf("Kilometraj: %d\n", camion.kilometraj);
}

void adaugareInArbore(Nod** rad, Camion camionNou) {
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = camionNou;
		nod->stanga = NULL;
		nod->dreapta = NULL;
		*rad = nod;
	}
	else {
		if ((*rad)->info.idCamion > camionNou.idCamion) {
			adaugareInArbore(&(*rad)->stanga, camionNou);
		}
		if ((*rad)->info.idCamion < camionNou.idCamion) {
			adaugareInArbore(&(*rad)->dreapta, camionNou);
		}
	}
}

Nod* citireArboreDinFisier(const char* numeFisier) {
	Nod* rad = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			Camion c = citireCamionDinFisier(f);
			adaugareInArbore(&rad, c);
		}
	}
	fclose(f);
	return rad;
}

void afisareInOrdine(Nod* rad) {
	if (rad) {
		afisareInOrdine(rad->stanga);
		afisareCamion(rad->info);
		afisareInOrdine(rad->dreapta);
	}
}

void afisarePreOrdine(Nod* rad) {
	if (rad) {
		afisareCamion(rad->info);
		afisareInOrdine(rad->stanga);	
		afisareInOrdine(rad->dreapta);
	}
}

void afisarePostOrdine(Nod* rad) {
	if (rad) {
		afisareInOrdine(rad->stanga);	
		afisareInOrdine(rad->dreapta);
		afisareCamion(rad->info);
	}
}

void dezalocareArboreCamioane(Nod** rad) {
	if (*rad) {
		dezalocareArboreCamioane(&(*rad)->stanga);
		dezalocareArboreCamioane(&(*rad)->dreapta);
		free((*rad)->info.nrInmatriculare);
		free((*rad)->info.serieSasiu);
		free(*rad);
		*rad = NULL;
	}
}

Camion getCamionById(Nod* rad, int id) {
	Camion c;
	c.idCamion = -1;
	if (rad) {
		if (rad->info.idCamion == id) {
			c = rad->info;
			c.nrInmatriculare = malloc(sizeof(int) * (strlen(rad->info.nrInmatriculare) + 1));
			strcpy_s(c.nrInmatriculare, strlen(rad->info.nrInmatriculare) + 1, rad->info.nrInmatriculare);

			c.serieSasiu = malloc(sizeof(int) * (strlen(rad->info.serieSasiu) + 1));
			strcpy_s(c.serieSasiu, strlen(rad->info.serieSasiu) + 1, rad->info.serieSasiu);

		}
		if (id < rad->info.idCamion) {
			c = getCamionById(rad->stanga, id);
		}
		if (id > rad->info.idCamion) {
			c = getCamionById(rad->dreapta, id);
		}
	}
	return c;
}

int nrNoduriArbore(Nod* rad) {
	if (rad) {
		return nrNoduriArbore(rad->stanga) + nrNoduriArbore(rad->dreapta) + 1;
	}
	else {
		return 0;
	}
}

int maxim(int a, int b) {
	return (a > b ? a : b);
}

int inaltimeArbore(Nod* rad) {
	if (rad) {
		return maxim(inaltimeArbore(rad->stanga), inaltimeArbore(rad->dreapta) + 1);
	}
	else {
		return 0;
	}
	
}

int calculNrTotalLocuri(Nod* rad) {
	if (rad) {
		return rad->info.nrLocuri + calculNrTotalLocuri(rad->stanga) + calculNrTotalLocuri(rad->dreapta);
	}
	else {
		return 0;
	}
}

void main() {
	Nod* rad = citireArboreDinFisier("suportLucruABC3.txt");
	afisareInOrdine(rad);

	printf("Numar noduri: %d \n", nrNoduriArbore(rad));

	printf("Inaltime arbore: %d \n", inaltimeArbore(rad));
	printf("Locuri totale: %d \n", calculNrTotalLocuri(rad));
}