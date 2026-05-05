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
	struct Nod* stanga;
};
typedef struct Nod Nod;

Camion citireMasinaDinFisier(FILE* file) {
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
	c1.kilometraj = *strtok(NULL, sep);
	return c1;
}

void afisareCamion(Camion camion) {
	printf("Id camion: %d\n", camion.idCamion);
	printf("Nr locuri: %d\n", camion.nrLocuri);
	printf("Capacitate: %.2f\n", camion.capacitateRezervor);
	printf("Nr inmatriculare: %.s\n", camion.nrInmatriculare);
	printf("Serie sasiu: %.s\n", camion.serieSasiu);
	printf("Kilometraj: %.d\n", camion.serieSasiu);
}

void adaugareInArbore(Nod** rad, Camion camionNou) {

}