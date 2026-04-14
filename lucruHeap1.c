#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>


typedef struct{
	int prioritate;
	char* numeClient;
	float valoare;
} comanda;

typedef struct{
	comanda* vect;
	int nrElem;
} heap;

void filtrare(heap h, int index){
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElem && h.vect[indexSt].prioritate < h.vect[indexRad].prioritate) {
		indexRad = indexSt;
	}
		
	if (indexDr < h.nrElem && h.vect[indexDr].prioritate < h.vect[indexRad].prioritate) {
		indexRad = indexDr;
	}
		

	if (index != indexRad){
		comanda aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;
		filtrare(h, indexRad);
	}
}

void afisareHeap(heap h){
	for (int i = 0; i < h.nrElem; i++) {
		printf("\nPrioritate = %d, Nume client = %s, Valoare = %5.2f",h.vect[i].prioritate, h.vect[i].numeClient, h.vect[i].valoare);
	}	
}

void dezalocareHeap(heap h){
	for (int i = 0; i < h.nrElem; i++) {
		free(h.vect[i].numeClient);
	}	
	free(h.vect);
}

heap inserare(heap h, comanda noua){
	comanda* vectNou = (comanda*)malloc((h.nrElem + 1) * sizeof(comanda));
	for (int i = 0; i < h.nrElem; i++) {
		vectNou[i] = h.vect[i];
	}	
	vectNou[h.nrElem] = noua;
	h.nrElem++;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}

heap extragere(heap h, comanda* extrasa){
	comanda* vectNou = (comanda*)malloc((h.nrElem - 1) * sizeof(comanda));
	comanda aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = aux;

	*extrasa = h.vect[h.nrElem - 1];

	h.nrElem--;
	for (int i = 0; i < h.nrElem; i++) {
		vectNou[i] = h.vect[i];
	}
	free(h.vect);
	h.vect = vectNou;

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}

void main(){
	heap h;
	char buffer[20];

	FILE* f = fopen("suportHeap1.txt", "r");
	if (f == NULL) {
		printf("Fisierul nu a fost gasit");
		return;
	}
	fscanf_s(f, "%d", &h.nrElem);
	h.vect = (comanda*)malloc(h.nrElem * sizeof(comanda));
	for (int i = 0; i < h.nrElem; i++){
		fscanf_s(f, "%d", &h.vect[i].prioritate);
		fscanf_s(f, "%19s", buffer, (unsigned)20);
		h.vect[i].numeClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy_s(h.vect[i].numeClient, strlen(buffer) + 1, buffer);
		fscanf_s(f, "%f", &h.vect[i].valoare);
	}
	fclose(f);

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	afisareHeap(h);

	printf("\n--------------------\n");

	/*comanda noua;
	printf("Prioritate=");
	fscanf_s("%d", &noua.prioritate);
	printf("Nume client=");
	fscanf_s("%s", buffer);
	noua.numeClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy_s(noua.numeClient, strlen(buffer) + 1, buffer);
	printf("Valoare=");
	fscanf_s("%f", &noua.valoare);

	h = inserare(h, noua);

	afisareHeap(h);*/

	printf("\n--------------------\n");

	comanda extrasa;
	h = extragere(h, &extrasa);
	printf("\nExtras -> Prioritate = %d, Nume client = %s, Valoare = %5.2f",extrasa.prioritate, extrasa.numeClient, extrasa.valoare);

	afisareHeap(h);

	printf("\n--------------------\n");
	comanda* vectSortat = (comanda*)malloc(h.nrElem * sizeof(comanda));
	int nr = h.nrElem;
	for (int i = 0; i < nr; i++){
		h = extragere(h, &extrasa);
		vectSortat[i] = extrasa;
	}
	for (int i = 0; i < nr; i++) {
		printf("\nSortat -> Prioritate = %d, Nume client = %s, Valoare = %5.2f", vectSortat[i].prioritate, vectSortat[i].numeClient, vectSortat[i].valoare);
	}	

	for (int i = 0; i < nr; i++) {
		free(vectSortat[i].numeClient);
	}	
	free(vectSortat);
	dezalocareHeap(h);
}