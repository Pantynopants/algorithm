#ifndef __ROUTE_H__
#define __ROUTE_H__


#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>  
#include <algorithm>  
#include <cstring>  
using namespace std;


const int maxnum = 100;
const int maxint = 999999;
const int inf = 999999;



struct AtoB{ 
    int dist;
    int id;
    int route[50];
}; 

void searchPath(int *prev,int v, int u);

int Dijkstra(int n, int v, int *dist, int *prev, AtoB c[maxnum][maxnum]);

int midPath(int IncludingSetLength, int IncludingSet[50], AtoB c[maxnum][maxnum]);

void search_route(char *graph[5000], int edge_num, char *condition);

#endif
