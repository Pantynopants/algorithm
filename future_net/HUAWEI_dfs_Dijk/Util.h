#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#include "stdafx.h"

using namespace std;

//�������ߣ��ַ����и�
int split(const string& str, vector<string>& ret_, string sep = ",");


//�������ߣ��жϼ���A�Ƿ��������B�е�ȫ��Ԫ��----�϶����Ա��Ż�
bool containsAll(vector<int>& A,vector<int>& B);