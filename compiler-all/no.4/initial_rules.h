#include <string>
#include <map>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

string form[5][8] = {  //�����ķ�����һ��Ԥ�������Ϊ�˲���ʹ���Ұ��ķ���չ���˼Ӽ��˳�
	{"","","","","TG","","TG",""},
	{"+TG","-TG","","","","e","","e"},
	{"","","","","FH","","FH",""},
	{"e","e","*FH","/FH","","e","","e"},
	{"","","","","(E)","","i",""},
};

string notTerminalSymbol = "EGTHF";  //���ս��,Ϊ�˷����ʾ,G����E',H����T'
string terminalSymbol = "+-*/()i$";  //�ս�������봮ĩβ$
map<char, int>notTerSym;  //���� ���ս�� ��Ԥ�����������ļ�ֵ��
map<char, int>terSym;  //���� �ս�� ��Ԥ�����������ļ�ֵ��
string input;  //������봮
stack<char> Stack;  //����ջ
int x, y;  //�����Ҫ��Ԥ��������в��ҵ�����
char a, X;  //a���input��ָ�뵱ǰָ����ַ���X���ջ��Ԫ��
int index = 0;  //���봮���±�

void initialMap()  //��ʼ��map��ֵ��
{
	for (int i = 0; i < 5; i++) {  // "EGTHF" �ļ�ֵ�ֱ�Ϊ 0,1...4
		notTerSym[notTerminalSymbol[i]] = i;
	}
	for (int i = 0; i < 8; i++) {  // "+-*/()i$" �ļ�ֵ�ֱ�Ϊ 0,1...7
		terSym[terminalSymbol[i]] = i;
	}
}

bool isTerSym(char x)  //�ж��Ƿ����ս�����Ƿ���true�����򷵻�false
{
	for (int i = 0; i < terminalSymbol.length(); i++) {
		if (x == terminalSymbol[i])return true;
	}
	return false;
}
