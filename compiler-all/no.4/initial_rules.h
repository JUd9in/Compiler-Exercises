#include <string>
#include <map>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

string form[5][8] = {  //根据文法构造一个预测分析表，为了测试使用我把文法扩展到了加减乘除
	{"","","","","TG","","TG",""},
	{"+TG","-TG","","","","e","","e"},
	{"","","","","FH","","FH",""},
	{"e","e","*FH","/FH","","e","","e"},
	{"","","","","(E)","","i",""},
};

string notTerminalSymbol = "EGTHF";  //非终结符,为了方便表示,G代表E',H代表T'
string terminalSymbol = "+-*/()i$";  //终结符和输入串末尾$
map<char, int>notTerSym;  //创建 非终结符 和预测分析表坐标的键值对
map<char, int>terSym;  //创建 终结符 和预测分析表坐标的键值对
string input;  //存放输入串
stack<char> Stack;  //分析栈
int x, y;  //存放需要在预测分析表中查找的坐标
char a, X;  //a存放input串指针当前指向的字符，X存放栈顶元素
int index = 0;  //输入串的下标

void initialMap()  //初始化map键值对
{
	for (int i = 0; i < 5; i++) {  // "EGTHF" 的键值分别为 0,1...4
		notTerSym[notTerminalSymbol[i]] = i;
	}
	for (int i = 0; i < 8; i++) {  // "+-*/()i$" 的键值分别为 0,1...7
		terSym[terminalSymbol[i]] = i;
	}
}

bool isTerSym(char x)  //判断是否是终结符，是返回true，否则返回false
{
	for (int i = 0; i < terminalSymbol.length(); i++) {
		if (x == terminalSymbol[i])return true;
	}
	return false;
}
