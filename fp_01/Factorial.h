/*
 * Factorial.h
 */

#ifndef FACTORIAL_H_
#define FACTORIAL_H_

#include "Defs.h"

/*Calcula o factorial de um valor de entrada n usando recursividade*/
unsigned long long factorialRecurs(int n){

	if(n ==0 || n ==1){
		return 1;
	}else
		return n * factorialRecurs(n-1);
}

/*Calcula o factorial de um valor de entrada n usando programa��o din�mica*/
int factorialDinam(int n){
	int r;

	for(int i=1;i<=n;i++){
		if(i == 0){
			r =1;
		}else
			r= r*i;
	}
	return r;
}

/*Calcula o factorial de todos os valores at� n (n >=0), colocando os resultados numa array*/
int* factorialDinamArray(int n){
	 int *array;
	 array = new int[n+1];

	 for(int i =0;i <= n;i++){
		 if(i == 0){
			 array[i]=1;
		 }else{
			 array[i] = array[i-1]*i;
		 }
	 }
	return array;
}

#endif /* FACTORIAL_H_ */
