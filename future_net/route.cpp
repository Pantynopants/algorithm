
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <string.h>
int inf = 99999999;

struct AtoB{ 
    int dist;
    int id;
    int route[50];
}; 
//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
    //unsigned short result[] = {2, 6, 4};
    //示例中的一个解

    AtoB distM[edge_num][edge_num];
    int startPoi;
    int finPoi;
    int access[50];
    //init the matrix
	for (int i = 0; i < edge_num; ++i)
	{
		for (int j = 0; j < edge_num; ++j)
		{
			if (i == j)
			{
				distM[i][j].dist = 0;
			}else{
				distM[i][j].dist = inf;
			}
		}
	}

    for (int i = 0; i < edge_num; i++){
    	//for (int j = 0; j < 7; j=j+2){
        	int begin = ((int)*(topo[i]+2) - 48);
        	int end = ((int)*(topo[i]+4) - 48);

        	distM[begin][end].id = ((int)*(topo[i]) - 48);
        	
        	distM[begin][end].dist = ((int)*(topo[i]+6)-48);
        	//printf("%d ",distM[begin][end]);
    	//}
    }

    for (int i = 0; i < edge_num; ++i)
	{
		for (int j = 0; j < edge_num; ++j)
		{
			printf("%d\t",distM[i][j].dist);
		}
		printf("\n");
	}

    int nodeNum = 0;

    for (int i = 0; i < edge_num; ++i)
	{
		for (int j = 0; j < edge_num; ++j)
		{
			for (int k = 0; k < edge_num; ++k)
			{
				if (distM[j][k].dist > distM[j][i].dist + distM[i][k].dist)
				{
					distM[j][k].dist = distM[j][i].dist + distM[i][k].dist;
					distM[j][k].route[nodeNum] = i;
					//printf("\n\n%d\n\n", i);
					nodeNum++;				
				}
			}
		}
	}
	//printf("%d\n",nodeNum);

	// for (int i = 0; i < edge_num; ++i){
	// 	for (int j = 0; j < edge_num; ++j){
	// 		for (int k = 0; k < nodeNum; ++k)
	// 		{
	// 				printf("%d to %d : access point :%d\t",i,j,distM[i][j].route[k]);
	// 		}
	// 	}
	// 	printf("\n");
	// }
	//while(*(demand) != 0X0a){

	int len = strlen(demand);
	printf("length is :%d\t",len);
	for (int i = 0; i < len/2; i++)
	{
		
		//printf("\n\n%c\n\n", *(demand));
		
		*demand = *(demand+i*2);
		access[i] = ((int)*demand-48);
		printf("\n\n%d\n\n", access[i]);
		// *demand = *(demand+1);
		// printf("\n\n%c\n\n", *(demand));
		// *demand = *(demand+1);
		// printf("\n\n%c\n\n", *(demand));
	}
	//}
	startPoi = access[0];
	finPoi = access[1];
	
    for (int i = 0; i < edge_num; ++i)
	{
		for (int j = 0; j < edge_num; ++j)
		{
			printf("%d\t",distM[i][j].dist);
		}
		printf("\n");
	}

    for (int i = 0; i < 3; i++)
        record_result(*topo[i]);
}
