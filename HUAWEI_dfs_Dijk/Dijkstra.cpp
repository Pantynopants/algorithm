/**
**ʹ��djistra����ȥ������Ӧ�����·��������̰���㷨��ÿһ���Ҷ�ѡȡ���ŵĽ������
*����������������û�п��ǵ����⣺���ͬһʱ�̣�dijkstra����������ͬ���������·��Ӧ����ô�죿
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

//djistra�㷨�еĻ���Ԫ��
struct djiNode{
	int from;//��һ���ڵ�
	int distance;//����
	int flag;//�ýڵ��Ƿ��Ѿ����뵽���·�����У�0-û�У�1-�Ѿ�������
};


//���ҵ�ǰ·����С���ýڵ㲻��sJihe�У�����·����Ϊ-1
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


//����nodeList,���µĹ������ڣ���������alreadyNode�еĽڵ�ĳ������Ϊ0��ɾ��������ȵ�already�еĽڵ�
void updateNodeList(vNode* nodeList,vector<int>& alreadyNode,int num){
	for(int i=0;i<alreadyNode.size();i++){
		nodeList[alreadyNode.at(i)].next=NULL;
	}
	for(int i=0;i<num;i++){//ɾ�����н���Ľڵ�
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
*ʹ��djistra�㷨ȥ��---������õ�һ�ַ�ʽ���ڽӱ�ÿѡ����һ����Ӧ�Ľڵ�Ͷ��ڽӾ�����һ�θ���,���һ���ǽڵ������
*/
void dijkstraFindWay(vNode* nodeList,vNode* nodeListCopy,int& maxCost,int& isHaveResult,vector<int>& result,int begin,int end,vector<int>& passNode,int num){
	vector<int> alreadyNode;//�Ѿ��߹��Ľڵ�
	vector<int> sJihe;//dijkstra�㷨�е�s����
	vector<int> timesNode;//һ�ι����м���Ľڵ�
	vector<int> passedNode;//�Ѿ������Ľڵ㣬�����ж�isTheLastPass
	djiNode* djiList;
	djiList=new djiNode[num];
	maxCost=0;
	isHaveResult=0;
	int isTheLastPass=0;//�Ƿ������һ������
	for(int i=0;i<num;i++){
		djiList[i].from=-1;
		djiList[i].distance=-1;
		djiList[i].flag=0;
	}

	//��ʼ������djiList
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
	*̰��djistra�㷨�ľ�����������
	*һ��ִ��һ�β���djistra�㷨��ѡ�����������passNode�еĽڵ㣬passNode�е����нڵ�û��ȫ�����꣬���Ҳ�����������Ľڵ㣬��ǿ�н������޽�
	**1-1���ѳ�ʼ�ڵ�ѹ��sJihe��Ȼ������һ�������·��Ȼ��ѹ��sJihe
	**1-2������djistra�㷨����djiList��ѭ��ִ��1-1��ֱ��ѹ��ջ�Ľڵ���passNode�еĽڵ㣬����Ҳ�������ڵ㣬������ѭ������Ϸ����
	**1-3����������ҵ������Ľڵ�˳��ѹ��ջ�У�����maxCost
	*��������nodeList��alreadyNode��sJihe��djiList
	**/
	while(true){
		sJihe.push_back(alreadyNode.at(alreadyNode.size()-1));
		djiList[sJihe.at(0)].flag=1;
		int best=-1;
		while(find(passNode.begin(),passNode.end(),best)==passNode.end()){//ѭ���������ŵĽڵ㣬ֱ�����ŵĽڵ���passNode��
	       best=findTheShortestNode(djiList,num,end,isTheLastPass);
	         if(best==-1)//û�����
			    break;
		   sJihe.push_back(best);//�ѵ�ǰ���Žڵ����sJihe����
		   djiList[best].flag=1;//��ǰ�ڵ��Ѿ����µ����нڵ�

		   //����һ��djiList
		   int cost=djiList[best].distance;
		   node* tmps=nodeListCopy[best].next;
		   while(tmps!=NULL){
			   if((djiList[tmps->destinationId].from==-1&&djiList[tmps->destinationId].flag==0)||(cost+tmps->cost)<djiList[tmps->destinationId].distance){//���������̵ľ���֮���̻���֮ǰ�����޷�����
				   djiList[tmps->destinationId].distance=cost+tmps->cost;
				   djiList[tmps->destinationId].from=best;
			   }
				tmps=tmps->next;   
		   }
		}

		/**
		*�ҳ���һ������������best�ڵ㣬���մ���ĸ��ӳ̶ȷ�Ϊ�����������
		*һ��best=-1  û���ҵ���Ӧ��·��
		*����best=end  �Ѿ��ߵ��յ��ˣ������ҵ���һ��·��
		*������ͨ�������Ҫ����һϵ�е����ݣ�Ѱ����һ���ڵ㣬���ʱ����Ҫȥ�ж�һ���Ƿ񵽴����һ���ڵ���
		*/
	/**--------------------------------------------�жϿ�ʼ-----------------------------------------------------------*/
		if(best==-1){
		    break;//ûɶ˵�ģ�ֱ����ֹ
		}
		else {//���ǵõ���һ���Ϸ���best�ڵ㣬���Ȱ���һ���ڵ㵽����ڵ�����е���Ϣѹ��alreadyNode
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

		  //����timesNode
		  timesNode.clear();
		  for(int j=0;j<alreadyNode.size()-1;j++){
			  timesNode.push_back(alreadyNode.at(j));
		  }

		  passedNode.push_back(best);

		  //Ȼ��������ȥ�ж��Ƿ��Ѿ��ߵ��յ�
		  if(best==end){//���յ���,������Ҫ�ҳ����·��
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
		  else{//û���յ�
		     //����Ҫ����nodeListCopy,sJihe,djiList
			  updateNodeList(nodeListCopy,timesNode,num);//����nodeList---��ΪnodeList��ÿ�ζ����£������ֻ��Ҫ����θ��·Ž�ȥ
		      sJihe.clear();
			  updateDJiList(djiList,best,nodeListCopy,num);//����djiList
			  if(passedNode.size()==passNode.size()-1){
	                    isTheLastPass=1;//��ǰ�����һ���ڵ�
			  }
		  }
		}
   /***----------------------------------�ж���ֹ��������������������������������������������������������������������������������������������������������*/
	}

}


int main(){

	double start=GetTickCount();

	//���ȶ�ȡ���е��ļ�
	vector<Line> lines;
	int num=0;
	readFile(lines,num);
	cout<<"����"<<num+1<<"���ڵ�"<<endl;

	//Ȼ��ȥ��ʼ���ڽӱ�----��Ҫ�������ӱ�
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

	//��ȡҪ��
	int begin,end;//��ֹ�ڵ�
	vector<int> passNode;//��������
	readDemand(begin,end,passNode);
	cout<<"��ʼ�ڵ�Ϊ"<<begin<<"-"<<end<<endl;


	int cost=0;
	int hasResult=0;
	vector<int> result;
	dijkstraFindWay(nodeList,nodeListCopy,cost,hasResult,result,begin,end,passNode,num+1);

	if(hasResult==1){
	   cout<<"�н��"<<endl;
	}
	else{
	   cout<<"û���"<<endl;
	}

	for(int i=0;i<result.size();i++){
	   cout<<result.at(i)<<"|";
	}
	cout<<endl;

	delete[] nodeList;
	double endTime=GetTickCount();
	cout<<"��������"<<(endTime-start)<<"ms"<<endl;
    cout<<"end"<<endl;
	return 0;
}