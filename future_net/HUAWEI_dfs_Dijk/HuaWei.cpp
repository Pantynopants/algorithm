// HuaWei.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <stack>


#include "Common.h"

using namespace std;


//ѹջ�е�Ԫ��
struct stackNode{
    int id;//ѹ��Ľڵ�
	node* nowNode;//��ǰ�ýڵ�������Ľڵ�
};



//ִ���������ɨ��-----nodeList�ڽӱ�maxCost---����Ȩֵ,isHaveResult---�Ƿ�ӵ�������Ľ��,result---����·��
//����ѹջ��ջ�ķ���ȥ����

void dfs(vNode* nodeList,int& maxCost,int& isHaveResult,vector<int>& result,int begin,int end,vector<int>& passNode){
	isHaveResult=0;//Ĭ�ϵ�ǰû��·��
	vector<int> tmpRoad;//��ʱ·��
	vector<int> tmpNode;//��ʱ�����Ľڵ�,��ֹ�ظ�ר��
	int tmpCost=0;//��ʱ����
	maxCost=-1;//δ�������㣬�������Ϊ-1
    stack<stackNode> tmpStack;

	//��һ��������һ��Ԫ��ѹ��ջ
	stackNode first;
	first.id=begin;
	first.nowNode=nodeList[begin].next;
	tmpStack.push(first);
	tmpNode.push_back(begin);
	tmpNode.push_back(end);
	//�ڶ���,��ͷ��ʼ��ȱ�����---�������ռ���������ջΪ�գ������ǰ����п��ܵ��������������
	/**
	*1�����Ȱѵ�ǰջ���ڵ����һ���ڵ�ѹ��ջ��----ִ������N���ж�
	*2����һ���жϣ���ǰջ��û�нڵ��ˣ������ǳ����������п��ܵĲ��裬����
	*3���ڶ����жϣ���ǰջ���ڵ���һ���Ѿ���·���ߣ�����ջ���ڵ㣬����tmpNode��tmpRoad
	*4���������жϣ���ǰջ���ڵ�����һ���ڵ㣬��ô������Ҫִ������N���ж�
	**4.1����3-1���жϣ���һ���ڵ�ΪҪ����յ�ڵ㣬�ж��Ƿ񾭹�����Ҫ������нڵ㣬�������ж�·���Ƿ�����е�С������tmpCost,isHaveResult,result�����tmpRoad,tmpNode
	                   ,������Σ������Ҫ���µ�ǰջ���ڵ�--����stckNode.nowNode
	**4.2����3-2���жϣ���һ���ڵ��Ѿ�����tmpNode���ˣ���ôֱ�Ӹ���ջ���ڵ�
	**4.3����3-3���жϣ���һ���ڵ����֮���tmpCost�ȵ�ǰ���е�cost���ˣ���ô�ýڵ���������ֱ�Ӹ���ջ���ڵ�
	**4.3����3-4���жϣ���һ���ڵ����֮�����κη�Ӧ����ô����ջ���ڵ㣬����ǰ�ڵ����ջ��������tmpRoad,tmpNode
	*/
	while(true){
		if(tmpStack.empty()||(tmpStack.size()==1&&tmpStack.top().nowNode==NULL)){//��һ���ж�
		   cout<<"ѭ������"<<endl;
		   break;
		}
		if(tmpStack.top().nowNode==NULL){//�ڶ����ж�
			if(!tmpRoad.empty())
		          tmpRoad.pop_back();
			if(tmpNode.size()>2)
			      tmpNode.pop_back();
			tmpStack.pop();
			tmpCost-=tmpStack.top().nowNode->cost;
			tmpStack.top().nowNode=tmpStack.top().nowNode->next;
			continue;
		}

		//���¾�Ϊ�������ж�
		stackNode secondNode;
		secondNode.id=tmpStack.top().nowNode->destinationId;
		secondNode.nowNode=nodeList[secondNode.id].next;

		if(secondNode.id==end){//��3-1���ж�
			if(tmpNode.size()<=passNode.size()+1){
			    //�����������϶�������ȫ����
			}
			else if(!containsAll(tmpNode,passNode)){
			    //û�а������϶�û�о���
			}
			else{//��õ���һ��·��
				tmpCost+=tmpStack.top().nowNode->cost;
				if(maxCost==-1||tmpCost<maxCost){//��·��Ϊ����ȫ�����£�Ȼ�����
				    isHaveResult=1;
					tmpRoad.push_back(tmpStack.top().nowNode->linkedId);
					result.clear();
					for(int i=0;i<tmpRoad.size();i++){
						result.push_back(tmpRoad.at(i));
					}
					maxCost=tmpCost;
					tmpRoad.pop_back();
				}
				tmpCost-=tmpStack.top().nowNode->cost;
			}
			//����tmpStack,tmpCost,tmpNode��tmpRoad---��һ��ֻ��Ҫ����tmpSatck����
			tmpStack.top().nowNode=tmpStack.top().nowNode->next;
			continue;
		}
		else if(find(tmpNode.begin(),tmpNode.end(),secondNode.id)!=tmpNode.end()){//�ڵ��ظ�����
		     tmpStack.top().nowNode=tmpStack.top().nowNode->next;
			 continue;
		}
		else if((tmpCost+tmpStack.top().nowNode->cost)>=maxCost&&maxCost!=-1){//��ǰ·���������
		      tmpStack.top().nowNode=tmpStack.top().nowNode->next;
			  continue;
		}
		else{//һ��������ѹ��ջ
			tmpNode.push_back(secondNode.id);
			tmpRoad.push_back(tmpStack.top().nowNode->linkedId);
			tmpCost+=tmpStack.top().nowNode->cost;
			tmpStack.push(secondNode);
			continue;
		}
	}

}




