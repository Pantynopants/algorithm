#include "Common.h"

//读取文件---num 
void readFile(vector<Line>& lines,int& num){
	fstream topo("topo.csv");
	if(!topo){
	   cout<<"topo.csv打开错误"<<endl;
	   return;
	}
	string buffer;
	//int linkedId,destinationId,cost,sourceId;
	while(getline(topo,buffer)){
	   //cout<<buffer<<endl;
	   vector<string> splitResult;
	   split(buffer,splitResult);
	   Line line;
	   line.linkedId=atoi(splitResult.at(0).c_str());
	   line.sourceId=atoi(splitResult.at(1).c_str());
	   line.destinationId=atoi(splitResult.at(2).c_str());
	   line.cost=atoi(splitResult.at(3).c_str());
	   lines.push_back(line);
	   num=(line.sourceId>num)?line.sourceId:num;
	   num=(line.destinationId>num)?line.destinationId:num;
	}
	topo.close();
};

//将图的存储方式转换为邻接表存储
void transferStorage(vector<Line>& lines,vNode* nodeList){
	for(int i=0;i<lines.size();i++){
	    Line line=lines.at(i);
		node* noded=new node;
		noded->cost=line.cost;
		noded->destinationId=line.destinationId;
		noded->linkedId=line.linkedId;
		noded->next=NULL;
		if(nodeList[line.sourceId].next==NULL){//如果该节点没有出边
			nodeList[line.sourceId].next=noded;
		}
		else{//有初边的情况需要，一是判断是否之前出现过，如果出现过，需要将值保存为最小的，否则直接插入
			node* lastnode=nodeList[line.sourceId].next;
			while(lastnode->next!=NULL&&lastnode->destinationId!=noded->destinationId){
			      lastnode=lastnode->next;
			}
			if(lastnode->destinationId!=noded->destinationId){//没有重复的路径
			      lastnode->next=noded;
			}
			else if((lastnode->cost)>(noded->cost)){//目前的边权值小·update
				lastnode->linkedId=noded->linkedId;
				lastnode->cost=noded->cost;
			}
		}
	}

};

//读取要求文件，起始节点以及经过的节点
void readDemand(int& begin,int& end,vector<int>& middleNode){
   fstream demand("demand.csv");
   if(!demand){
      cout<<"demand.csv文件读取失败"<<endl;
	  return;
   }
   string buffer;
   getline(demand,buffer);
   vector<string> result;
   split(buffer,result);
   begin=atoi(result.at(0).c_str());
   end=atoi(result.at(1).c_str());
   vector<string> middle;
   split(result.at(2),middle,"|");
   for(int i=0;i<middle.size();i++){
	   middleNode.push_back(atoi(middle.at(i).c_str()));
   }
};