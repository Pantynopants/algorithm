/**
*全部的基础操作，更改邻接表之类的
**
*/

#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "Util.h"



using namespace std;

struct Line{
   int linkedId;//代号
   int sourceId;//起点
   int destinationId;//终点
   int cost;//权值
};

//邻接表中的边的表示
struct node{
	int linkedId;
    int destinationId;
	int cost;
	struct node* next;
};

//邻接表中的首节点
struct vNode{
	int sourceId;
	node* next;
};

//读取文件---num 
void readFile(vector<Line>& lines,int& num);

//将图的存储方式转换为邻接表存储
void transferStorage(vector<Line>& lines,vNode* nodeList);

//读取要求文件，起始节点以及经过的节点
void readDemand(int& begin,int& end,vector<int>& middleNode);