
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

const int maxnum = 100;
const int maxint = 999999;
const int inf = 999999;

struct AtoB{ 
    int dist;
    int id;
    int route[50];
}; 
/* n == end point
*	v==start point
*/
int Dijkstra(int n, int v, int *dist, int *prev, AtoB c[maxnum][maxnum])
{
    
    bool s[maxnum];    // 判断是否已存入该点到S集合中
    for(int i=1; i<=n; ++i)
    {
        dist[i] = c[v][i].dist;
        s[i] = 0;     // 初始都未用过该点
        if(dist[i] == maxint)
            prev[i] = 0;
        else
            prev[i] = v;
    }
    dist[v] = 0;
    s[v] = 1;
 
    // 依次将未放入S集合的结点中，取dist[]最小值的结点，放入结合S中
    // 一旦S包含了所有V中顶点，dist就记录了从源点到所有其他顶点之间的最短路径长度
    for(int i=2; i<=n; ++i)
    {
        int tmp = maxint;
        int u = v;
        // 找出当前未使用的点j的dist[j]最小值
        for(int j=1; j<=n; ++j)
            if((!s[j]) && dist[j]<tmp)
            {
                u = j;              // u保存当前邻接点中距离最小的点的号码
                tmp = dist[j];
            }
        s[u] = 1;    // 表示u点已存入S集合中
 
        // 更新dist
        for(int j=1; j<=n; ++j)
            if((!s[j]) && c[u][j].dist<maxint)
            {
                int newdist = dist[u] + c[u][j].dist;
                if(newdist < dist[j])
                {
                    dist[j] = newdist;
                    prev[j] = u;
                }
            }
    }

    return dist[n];
}




/*  u == end point
*	v == start point
*/
void searchPath(int *prev,int v, int u)
{
    int que[maxnum];
    int tot = 1;
    que[tot] = u;
    tot++;
    int tmp = prev[u];
    while(tmp != v)
    {
        que[tot] = tmp;
        tot++;
        tmp = prev[tmp];
    }
    que[tot] = v;
    for(int i=tot; i>=1; --i)
        if(i != 1)
            cout << que[i] << " -> ";
        else
            cout << que[i] << endl;
}




void search_route(char *topo[5000], int edge_num, char *demand)
{
    //unsigned short result[] = {2, 6, 4};
    

    AtoB distM[maxnum][maxnum];
    
    int begin;
    int end;
    int id;
    int dist;

    
    /*
    *init the matrix
    *
    *
	*/

    //TODO

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			if (i == j)
			{
				distM[i][j].dist = 0;
			}else{
				distM[i][j].dist = inf;
			}
		}
	}



    // for (int i = 0; i < edge_num; i++){
    	
    //     	int begin = ((int)*(topo[i]+2) - 48);
    //     	int end = ((int)*(topo[i]+4) - 48);

    //     	distM[begin][end].id = ((int)*(topo[i]) - 48);
        	
    //     	distM[begin][end].dist = ((int)*(topo[i]+6)-48);
        	
    // }
    
    /* format the matrix */
    for (int i = 0; i < edge_num; ++i)
    {
    	char* token = strtok( topo[i], ",");
    	int k = 0;
    	while( token != NULL ) {

	        //printf( "result is %s\n", result );
	        if (k == 0)
	        {
	        	id = atoi(token);
	        }else if (k == 1)
	        {
	        	begin = atoi(token);
	        }else if (k == 2)
	        {
	        	end = atoi(token);
	        }else if (k ==3)
	        {
	        	dist = atoi(token);
	        }
    		k++;
	        token = strtok( NULL, "," );

   		}     
    	

    	distM[begin][end].id = id;
        	
    	distM[begin][end].dist = dist;

        printf( "from %d to %d ,token is :%d ", begin, end, distM[begin][end].dist );

	    //token = strtok( NULL, ",");
	    printf("\n");
    }
 
	printf("\n\n\n\n");

/*
*	get the necessary point which is in demand.csv
*
*/
	
	/* for demand */

    int SourceID;
    int DestinationID;
    int IncludingSet[50];
	
	//int len = strlen(demand);
	//printf("length is :%d\t",len);
	char* token = strtok( demand, ",|");
	int i = 0;
	int IncludingSetLength = 0;

    while( token != NULL )
    {
        /* While there are tokens in "string" */
        //printf( "token is :%s ", token );

    	if (i == 0)
    	{
    		SourceID = atoi(token);
    	}else if (i ==1)
    	{
    		DestinationID = atoi(token);
    	}else if (i >= 2)
    	{
    		IncludingSet[IncludingSetLength] = atoi(token);
    		IncludingSetLength++;
    	}

        /* Get next token: */
    	
        token = strtok( NULL, ",|");
        i++;
    }
    printf( "start :%d ", SourceID );
    printf( "end :%d ", DestinationID );
    for (int i = 0; i < IncludingSetLength; ++i)
    {
        
    	printf( "access :%d ", IncludingSet[i] );

    }

    /*
    * algorithm start
    *
    */

 //    int nodeNum = 0;

 //    for (int i = 0; i < edge_num; ++i)
	// {
	// 	for (int j = 0; j < edge_num; ++j)
	// 	{
	// 		for (int k = 0; k < edge_num; ++k)
	// 		{
	// 			if (distM[j][k].dist > distM[j][i].dist + distM[i][k].dist)
	// 			{
	// 				distM[j][k].dist = distM[j][i].dist + distM[i][k].dist;
	// 				distM[j][k].route[nodeNum] = i;
					
	// 				nodeNum++;				
	// 			}
	// 		}
	// 	}
	// }

    int distance[maxnum];     // 表示当前点到源点的最短路径长度
    int prevpoint[maxnum];     // 记录当前点的前一个结点

	for(int i=0; i<=edge_num/2; ++i)
        distance[i] = maxint;

    int case0;

/* Dijkstra(int SourceID, int DestinationID, int distance[], int prevpoint[], AtoB distM[][]);*/
    // you can set startpoint and endpoint as you want
    case0 = Dijkstra(DestinationID, SourceID, distance, prevpoint, distM);
 
    // 最短路径长度
    cout << "startPoint到endPoint的最短路径长度: " << case0 << endl;

	cout << "tartPoint到endPoint的的路径: " << endl;
	searchPath(prevpoint, SourceID, DestinationID);
//TODO 
// 1 存储方式由邻接矩阵转化为邻接表
// 2 实现pdf中的算法
// 3 注意输出路径结果为边的编号而不是顶点的编号
//
//
//
/* wirte to file */
    for (int i = 0; i < 3; i++)
        record_result(*topo[i]);
}
