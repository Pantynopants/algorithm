/**
*ȫ���Ļ��������������ڽӱ�֮���
**
*/

#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "Util.h"



using namespace std;

struct Line{
   int linkedId;//����
   int sourceId;//���
   int destinationId;//�յ�
   int cost;//Ȩֵ
};

//�ڽӱ��еıߵı�ʾ
struct node{
	int linkedId;
    int destinationId;
	int cost;
	struct node* next;
};

//�ڽӱ��е��׽ڵ�
struct vNode{
	int sourceId;
	node* next;
};

//��ȡ�ļ�---num 
void readFile(vector<Line>& lines,int& num);

//��ͼ�Ĵ洢��ʽת��Ϊ�ڽӱ�洢
void transferStorage(vector<Line>& lines,vNode* nodeList);

//��ȡҪ���ļ�����ʼ�ڵ��Լ������Ľڵ�
void readDemand(int& begin,int& end,vector<int>& middleNode);