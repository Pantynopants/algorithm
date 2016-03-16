SDK-gcc目录下为c/c++版本的SDK，具体使用方法参看该路径下的readme。
SDK-java目录下为java版本的SDK，具体使用方法参看该路径下的readme。
test-case目录下为两套测试例，其中topo.csv为图的信息文件，demand.csv为路径信息文件，sample_result.csv为输出结果文件样例。其中case0目录下的用例为题目描述中的用例，case1中的用例为大赛提供的中等复杂度用例，为便于理解和调试大赛为选手提供了case1中topo以及一条符合要求的有效路径的样例图供参考。
大赛提供的SDK仅供参考，选手可以选择自行解析测试用例，但需保证符合判题程序要求。判题时调用可执行程序输入的参数表： your_program xxx/topo.csv xxx/demand.csv xxx/result.csv 。参数的顺序从左到右为topo(图的数据G)、demand(需要计算的路径信息:s,t,V')、result(计算结果)，文件具体格式请参考赛题描述。