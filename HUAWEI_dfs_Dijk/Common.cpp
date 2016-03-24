#include "Common.h"

//��ȡ�ļ�---num 
void readFile(vector<Line>& lines,int& num){
	fstream topo("topo.csv");
	if(!topo){
	   cout<<"topo.csv�򿪴���"<<endl;
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

//��ͼ�Ĵ洢��ʽת��Ϊ�ڽӱ�洢
void transferStorage(vector<Line>& lines,vNode* nodeList){
	for(int i=0;i<lines.size();i++){
	    Line line=lines.at(i);
		node* noded=new node;
		noded->cost=line.cost;
		noded->destinationId=line.destinationId;
		noded->linkedId=line.linkedId;
		noded->next=NULL;
		if(nodeList[line.sourceId].next==NULL){//����ýڵ�û�г���
			nodeList[line.sourceId].next=noded;
		}
		else{//�г��ߵ������Ҫ��һ���ж��Ƿ�֮ǰ���ֹ���������ֹ�����Ҫ��ֵ����Ϊ��С�ģ�����ֱ�Ӳ���
			node* lastnode=nodeList[line.sourceId].next;
			while(lastnode->next!=NULL&&lastnode->destinationId!=noded->destinationId){
			      lastnode=lastnode->next;
			}
			if(lastnode->destinationId!=noded->destinationId){//û���ظ���·��
			      lastnode->next=noded;
			}
			else if((lastnode->cost)>(noded->cost)){//Ŀǰ�ı�ȨֵС��update
				lastnode->linkedId=noded->linkedId;
				lastnode->cost=noded->cost;
			}
		}
	}

};

//��ȡҪ���ļ�����ʼ�ڵ��Լ������Ľڵ�
void readDemand(int& begin,int& end,vector<int>& middleNode){
   fstream demand("demand.csv");
   if(!demand){
      cout<<"demand.csv�ļ���ȡʧ��"<<endl;
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