int main_dfs(){
	double start=GetTickCount();

	//���ȶ�ȡ���е��ļ�
	vector<Line> lines;
	int num=0;
	readFile(lines,num);
	cout<<"����"<<num+1<<"���ڵ�"<<endl;

	//Ȼ��ȥ��ʼ���ڽӱ�
	vNode* nodeList;
	nodeList=new vNode[num+1];
	for(int i=0;i<=num;i++){
		nodeList[i].sourceId=i;
		nodeList[i].next=NULL;
	}
	transferStorage(lines,nodeList);

	//��ȡҪ��
	int begin,end;//��ֹ�ڵ�
	vector<int> passNode;//��������
	readDemand(begin,end,passNode);
	cout<<"��ʼ�ڵ�Ϊ"<<begin<<"-"<<end<<endl;



	//�������
	/**
	for(int i=0;i<=num;i++){
	   cout<<nodeList[i].sourceId<<"->";
	   node* lastnode=nodeList[i].next;
	   while(lastnode!=NULL){
		   cout<<lastnode->linkedId<<","<<lastnode->destinationId<<","<<lastnode->cost<<"->";
		   lastnode=lastnode->next;
	   }
	   cout<<endl;
	}
	
	cout<<"��Ҫ�����Ľڵ�Ϊ"<<passNode.at(0)<<","<<passNode.at(1)<<endl;
	**/

	//ִ��dfs
	int maxCost,isHaveResult;
	vector<int> result;
	dfs(nodeList,maxCost,isHaveResult,result,begin,end,passNode);


	if(isHaveResult==1){
	   cout<<"����Ӧ��·��"<<endl;
	   cout<<"ȨֵΪ"<<maxCost<<endl;
	   for(int i=0;i<result.size();i++)
		   cout<<result.at(i)<<"-";
	   cout<<endl;
	}
	else{
	   cout<<"δ�ҵ���Ӧ��·��"<<endl;
	}
	

	delete[] nodeList;
	double endTime=GetTickCount();
	cout<<"��������"<<(endTime-start)<<"ms"<<endl;
   cout<<"end"<<endl;

   return 0;
};




