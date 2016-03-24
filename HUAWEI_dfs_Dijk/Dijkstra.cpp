/**
**使用djistra方法去计算相应的最短路径，利用贪心算法，每一次我都选取最优的解决方案
*————————没有考虑的问题：如果同一时刻，dijkstra遇到了两个同样是最近的路径应该怎么办？
*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <stack>
#include<limits>


#include "Common.h"

using namespace std;

//djistra算法中的基本元素
struct djiNode{
	int from;//上一个节点
	int distance;//距离
	int flag;//该节点是否已经加入到最短路径当中，0-没有，1-已经加入了
};


//查找当前路径最小，该节点不在sJihe中，且其路径不为-1
int findTheShortestNode(djiNode* djiList,int num,int end,int isTheLastPass){
	int cost=INT_MAX;
	int number=-1;
	if(isTheLastPass==1){
	   for(int i=0;i<num;i++){
		if(djiList[i].flag==0&&djiList[i].from!=-1&&djiList[i].distance<cost){
		    number=i;
			cost=djiList[i].distance;
		}
	   }
	}
	else{
	 for(int i=0;i<num;i++){
		if(i!=end&&djiList[i].flag==0&&djiList[i].from!=-1&&djiList[i].distance<cost){
		    number=i;
			cost=djiList[i].distance;
		}
	   }
	}
	
	return number;
};


//更新nodeList,更新的过程在于，把所有在alreadyNode中的节点的出度清空为0，删除所有入度到already中的节点
void updateNodeList(vNode* nodeList,vector<int>& alreadyNode,int num){
	for(int i=0;i<alreadyNode.size();i++){
		nodeList[alreadyNode.at(i)].next=NULL;
	}
	for(int i=0;i<num;i++){//删除所有进入的节点
	  node* previous=nodeList[i].next;
	  int only=0;
	  while(previous!=NULL){
		  if(only=0){
			  if(find(alreadyNode.begin(),alreadyNode.end(),previous->destinationId)!=alreadyNode.end()){
			         node* tmp=previous;
					 previous=previous->next;
					 delete tmp;
			  }
			  else{
			        only=1;
			  } 
		  }
		  else{
		       if(previous->next==NULL)
				   break;
			   node* second=previous->next;
			   if(find(alreadyNode.begin(),alreadyNode.end(),second->destinationId)!=alreadyNode.end()){
				   previous->next=second->next;
				   delete second;
			   }
			   else{
			      previous=previous->next;
			   }
		  }
	  }
	}
};




void updateDJiList(djiNode* djiList,int best,vNode* nodeList,int num){
	for(int i=0;i<num;i++){
		djiList[i].distance=-1;
		djiList[i].flag=0;
		djiList[i].from=-1;
	}
	node* tmp=nodeList[best].next;
	while(tmp!=NULL){
		djiList[tmp->destinationId].from=best;
		djiList[tmp->destinationId].distance=tmp->cost;
		tmp=tmp->next;
	}

};

/**
*使用djistra算法去做---这里采用的一种方式是邻接表，每选出来一个相应的节点就对邻接矩阵做一次更新,最后一个是节点的数量
*/
void dijkstraFindWay(vNode* nodeList,vNode* nodeListCopy,int& maxCost,int& isHaveResult,vector<int>& result,int begin,int end,vector<int>& passNode,int num){
	vector<int> alreadyNode;//已经走过的节点
	vector<int> sJihe;//dijkstra算法中的s集合
	vector<int> timesNode;//一次过程中加入的节点
	vector<int> passedNode;//已经经过的节点，用来判断isTheLastPass
	djiNode* djiList;
	djiList=new djiNode[num];
	maxCost=0;
	isHaveResult=0;
	int isTheLastPass=0;//是否是最后一个点了
	for(int i=0;i<num;i++){
		djiList[i].from=-1;
		djiList[i].distance=-1;
		djiList[i].flag=0;
	}

	//初始化整个djiList
	node* tmp=nodeList[begin].next;
	while(tmp!=NULL){
		if(tmp->destinationId!=end){
			djiList[tmp->destinationId].distance=tmp->cost;
			djiList[tmp->destinationId].from=begin;
		}
		tmp=tmp->next;
	}

	alreadyNode.push_back(begin);

	passNode.push_back(end);

	/**
	*贪婪djistra算法的具体流程如下
	*一、执行一次部分djistra算法，选出距离最近的passNode中的节点，passNode中的所有节点没有全部走完，且找不到距离最近的节点，则强行结束，无解
	**1-1、把初始节点压入sJihe，然后计算第一个最近的路，然后压入sJihe
	**1-2、按照djistra算法更新djiList，循环执行1-1，直到压入栈的节点是passNode中的节点，如果找不到最近节点，则跳出循环，游戏结束
	**1-3、反向回溯找到经过的节点顺序，压入栈中，更新maxCost
	*二、更新nodeList，alreadyNode，sJihe和djiList
	**/
	while(true){
		sJihe.push_back(alreadyNode.at(alreadyNode.size()-1));
		djiList[sJihe.at(0)].flag=1;
		int best=-1;
		while(find(passNode.begin(),passNode.end(),best)==passNode.end()){//循环查找最优的节点，直到最优的节点在passNode中
	       best=findTheShortestNode(djiList,num,end,isTheLastPass);
	         if(best==-1)//没有最佳
			    break;
		   sJihe.push_back(best);//把当前最优节点放入sJihe当中
		   djiList[best].flag=1;//当前节点已经更新到最有节点

		   //更新一下djiList
		   int cost=djiList[best].distance;
		   node* tmps=nodeListCopy[best].next;
		   while(tmps!=NULL){
			   if((djiList[tmps->destinationId].from==-1&&djiList[tmps->destinationId].flag==0)||(cost+tmps->cost)<djiList[tmps->destinationId].distance){//如果加入最短的距离之后变短或者之前根本无法到达
				   djiList[tmps->destinationId].distance=cost+tmps->cost;
				   djiList[tmps->destinationId].from=best;
			   }
				tmps=tmps->next;   
		   }
		}

		/**
		*找出了一个符合条件的best节点，按照处理的复杂程度分为以下三种情况
		*一、best=-1  没有找到相应的路径
		*二、best=end  已经走到终点了，我们找到了一条路径
		*三、普通情况，需要更新一系列的数据，寻找下一个节点，这个时候需要去判断一下是否到达最后一个节点了
		*/
	/**--------------------------------------------判断开始-----------------------------------------------------------*/
		if(best==-1){
		    break;//没啥说的，直接终止
		}
		else {//我们得到了一个合法的best节点，首先把上一个节点到这个节点的所有的信息压入alreadyNode
		  stack<int> tmpList;
		  int itmp=best;
		  while(djiList[itmp].from!=-1){
			  tmpList.push(itmp);
			  itmp=djiList[itmp].from;
		  }
		  while(!tmpList.empty()){
			  alreadyNode.push_back(tmpList.top());
			  //timesNode.push_back(tmpList.top());
			  tmpList.pop();
		  }
		  maxCost+=djiList[best].distance;

		  //更新timesNode
		  timesNode.clear();
		  for(int j=0;j<alreadyNode.size()-1;j++){
			  timesNode.push_back(alreadyNode.at(j));
		  }

		  passedNode.push_back(best);

		  //然后我们再去判断是否已经走到终点
		  if(best==end){//到终点了,我们需要找出这个路径
			  for(int i=0;i<alreadyNode.size()-1;i++){
			       int head=alreadyNode.at(i);
				   int back=alreadyNode.at(i+1);
				   node* nownode=nodeList[head].next;
				   while(nownode->destinationId!=back)
					   nownode=nownode->next;
				   result.push_back(nownode->linkedId);
			  }
			  isHaveResult=1;
			  break;
		  }
		  else{//没到终点
		     //我们要更新nodeListCopy,sJihe,djiList
			  updateNodeList(nodeListCopy,timesNode,num);//更新nodeList---因为nodeList是每次都更新，因此我只需要把这次更新放进去
		      sJihe.clear();
			  updateDJiList(djiList,best,nodeListCopy,num);//更新djiList
			  if(passedNode.size()==passNode.size()-1){
	                    isTheLastPass=1;//当前是最后一个节点
			  }
		  }
		}
   /***----------------------------------判断终止————————————————————————————————————————————————————*/
	}

}


