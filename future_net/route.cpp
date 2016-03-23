
#include "route.h"
#include "lib_record.h"






//TODO 
// IMPORTTANT!!!!
// 0 function searchPath(...) return a wrong value , such as 0to19 ,
// we can get it bug it print "no path"
//
// 1 存储方式由邻接矩阵转化为邻接表
// 2 实现pdf中的算法
// 3 注意输出路径结果为边的编号而不是顶点的编号
// 
//
//








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


    if (prev[u] == NULL)
    {
        printf("no path from %d to %d \n",v,u );
        return;
    }


    int tmp = prev[u];
    while(tmp != v)
    {
        que[tot] = tmp;
        tot++;

        if (prev[tmp] == NULL)
        {
            printf("no path from %d to %d \n",v,u );
            return;
        }

        tmp = prev[tmp];
    }
    que[tot] = v;
    for(int i=tot; i>=1; --i){
        if(i != 1)
            cout << que[i] << " -> ";
        else
            cout << que[i] << endl;
    }
}




int midPath(int IncludingSetLength, int IncludingSet[50], AtoB c[maxnum][maxnum])
{

    //cout << "get mid path" << endl;
    int midDist = 0;
    int distance[maxnum];     // 表示当前点到源点的最短路径长度
    int prevpoint[maxnum];     // 记录当前点的前一个结点

    for(int i=0; i<=200; ++i)
        distance[i] = maxint;

    for (int i = 0; i+1 < IncludingSetLength; ++i)
    {
            
        /*
        * TODO use if {}else{} to cut runtime 
        *
        *
        */

        // if (c[ IncludingSet[i] ][ IncludingSet[i+1] ].dist != inf)
        // {
        //     midDist += c[ IncludingSet[i] ][ IncludingSet[i+1] ].dist;
        // }else{
            midDist += Dijkstra(IncludingSet[i+1], IncludingSet[i], distance, prevpoint, c);
            //cout << IncludingSet[i] << "到" << IncludingSet[i+1] <<"的路径: " << endl;
            searchPath(prevpoint, IncludingSet[i], IncludingSet[i+1]);

        
        
        
    }
    // for (int i = 0; i < IncludingSetLength; ++i)
    // {
            
    //     printf( "access :%d  ", IncludingSet[i]);
    // }
    
    if (midDist >= inf)
    {
        printf( "no result\n" );
    }else{
        printf( "distance :%d \n" ,midDist);
    }
    
    
    return midDist;
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

    //TODO use dist[] not matrix to change 600

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
    printf( "start :%d \n", SourceID );
    printf( "end :%d \n", DestinationID );
    printf( "number :%d \n", IncludingSetLength);
    // for (int i = 0; i < IncludingSetLength; ++i)
    // {
        
    // 	printf( "access :%d ", IncludingSet[i] );

    // }
    

    int arrNum = 1;
    int midDist = inf;

    int totalDist = inf;

    int firstDist = inf;
    int lastDist = inf;

    int tempDist = 0;

    int firstdistance[maxnum];     // 表示当前点到源点的最短路径长度
    int firstprevpoint[maxnum];     // 记录当前点的前一个结点

    for(int i=0; i<=edge_num/2; ++i)
        firstdistance[i] = maxint;

    int lastdistance[maxnum];     // 表示当前点到源点的最短路径长度
    int lastprevpoint[maxnum];     // 记录当前点的前一个结点

    for(int i=0; i<=edge_num/2; ++i)
        lastdistance[i] = maxint;

    int copyIncludingSet[50];

    do 
    {  
        /* Dijkstra(int SourceID, int DestinationID, int distance[], int prevpoint[], AtoB distM[][]);*/

        midDist = midPath(IncludingSetLength, IncludingSet, distM);
        firstDist = Dijkstra(IncludingSet[0] , SourceID, firstdistance, firstprevpoint, distM);
        lastDist = Dijkstra(DestinationID, IncludingSet[IncludingSetLength], lastdistance, lastprevpoint, distM);

        tempDist = firstDist + midDist + lastDist;
        cout << firstDist << " " << midDist << " " << lastDist << "\n" ;
        if (tempDist < totalDist)
        {
            totalDist = tempDist;
            //copy the shortest IncludingSet to the new array
            //the last time we copied is the shortest IncludingSet
            
            //memcpy(copyIncludingSet,IncludingSet, IncludingSetLength*sizeof(int)); 

            for (int i = 0; i < IncludingSetLength; ++i)
            {
                copyIncludingSet[i] = IncludingSet[i];
            }
            cout << "\n\n\n\n\n\n\n\n\n\n copy \n\n\n\n\n\n\n" ;
            
        }

        arrNum++;
            
    }while (next_permutation(IncludingSet, (IncludingSet+IncludingSetLength)));

    cout << "array number is :" << arrNum-1 << endl;
    
    printf("\n\n\n\n\n");
    for (int i = 0; i < IncludingSetLength; ++i)
    {
        printf("access %d", copyIncludingSet[i]);
    }
    printf("\n\n\n\n\n");

    midDist = midPath(IncludingSetLength, IncludingSet, distM);

    firstDist = Dijkstra(IncludingSet[0] , SourceID, firstdistance, firstprevpoint, distM);
    searchPath(firstprevpoint, SourceID, IncludingSet[0]);

    lastDist = Dijkstra(DestinationID, IncludingSet[IncludingSetLength], lastdistance, lastprevpoint, distM);
    searchPath(lastprevpoint, IncludingSet[IncludingSetLength], DestinationID);

    printf("\n\n\n\n\n");




 //    int distance[maxnum];     // 表示当前点到源点的最短路径长度
 //    int prevpoint[maxnum];     // 记录当前点的前一个结点

	// for(int i=0; i<=edge_num/2; ++i)
 //        distance[i] = maxint;

 //    int case0;

 //    // you can set startpoint and endpoint as you want
 //    case0 = Dijkstra(DestinationID, SourceID, distance, prevpoint, distM);
 
 //    // 最短路径长度
 //    cout << "startPoint到endPoint的最短路径长度: " << case0 << endl;

	// cout << "tartPoint到endPoint的的路径: " << endl;
	// searchPath(prevpoint, SourceID, DestinationID);

/* wirte to file */
    for (int i = 0; i < 3; i++)
        record_result(*topo[i]);
}
