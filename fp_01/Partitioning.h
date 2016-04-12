/*
 * Partioning.h
 */

#ifndef PARTITIONING_H_
#define PARTITIONING_H_

#include "Defs.h"

/*Implementa a fun��o s(n,k) usando recursividade*/
int s_recursive(int n,int k){
	if(k<n && k>1){
		return s_recursive(n-1,k-1)+k*s_recursive(n-1,k);
	}else{
		return 1;
	}
}

/*Implementa a fun��o b(n) usando recursividade*/
int b_recursive(int n){
	int sum = 0;
	for(int i =0; i < n;i++){
		sum += s_recursive(n,i);
	}
	return sum;
}

/*Implementa a fun��o s(n,k) usando programa��o din�mica*/
int s_dynamic(int n,int k) {
	int s_array1[n];
	int s_array2[n];

	for (int i = 0; i < n; i++) {		//n
		for (int j = 0; j <= i; j++) {	//k
			if (j == 0 || j == i) {
				s_array2[j] = 1;
			}
			else {
				s_array2[j] = (j+1)*s_array1[j] + s_array1[j-1];
			}
		}

		for (int j = 0; j < n; j++) {
			s_array1[j] = s_array2[j];
		}
	}

	return s_array2[k-1];
}

/*Implementa a fun��o b(n) usando programa��o din�mica*/
int b_dynamic(int n){
	int sum=0;
	for(int i =1; i <= n;i++){
		sum += s_dynamic(n,i);
	}
	return sum;
}

#endif /* SUM_H_ */
