/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conte�do inicial.
 * Lan�a excep��o IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conte�do actual (s� para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku j� est� completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}



/**
 * Resolve o Sudoku.
 * Retorna indica��o de sucesso ou insucesso (sudoku imposs�vel).
 */
bool Sudoku::solve()
{
	int nx,ny;


	if(!nextPos(nx,ny)){
		return true;
	}

	for(int n = 1; n <= 9;n++){
		if(check(n,nx,ny)){
			numbers[nx][ny] = n;
			countFilled++;

			if(solve()){
				return true;
			}

			numbers[nx][ny] = 0;
			countFilled--;
		}
	}


	return false;

}

bool Sudoku::nextPos(int & nx, int & ny ){
	for(nx =0; nx <9;nx++){
		for(ny = 0;ny <9; ny++){
			if(numbers[nx][ny] == 0){
				return true;
			}
		}
	}
	return false;
}

bool Sudoku::check(int i,int x,int y){
	int tempx,tempy;

	//Line
	for(int j = 0; j <9;j++){
		if(numbers[x][j] == i){
			return false;
		}
	}
	//Column
	for (int j = 0; j < 9; j++) {
		if (numbers[j][y] == i) {
			return false;
		}
	}
	//3x3
	if (x < 3) {
		tempx = 0;
	} else if (x >= 3 && x < 6) {
		tempx = 3;
	} else {
		tempx = 6;
	}

	if (y < 3) {
		tempy = 0;
	} else if (y >= 3 && y < 6) {
		tempy = 3;
	} else {
		tempy = 6;
	}

	for(int j =0; j < 3; j++){
		for(int h = 0 ; h <3; h++){
			if(numbers[tempx+j][tempy+h] == i) {
				return false;
			}
		}
	}

	return true;
}



/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
