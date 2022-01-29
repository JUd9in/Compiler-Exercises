#include "initial_rules.h"
#include <sstream>

int main()
{
	initialMap();
	cout << "请输入需要进行语法分析的串(为了方便表示,输出的结果中G代表E',H代表T')：" << endl;
	cin >> input;//输入串存在input中
	input[input.length()] = '$';//将输入串尾部赋为'$'
	Stack.push('$');//初始化栈
	Stack.push('E');
	X = Stack.top();//将栈顶元素赋值给X
	//map<char, vector<char>> res;
	string resS = "[E]";  //初始化结果串
	while (X != '$') {
		a = input[index];//a是当前input串指针指向的元素
		x = notTerSym[X];//x对应的预测表达式的一维坐标
		y = terSym[a];//a对应的预测表达式的二维坐标
		if (X == a) {  //X等于input串指针指向的元素
			Stack.pop();
			index++;
		}
		else if (isTerSym(X)) {//X是一个终结符
			cout << "栈顶字符" << X << "与输入串第" << index + 1 << "个字符'" << a << "'不匹配" << endl;
			break;
		}
		else if (form[x][y].empty()) {//预测分析表中匹配到一个error项
			cout << "匹配输入串中第" << index + 1 << "个字符'" << a << "'时发生错误" << endl;
			break;
		}
		else {//在预测分析表中找到了匹配的产生式
			cout << "matched " << X << "->" << form[x][y] << endl;
			//vector<char> temp;
			char flag;
			for (int i = 0; i < form[x][y].size(); i++) {
				//temp.push_back(form[x][y][i]);
				//cout << form[x][y][i] << endl;
				int indx;
				if (i == 0) {
					flag = X;
					indx = resS.find_last_of(flag) + 1;
					
				}
				else {
					flag = form[x][y][i - 1];
					indx= resS.find_last_of(flag) + 2;
				}
				stringstream ss;
				ss << form[x][y][i];
				string str2 = ss.str();
				string temp = "[]";
				temp.insert(1, str2);
				//cout << temp << endl;
				resS.insert(indx, temp);
			}
			//res[X] = temp;
			Stack.pop();
			if (form[x][y] == "e") {//如果产生式是X->e
				//不需要压入栈Stack
			}
			else {
				for (int i = form[x][y].length() - 1; i >= 0; i--) {//将产生式右部倒序压入栈
					Stack.push(form[x][y][i]);
				}
			}
		}
		X = Stack.top();//X重新赋值为栈顶元素
	}
	if (index == input.length()) {
		cout << "此表达式正确" << endl;
		cout << "该表达式的语法树对应的字符串为" << endl;
		cout << resS << endl;
	}
	else {
		cout << "此表达式错误" << endl;
	}
	cout << "\n按任意键退出....." << endl;
	cin.get();
	cin.get();
	return 0;
}