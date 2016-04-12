/*
 * Sum.h
 */

#ifndef SUM_H_
#define SUM_H_

#include "Defs.h"

/* Calcula, numa sequ�ncia de n n�meros (n > 0), para cada subsequ�ncia de m n�meros (m <= n, m > 0),
 * o �ndice i a partir do qual a soma s dos valores dessa subsequ�ncia � m�nimo.
 *
 * Argumentos:
 * 	sequence - Array com a sequ�ncia
 * 	size - Tamanho da sequ�ncia
 *
 * Devolve:
 * Uma string que cont�m com a indica��o do �ndice i e somat�rio s, para cada m
 * i[0],s[0];i[1],s[1],i[2],s[2]...
 * Exemplo: 1,4;9,1;11,2;18,1;22,0;
 *
 *
 *
 *
 */

string searchMin(int *array, int size);

string calcSum(int* sequence, int size) {
	string sum = "";
	int sumArray[size];
	for (int i = 0; i < size; i++) {
		sumArray[i] = sequence[i];
	}
	sum += searchMin(sequence, size) + ";";

	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size-i; j++) {
			sumArray[j] += sequence[j+i];
		}

		sum += searchMin(sumArray, size-i) + ";";
	}

	return sum;
}

string searchMin(int *array, int size) {
	int min = array[0];
	int pos = 0;

	for (int i = 0; i < size; i++) {
		if (array[i] < min) {
			min = array[i];
			pos = i;
		}
	}

	stringstream convert;
	convert << min << "," << pos;

	return convert.str();
}
#endif /* SUM_H_ */
