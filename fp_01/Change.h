/*
 * Change.h
 */

#ifndef CHANGE_H_
#define CHANGE_H_

#include "Defs.h"

/* Calcula o troco para n c�ntimos, utilizando o n�mero m�nimo de moedas, tendo apenas dispon�veis
 * moedas de 1, 2 e 5 c�ntimos.
 *
 * Devolve:
 * Uma string que cont�m com a indica��o, para cada n, a combina��o de moedas a utilizar.
 * Por exemplo: troco de 1 c�ntimo: 1 moeda de 1
 * 				troco de 2 c�ntimos: 1 moeda de 2
 * 				troco de 3 c�ntimos: 1 moeda de 1, 1 moeda de 2
 * 				(...)
 * A string devolvida representa os valores das moedas (separadas por virgula) para cada n (separado por ponto e v�rgula)
 * Exemplo: 1;2;1,2;2,2;5;1,5;...
 * */
string calcChange(int n){

	stringstream troco;
	vector< vector<int> > vstring;

	if (n ==0){
		return "";
	}else{
		vector<int> temp1;
		temp1.push_back(1);
		vstring.push_back(temp1);
		//cout << vstring.at(0).at(0) << vstring.at(0).size();
	}

	int soma=1;

	for(int i = 0; soma != n; i++){
		soma =0;
		vector<int> temp;

		if(vstring.at(i).at(0) == 1 ){   // 1
			if(vstring.at(i).size() == 1){  // Só tem 1
				temp.push_back(2);
				vstring.push_back(temp);
				//cout << vstring.at(i+1).at(0);
			}else{
				if(vstring.at(i).at(1) == 2){ // depois do 1 tem um 2
					temp.push_back(2);
					for(unsigned int x=1;x < vstring.at(i).size();x++){
						temp.push_back(vstring.at(i).at(x));
					}
					vstring.push_back(temp);
				}else if (vstring.at(i).at(1) == 5){ //depois do 1 tem um 5
					temp.push_back(2);
					for (unsigned int x = 1; x < vstring.at(i).size(); x++) {
						temp.push_back(vstring.at(i).at(x));
					}
					vstring.push_back(temp);
				}
			}
		} else if (vstring.at(i).at(0) == 2) { //2
			if (vstring.at(i).size() == 1) {  // Só tem 2
				temp.push_back(1);
				temp.push_back(2);
				vstring.push_back(temp);
			} else {
				if (vstring.at(i).at(1) == 2) {   //depois do 2 tem um 2
					temp.push_back(5);
					for (unsigned int x = 2; x < vstring.at(i).size(); x++) {
						temp.push_back(vstring.at(i).at(x));
					}
					vstring.push_back(temp);
				}else if(vstring.at(i).at(1)==5){ //depois do 2 tem um 5
					temp.push_back(1);
					for (unsigned int x = 0; x < vstring.at(i).size(); x++) {
						temp.push_back(vstring.at(i).at(x));
					}
					vstring.push_back(temp);
				}
			}
		} else if (vstring.at(i).at(0) == 5) { //5
			temp.push_back(1);
			for (unsigned int x = 0; x < vstring.at(i).size(); x++) {
				temp.push_back(vstring.at(i).at(x));
			}
			vstring.push_back(temp);
		}
		for (int h = 0; h < temp.size(); h++) {
			soma = soma + temp.at(h);
		}
	}

	for(int i =0;i<vstring.size();i++){
		for(int h =0;h<vstring.at(i).size();h++){
			if(h +1 !=vstring.at(i).size()){
				troco << vstring.at(i).at(h)<< ",";
			}else{
				troco << vstring.at(i).at(h);
			}
		}
		troco << ";";
	}

	return troco.str();
}


#endif /* CHANGE_H_ */
