/**
**Ê¹ÓÃdjistra·½·¨È¥¼ÆËãÏàÓ¦µÄ×î¶ÌÂ·¾¶£¬ÀûÓÃÌ°ÐÄËã·¨£¬Ã¿Ò»´ÎÎÒ¶¼Ñ¡È¡×îÓÅµÄ½â¾ö·½°¸
*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ªÃ»ÓÐ¿¼ÂÇµÄÎÊÌâ£ºÈç¹ûÍ¬Ò»Ê±¿Ì£¬dijkstraÓöµ½ÁËÁ½¸öÍ¬ÑùÊÇ×î½üµÄÂ·¾¶Ó¦¸ÃÔõÃ´°ì£¿
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

//djistraËã·¨ÖÐµÄ»ù±¾ÔªËØ
struct djiNode{
	int from;//ÉÏÒ»¸ö½Úµã
	int distance;//¾àÀë
	int flag;//¸Ã½ÚµãÊÇ·ñÒÑ¾­¼ÓÈëµ½×î¶ÌÂ·¾¶µ±ÖÐ£¬0-Ã»ÓÐ£¬1-ÒÑ¾­¼ÓÈëÁË
};


//²éÕÒµ±Ç°Â·¾¶×îÐ¡£¬¸Ã½Úµã²»ÔÚsJiheÖÐ£¬ÇÒÆäÂ·¾¶²»Îª-1
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


//¸üÐÂnodeList,¸üÐÂµÄ¹ý³ÌÔÚÓÚ£¬°ÑËùÓÐÔÚalreadyNodeÖÐµÄ½ÚµãµÄ³ö¶ÈÇå¿ÕÎª0£¬É¾³ýËùÓÐÈë¶Èµ½alreadyÖÐµÄ½Úµã
void updateNodeList(vNode* nodeList,vector<int>& alreadyNode,int num){
	for(int i=0;i<alreadyNode.size();i++){
		nodeList[alreadyNode.at(i)].next=NULL;
	}
	for(int i=0;i<num;i++){//É¾³ýËùÓÐ½øÈëµÄ½Úµã
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
*Ê¹ÓÃdjistraËã·¨È¥×ö---ÕâÀï²ÉÓÃµÄÒ»ÖÖ·½Ê½ÊÇÁÚ½Ó±í£¬Ã¿Ñ¡³öÀ´Ò»¸öÏàÓ¦µÄ½Úµã¾Í¶ÔÁÚ½Ó¾ØÕó×öÒ»´Î¸üÐÂ,×îºóÒ»¸öÊÇ½ÚµãµÄÊýÁ¿
*/
void dijkstraFindWay(vNode* nodeList,vNode* nodeListCopy,int& maxCost,int& isHaveResult,vector<int>& result,int begin,int end,vector<int>& passNode,int num){
	vector<int> alreadyNode;//ÒÑ¾­×ß¹ýµÄ½Úµã
	vector<int> sJihe;//dijkstraËã·¨ÖÐµÄs¼¯ºÏ
	vector<int> timesNode;//Ò»´Î¹ý³ÌÖÐ¼ÓÈëµÄ½Úµã
	vector<int> passedNode;//ÒÑ¾­¾­¹ýµÄ½Úµã£¬ÓÃÀ´ÅÐ¶ÏisTheLastPass
	djiNode* djiList;
	djiList=new djiNode[num];
	maxCost=0;
	isHaveResult=0;
	int isTheLastPass=0;//ÊÇ·ñÊÇ×îºóÒ»¸öµãÁË
	for(int i=0;i<num;i++){
		djiList[i].from=-1;
		djiList[i].distance=-1;
		djiList[i].flag=0;
	}

	//³õÊ¼»¯Õû¸ödjiList
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
	*Ì°À·djistraËã·¨µÄ¾ßÌåÁ÷³ÌÈçÏÂ
	*Ò»¡¢Ö´ÐÐÒ»´Î²¿·ÖdjistraËã·¨£¬Ñ¡³ö¾àÀë×î½üµÄpassNodeÖÐµÄ½Úµã£¬passNodeÖÐµÄËùÓÐ½ÚµãÃ»ÓÐÈ«²¿×ßÍê£¬ÇÒÕÒ²»µ½¾àÀë×î½üµÄ½Úµã£¬ÔòÇ¿ÐÐ½áÊø£¬ÎÞ½â
	**1-1¡¢°Ñ³õÊ¼½ÚµãÑ¹ÈësJihe£¬È»ºó¼ÆËãµÚÒ»¸ö×î½üµÄÂ·£¬È»ºóÑ¹ÈësJihe
	**1-2¡¢°´ÕÕdjistraËã·¨¸üÐÂdjiList£¬Ñ­»·Ö´ÐÐ1-1£¬Ö±µ½Ñ¹ÈëÕ»µÄ½ÚµãÊÇpassNodeÖÐµÄ½Úµã£¬Èç¹ûÕÒ²»µ½×î½ü½Úµã£¬ÔòÌø³öÑ­»·£¬ÓÎÏ·½áÊø
	**1-3¡¢·´Ïò»ØËÝÕÒµ½¾­¹ýµÄ½ÚµãË³Ðò£¬Ñ¹ÈëÕ»ÖÐ£¬¸üÐÂmaxCost
	*¶þ¡¢¸üÐÂnodeList£¬alreadyNode£¬sJiheºÍdjiList
	**/
	while(true){
		sJihe.push_back(alreadyNode.at(alreadyNode.size()-1));
		djiList[sJihe.at(0)].flag=1;
		int best=-1;
		while(find(passNode.begin(),passNode.end(),best)==passNode.end()){//Ñ­»·²éÕÒ×îÓÅµÄ½Úµã£¬Ö±µ½×îÓÅµÄ½ÚµãÔÚpassNodeÖÐ
	       best=findTheShortestNode(djiList,num,end,isTheLastPass);
	         if(best==-1)//Ã»ÓÐ×î¼Ñ
			    break;
		   sJihe.push_back(best);//°Ñµ±Ç°×îÓÅ½Úµã·ÅÈësJiheµ±ÖÐ
		   djiList[best].flag=1;//µ±Ç°½ÚµãÒÑ¾­¸üÐÂµ½×îÓÐ½Úµã

		   //¸üÐÂÒ»ÏÂdjiList
		   int cost=djiList[best].distance;
		   node* tmps=nodeListCopy[best].next;
		   while(tmps!=NULL){
			   if((djiList[tmps->destinationId].from==-1&&djiList[tmps->destinationId].flag==0)||(cost+tmps->cost)<djiList[tmps->destinationId].distance){//Èç¹û¼ÓÈë×î¶ÌµÄ¾àÀëÖ®ºó±ä¶Ì»òÕßÖ®Ç°¸ù±¾ÎÞ·¨µ½´ï
				   djiList[tmps->destinationId].distance=cost+tmps->cost;
				   djiList[tmps->destinationId].from=best;
			   }
				tmps=tmps->next;   
		   }
		}

		/**
		*ÕÒ³öÁËÒ»¸ö·ûºÏÌõ¼þµÄbest½Úµã£¬°´ÕÕ´¦ÀíµÄ¸´ÔÓ³Ì¶È·ÖÎªÒÔÏÂÈýÖÖÇé¿ö
		*Ò»¡¢best=-1  Ã»ÓÐÕÒµ½ÏàÓ¦µÄÂ·¾¶
		*¶þ¡¢best=end  ÒÑ¾­×ßµ½ÖÕµãÁË£¬ÎÒÃÇÕÒµ½ÁËÒ»ÌõÂ·¾¶
		*Èý¡¢ÆÕÍ¨Çé¿ö£¬ÐèÒª¸üÐÂÒ»ÏµÁÐµÄÊý¾Ý£¬Ñ°ÕÒÏÂÒ»¸ö½Úµã£¬Õâ¸öÊ±ºòÐèÒªÈ¥ÅÐ¶ÏÒ»ÏÂÊÇ·ñµ½´ï×îºóÒ»¸ö½ÚµãÁË
		*/
	/**--------------------------------------------ÅÐ¶Ï¿ªÊ¼-----------------------------------------------------------*/
		if(best==-1){
		    break;//Ã»É¶ËµµÄ£¬Ö±½ÓÖÕÖ¹
		}
		else {//ÎÒÃÇµÃµ½ÁËÒ»¸öºÏ·¨µÄbest½Úµã£¬Ê×ÏÈ°ÑÉÏÒ»¸ö½Úµãµ½Õâ¸ö½ÚµãµÄËùÓÐµÄÐÅÏ¢Ñ¹ÈëalreadyNode
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

		  //¸üÐÂtimesNode
		  timesNode.clear();
		  for(int j=0;j<alreadyNode.size()-1;j++){
			  timesNode.push_back(alreadyNode.at(j));
		  }

		  passedNode.push_back(best);

		  //È»ºóÎÒÃÇÔÙÈ¥ÅÐ¶ÏÊÇ·ñÒÑ¾­×ßµ½ÖÕµã
		  if(best==end){//µ½ÖÕµãÁË,ÎÒÃÇÐèÒªÕÒ³öÕâ¸öÂ·¾¶
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
		  else{//Ã»µ½ÖÕµã
		     //ÎÒÃÇÒª¸üÐÂnodeListCopy,sJihe,djiList
			  updateNodeList(nodeListCopy,timesNode,num);//¸üÐÂnodeList---ÒòÎªnodeListÊÇÃ¿´Î¶¼¸üÐÂ£¬Òò´ËÎÒÖ»ÐèÒª°ÑÕâ´Î¸üÐÂ·Å½øÈ¥
		      sJihe.clear();
			  updateDJiList(djiList,best,nodeListCopy,num);//¸üÐÂdjiList
			  if(passedNode.size()==passNode.size()-1){
	                    isTheLastPass=1;//µ±Ç°ÊÇ×îºóÒ»¸ö½Úµã
			  }
		  }
		}
   /***----------------------------------ÅÐ¶ÏÖÕÖ¹¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
	}

}


int main(){

	double start=GetTickCount();

	//Ê×ÏÈ¶ÁÈ¡ËùÓÐµÄÎÄ¼þ
	vector<Line> lines;
	int num=0;
	readFile(lines,num);
	cout<<"¹²ÓÐ"<<num+1<<"¸ö½Úµã"<<endl;

	//È»ºóÈ¥³õÊ¼»¯ÁÚ½Ó±í----ÐèÒªÁ½¸öÁ´½Ó±í
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

	//¶ÁÈ¡ÒªÇó
	int begin,end;//ÆðÖ¹½Úµã
	vector<int> passNode;//¾­¹ý¾­µä
	readDemand(begin,end,passNode);
	cout<<"ÆðÊ¼½ÚµãÎª"<<begin<<"-"<<end<<endl;


	int cost=0;
	int hasResult=0;
	vector<int> result;
	dijkstraFindWay(nodeList,nodeListCopy,cost,hasResult,result,begin,end,passNode,num+1);

	if(hasResult==1){
	   cout<<"ÓÐ½á¹û"<<endl;
	}
	else{
	   cout<<"Ã»½á¹û"<<endl;
	}

	for(int i=0;i<result.size();i++){
	   cout<<result.at(i)<<"|";
	}
	cout<<endl;

	delete[] nodeList;
	double endTime=GetTickCount();
	cout<<"³ÌÐò¹²ÔËÐÐ"<<(endTime-start)<<"ms"<<endl;
    cout<<"end"<<endl;
	return 0;
}