int main(){

	double start=GetTickCount();

	//首先读取所有的文件
	vector<Line> lines;
	int num=0;
	readFile(lines,num);
	cout<<"共有"<<num+1<<"个节点"<<endl;

	//然后去初始化邻接表----需要两个链接表
	vNode* nodeList;
	vNode* nodeListCopy;
	nodeList=new vNode[num+1];
	nodeListCopy=new vNode[num+1];
	for(int i=0;i<=num;i++){
		nodeList[i].sourceId=i;
		nodeList[i].next=NULL;

		nodeListCopy[i].sourceId=i;
		nodeListCopy[i].next=NULL;
	}
	transferStorage(lines,nodeList);

	transferStorage(lines,nodeListCopy);

	//读取要求
	int begin,end;//起止节点
	vector<int> passNode;//经过经典
	readDemand(begin,end,passNode);
	cout<<"起始节点为"<<begin<<"-"<<end<<endl;


	int cost=0;
	int hasResult=0;
	vector<int> result;
	dijkstraFindWay(nodeList,nodeListCopy,cost,hasResult,result,begin,end,passNode,num+1);

	if(hasResult==1){
	   cout<<"有结果"<<endl;
	}
	else{
	   cout<<"没结果"<<endl;
	}

	for(int i=0;i<result.size();i++){
	   cout<<result.at(i)<<"|";
	}
	cout<<endl;

	delete[] nodeList;
	double endTime=GetTickCount();
	cout<<"程序共运行"<<(endTime-start)<<"ms"<<endl;
    cout<<"end"<<endl;
	return 0;
}