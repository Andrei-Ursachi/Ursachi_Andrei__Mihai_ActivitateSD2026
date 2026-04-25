// lucru din AT poate fi ignorat la activitate
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//formula deducere pozitii s->2p +1 si d->2p+2 //p fiind pozitia nodului parinte
//formula aflat pozitia ultimului parinte p = n-2/2
//heap sort inseamna ca min heap este sortat descrescator si max heap sortat crescator

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

//creare structura pentru Heap
//un vector de elemente, lungimea vectorului si numarul de elemente din vector
struct Heap {
	int lungime;
	Masina* masini;
	int nrElemente;
};
typedef struct Heap Heap;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
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

Heap initializareHeap(int lungime) {
	//initializeaza heap-ul cu 0 elemente 
	//dar cu o lungime primita ca parametru
	Heap heap;
	heap.lungime = lungime;
	heap.masini = malloc(sizeof(Masina) * lungime);
	heap.nrElemente = 0;
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	//filtreaza heap-ul pentru nodul a carei pozitie o primeste ca parametru
	int pozStanga = 2 * pozitieNod + 1;
	int pozDreapta = 2 * pozitieNod + 2;
	int pozMin = pozitieNod;
	if (pozStanga<heap.nrElemente && heap.masini[pozMin].pret > heap.masini[pozStanga].pret) {
		pozMin = pozStanga;
	}
	if (pozDreapta<heap.nrElemente && heap.masini[pozMin].pret > heap.masini[pozDreapta].pret) {
		pozMin = pozDreapta;
	}
	if (pozMin != pozitieNod) {
		Masina aux = heap.masini[pozMin];
		heap.masini[pozMin] = heap.masini[pozitieNod];
		heap.masini[pozitieNod] = aux;
		if (pozMin < (heap.nrElemente - 2) / 2) {
			filtreazaHeap(heap, pozMin);
		}
	}
}

Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
	//citim toate masinile din fisier si le stocam intr-un heap 
	// pe care trebuie sa il filtram astfel incat sa respecte 
	// principiul de MAX-HEAP sau MIN-HEAP dupa un anumit criteriu
	// sunt citite toate elementele si abia apoi este filtrat vectorul

	Heap heap = initializareHeap(10);
	heap.nrElemente = 0;
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			heap.masini[heap.nrElemente++] = citireMasinaDinFisier(f);
		}
	}
	fclose(f);
	for (int i = (heap.nrElemente - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afisareHeap(Heap heap) {
	//afiseaza elementele vizibile din heap
	for (int i = 0; i < heap.nrElemente; i++) {
		afisareMasina(heap.masini[i]);
	}
}

void afiseazaHeapAscuns(Heap heap) {
	//afiseaza elementele ascunse din heap
	for (int i = heap.nrElemente; i < heap.lungime; i++) {
		afisareMasina(heap.masini[i]);
	}
}

Masina extrageMasina(Heap* heap) {
	//extrage si returneaza masina de pe prima pozitie
	//elementul extras nu il stergem...doar il ascundem
	Masina masina;
	masina.id = -1;
	if (heap->nrElemente > 0) {
		masina = heap->masini[0];
		heap->masini[0] = heap->masini[heap->nrElemente - 1];
		heap->masini[heap->nrElemente - 1] = masina;
		heap->nrElemente--;
		for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
	}
	return masina;
}


void dezalocareHeap(Heap* heap) {
	//sterge toate elementele din Heap
	for (int i = 0; i < heap->lungime; i++) {
		free(heap->masini[i].model);
		free(heap->masini[i].numeSofer);
	}
	free(heap->masini);
	heap->masini = NULL;
	heap->lungime = 0;
	heap->nrElemente = 0;
}

int main() {
	Heap heap = citireHeapDeMasiniDinFisier("suportLucruHeap2.txt");
	afisareHeap(heap);

	printf("Extrageri: \n");
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));

	printf("Heap ramas vizibil: \n");
	afisareHeap(heap);

	printf("Elemente ascunse: \n");
	afiseazaHeapAscuns(heap);

	return 0;
}