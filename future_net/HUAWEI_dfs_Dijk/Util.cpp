#include "Util.h"


//�������ߣ��ַ����и�
int split(const string& str, vector<string>& ret_, string sep)
{
    if (str.empty())
    {
        return 0;
    }

    string tmp;
    string::size_type pos_begin = str.find_first_not_of(sep);
    string::size_type comma_pos = 0;

    while (pos_begin != string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        if (!tmp.empty())
        {
            ret_.push_back(tmp);
            tmp.clear();
        }
    }
    return 0;
};


//�������ߣ��жϼ���A�Ƿ��������B�е�ȫ��Ԫ��----�϶����Ա��Ż�
bool containsAll(vector<int>& A,vector<int>& B){
    stack<int> BS;
	for(int i=0;i<B.size();i++){
		BS.push(B.at(i));
	}
	while(!BS.empty()){
	     int i=BS.top();
		 if(find(A.begin(),A.end(),i)==A.end()){
		    return false;
		 }
		 else{
		    BS.pop();
		 }
	}
	return true;
};