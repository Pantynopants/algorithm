// HuaWei.cpp : 定义控制台应用程序的入口点。
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


//压栈中的元素
struct stackNode{
    int id;//压入的节点
	node* nowNode;//当前该节点遍历到的节点
};



//执行深度优先扫描-----nodeList邻接表，maxCost---最后的权值,isHaveResult---是否拥有这样的结果,result---结束路线
//利用压栈出栈的方法去计算

void dfs(vNode* nodeList,int& maxCost,int& isHaveResult,vector<int>& result,int begin,int end,vector<int>& passNode){
	isHaveResult=0;//默认当前没有路径
	vector<int> tmpRoad;//临时路径
	vector<int> tmpNode;//临时经过的节点,防止重复专用
	int tmpCost=0;//临时消耗
	maxCost=-1;//未进行运算，最大消耗为-1
    stack<stackNode> tmpStack;

	//第一步，将第一个元素压入栈
	stackNode first;
	first.id=begin;
	first.nowNode=nodeList[begin].next;
	tmpStack.push(first);
	tmpNode.push_back(begin);
	tmpNode.push_back(end);
	//第二部,从头开始深度遍历树---遍历的终极条件就是栈为空，即我们把所有可能的情况都考虑完了
	/**
	*1、首先把当前栈顶节点的下一步节点压入栈中----执行如下N次判断
	*2、第一次判断：当前栈顶没有节点了，则我们尝试完了所有可能的步骤，结束
	*3、第二个判断：当前栈顶节点下一步已经无路可走，弹出栈顶节点，更新tmpNode和tmpRoad
	*4、第三个判断：当前栈顶节点有下一步节点，那么我们需要执行以下N次判断
	**4.1、第3-1个判断：下一步节点为要求的终点节点，判断是否经过我们要求的所有节点，经过，判断路径是否比现有的小，更新tmpCost,isHaveResult,result，清空tmpRoad,tmpNode
	                   ,不管如何，最后都需要更新当前栈顶节点--更新stckNode.nowNode
	**4.2、第3-2个判断：下一步节点已经存在tmpNode中了，那么直接更新栈顶节点
	**4.3、第3-3个判断：下一步节点加入之后的tmpCost比当前已有的cost大了，那么该节点必需放弃，直接更新栈顶节点
	**4.3、第3-4个判断：下一步节点加入之后无任何反应，那么更新栈顶节点，将当前节点加入栈顶，更新tmpRoad,tmpNode
	*/
	while(true){
		if(tmpStack.empty()||(tmpStack.size()==1&&tmpStack.top().nowNode==NULL)){//第一次判断
		   cout<<"循环结束"<<endl;
		   break;
		}
		if(tmpStack.top().nowNode==NULL){//第二次判断
			if(!tmpRoad.empty())
		          tmpRoad.pop_back();
			if(tmpNode.size()>2)
			      tmpNode.pop_back();
			tmpStack.pop();
			tmpCost-=tmpStack.top().nowNode->cost;
			tmpStack.top().nowNode=tmpStack.top().nowNode->next;
			continue;
		}

		//以下均为第三个判断
		stackNode secondNode;
		secondNode.id=tmpStack.top().nowNode->destinationId;
		secondNode.nowNode=nodeList[secondNode.id].next;

		if(secondNode.id==end){//第3-1个判断
			if(tmpNode.size()<=passNode.size()+1){
			    //数量不够，肯定不能完全经过
			}
			else if(!containsAll(tmpNode,passNode)){
			    //没有包含，肯定没有经过
			}
			else{//求得到了一个路径
				tmpCost+=tmpStack.top().nowNode->cost;
				if(maxCost==-1||tmpCost<maxCost){//此路径为所求，全部更新，然后清空
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
			//更新tmpStack,tmpCost,tmpNode和tmpRoad---这一步只需要更新tmpSatck即可
			tmpStack.top().nowNode=tmpStack.top().nowNode->next;
			continue;
		}
		else if(find(tmpNode.begin(),tmpNode.end(),secondNode.id)!=tmpNode.end()){//节点重复出现
		     tmpStack.top().nowNode=tmpStack.top().nowNode->next;
			 continue;
		}
		else if((tmpCost+tmpStack.top().nowNode->cost)>=maxCost&&maxCost!=-1){//当前路径必需放弃
		      tmpStack.top().nowNode=tmpStack.top().nowNode->next;
			  continue;
		}
		else{//一切正常，压入栈
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

	//首先读取所有的文件
	vector<Line> lines;
	int num=0;
	readFile(lines,num);
	cout<<"共有"<<num+1<<"个节点"<<endl;

	//然后去初始化邻接表
	vNode* nodeList;
	nodeList=new vNode[num+1];
	for(int i=0;i<=num;i++){
		nodeList[i].sourceId=i;
		nodeList[i].next=NULL;
	}
	transferStorage(lines,nodeList);

	//读取要求
	int begin,end;//起止节点
	vector<int> passNode;//经过经典
	readDemand(begin,end,passNode);
	cout<<"起始节点为"<<begin<<"-"<<end<<endl;



	//测试输出
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
	
	cout<<"需要经过的节点为"<<passNode.at(0)<<","<<passNode.at(1)<<endl;
	**/

	//执行dfs
	int maxCost,isHaveResult;
	vector<int> result;
	dfs(nodeList,maxCost,isHaveResult,result,begin,end,passNode);


	if(isHaveResult==1){
	   cout<<"有相应的路线"<<endl;
	   cout<<"权值为"<<maxCost<<endl;
	   for(int i=0;i<result.size();i++)
		   cout<<result.at(i)<<"-";
	   cout<<endl;
	}
	else{
	   cout<<"未找到相应的路线"<<endl;
	}
	

	delete[] nodeList;
	double endTime=GetTickCount();
	cout<<"程序共运行"<<(endTime-start)<<"ms"<<endl;
   cout<<"end"<<endl;

   return 0;
};




