#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct
{
	int prioritate;
	char* numeClient;
	float valoare;
} comanda;

typedef struct
{
	comanda* vect;
	int nrElem;
} heap;

void filtrare(heap h, int index)
{
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElem && h.vect[indexSt].prioritate <
		h.vect[indexRad].prioritate)
		indexRad = indexSt;

	if (indexDr < h.nrElem && h.vect[indexDr].prioritate <
		h.vect[indexRad].prioritate)
		indexRad = indexDr;

	if (index != indexRad)
	{
		comanda aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

void main(){

}