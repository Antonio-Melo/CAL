/*
 * UtilFunctions.cpp
 */

#include "Ponto.h"
#include "Util.h"
#include <time.h>
#include <sys/timeb.h>


/**
 * function to fill list 'lp' with 'Ponto' objects read from 'is'
 */
void lerPontos(istream &is, vector<Ponto> &vp){
	double x, y;
	if (!is)
		return;
	while (!is.eof()) {
		is >> x >> y;
		Ponto p(x,y);
		vp.push_back(p);
	}
}
//---------------------------------------------------------------------------

/**
 * function to compare 'Ponto' based on 'X' or 'Y'
 */
double comparaPontos(Ponto p1, Ponto p2, int type) {
    if (type == X)
        return p1.x - p2.x;
    return p1.y - p2.y;
}
//---------------------------------------------------------------------------
/**
 * quickSort algorithm for 'std::vector<bestHistory>' by ascending X coordinate
 */
void quickSortX(vector<Ponto> &vp)
{
    quickSort(vp, 0, vp.size()-1, X);
}
//---------------------------------------------------------------------------

/**
 * quickSort algorithm for 'std::vector<bestHistory>' by ascending Y coordinate
 */
void quickSortY(vector<Ponto> &vp)
{
    quickSort(vp, 0, vp.size()-1, Y);
}
//---------------------------------------------------------------------------

void quickSort(vector<Ponto> &v, int left, int right, int type)
{
    if (right - left <= 50)    // if small vector
        insertionSort(v, left, right, type);
    else {
        Ponto p = median3(v, left, right, type);  // x is pivot
        int i = left; int j = right-1;            // partition step
        double comp;
        for(; ; ) {

            comp = -1;
            while (comp < 0) {
                comp = comparaPontos(v[++i], p, type);
            }

            comp = -1;
            while (comp < 0) {
                comp = comparaPontos(p, v[--j], type);
            }
            if (i < j)
                swap(v[i], v[j]);
            else break;
        }
        swap(v[i], v[right-1]);  // reset pivot
        quickSort(v, left, i-1, type);
        quickSort(v, i+1, right, type);
    }
}
//---------------------------------------------------------------------------

/**
 * choose pivot as the median of three values:
 * extremes and central value of vector
 */
Ponto & median3(vector<Ponto> &v, int left, int right, int type)
{
    int center = (left+right) /2;
    if (comparaPontos(v[center], v[left], type) < 0)
        swap(v[left], v[center]);

    if (comparaPontos(v[right], v[left], type) < 0)
        swap(v[left], v[right]);

    if (comparaPontos(v[right], v[center], type) < 0)
        swap(v[center], v[right]);

    swap(v[center], v[right-1]);     // put pivot in position 'right-1'
    return v[right-1];
}
//---------------------------------------------------------------------------

/**
 * for small vectors use a simple method - insertion sort
 */
void insertionSort(vector<Ponto> &v, int left, int right, int type)
{
    for (int i = left+1; i < right+1; i++)
    {
        Ponto tmp = v[i];
        int j;
        for (j = i; j > left && comparaPontos(tmp, v[j-1], type) < 0; j--)
            v[j] = v[j-1];
        v[j] = tmp;
    }
}
//---------------------------------------------------------------------------

/*
 * Print time
 */
// Something like GetTickCount but portable
// It rolls over every ~ 12.1 days (0x100000/24/60/60)
// Use GetMilliSpan to correct for rollover

int GetMilliCount()
{
  timeb tb;
  ftime( &tb );
  int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
  return nCount;
}
//---------------------------------------------------------------------------

int GetMilliSpan(int nTimeStart)
{
  int nSpan = GetMilliCount() - nTimeStart;
  if (nSpan < 0)
	  nSpan += 0x100000 * 1000;
  return nSpan;
}
//---------------------------------------------------------------------------



double nearestPoints_BF(vector<Ponto> &vp, vector<Ponto> &vMP)
{
	Ponto a,b;
	double d=DMAXIMUM;

	for(unsigned int i =0 ;i < vp.size();i++){
		for(unsigned int j=i+1; j < vp.size();j++){
			if(vp.at(i).distancia(vp.at(j)) < d){
				d =vp.at(i).distancia(vp.at(j));
				a = vp.at(i);
				b = vp.at(j);
			}
		}
	}

	vMP.push_back(a);
	vMP.push_back(b);

	return d;
}


//Código Bernardo Belchior
double nearestPoints_DC_aux(vector<Ponto> &vp, int p, int r, vector<Ponto> &vMP) {

	if(r == p+1) {
		vMP.resize(2);
		vMP[0] = vp[p];
		vMP[1] = vp[r];
		return (vp[p].distancia(vp[r]));
	}

	int m = (p+r)/2;

	vector<Ponto> vMPL;
	vector<Ponto> vMPR;
	double minDistL = nearestPoints_DC_aux(vp, p, m, vMPL);
	double minDistR = nearestPoints_DC_aux(vp, m+1, r, vMPR);
	double minDist = min(minDistL, minDistR);

	if(minDist == minDistL) {
		vMP = vMPL;
	} else {
		vMP = vMPR;
	}

	//Brute Force
	int mediumX = vp[m].x;

	int i;
	for(i = m - 1; i >= p; i--) {
		if(!(vp[i].x >= mediumX - minDist && vp[i].x <= mediumX + minDist))
			break;
	}
	i++;

	int j;
	for(j = m + 1; j <= r; j++) {
		if(!(vp[j].x >= mediumX - minDist && vp[j].x <= mediumX + minDist))
			break;
	}
	j--;

	if(j > i) {
		double curDist;
		for(int k = i; k <= j; k++) {
			for(int x = k + 1; x <= j; x++) {
				 curDist = vp[x].distancia(vp[k]);
				if(curDist < minDist) {
					minDist = curDist;
					vMP[0] = vp[k];
					vMP[1] = vp[x];
				}
			}
		}
	}

	return minDist;
}

double nearestPoints_DC(vector<Ponto> &vp, vector<Ponto> &vMP) {
	quickSortX(vp);

	return nearestPoints_DC_aux(vp, 0, vp.size() - 1, vMP);
}


