#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#include "stdafx.h"

using namespace std;

//辅助工具，字符串切割
int split(const string& str, vector<string>& ret_, string sep = ",");


//辅助工具，判断几何A是否包含集合B中的全部元素----肯定可以被优化
bool containsAll(vector<int>& A,vector<int>& B);