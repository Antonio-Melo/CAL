/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j]=values[i][j];

	foundTheSolution = false;
}


void Labirinth::initializeVisited(int x, int y)
{
	for (int i = 0; i < 10; i++)
		for (int a = 0; a < 10; a++){
			visited[i][a] = false;
			if(labirinth[i][a] == 0){
				visited[i][a] = true;
			}
		}
	visited[y][x] = true;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int a = 0; a < 10; a++)
			cout << labirinth[i][a] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{
	initializeVisited(x,y);
	findGoal2(x,y);
	return foundTheSolution;
}


void Labirinth::findGoal2(int x, int y)
{
	visited[y][x] = true;
/*
	for(int z = 0; z < 10;z++){
		for(int i = 0; i <10;i++){
			cout << visited[z][i] +"";
		}
		cout << endl;
	}*/

	if(labirinth[y][x] == 2){
		foundTheSolution = true;
		return;
	}else{
		//Check possible ways
		if(visited[y-1][x] == false){
			findGoal2(x, y - 1);
		}
		if (visited[y + 1][x] == false) {
			findGoal2(x, y + 1);
		}
		if (visited[y][x+1] == false) {
			findGoal2(x+1,y);
		}
		if (visited[y][x-1] == false) {
			findGoal2(x-1, y);
		}
	}
}


