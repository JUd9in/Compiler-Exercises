#include "initial_rules.h"
#include <sstream>

int main()
{
	initialMap();
	cout << "��������Ҫ�����﷨�����Ĵ�(Ϊ�˷����ʾ,����Ľ����G����E',H����T')��" << endl;
	cin >> input;//���봮����input��
	input[input.length()] = '$';//�����봮β����Ϊ'$'
	Stack.push('$');//��ʼ��ջ
	Stack.push('E');
	X = Stack.top();//��ջ��Ԫ�ظ�ֵ��X
	//map<char, vector<char>> res;
	string resS = "[E]";  //��ʼ�������
	while (X != '$') {
		a = input[index];//a�ǵ�ǰinput��ָ��ָ���Ԫ��
		x = notTerSym[X];//x��Ӧ��Ԥ����ʽ��һά����
		y = terSym[a];//a��Ӧ��Ԥ����ʽ�Ķ�ά����
		if (X == a) {  //X����input��ָ��ָ���Ԫ��
			Stack.pop();
			index++;
		}
		else if (isTerSym(X)) {//X��һ���ս��
			cout << "ջ���ַ�" << X << "�����봮��" << index + 1 << "���ַ�'" << a << "'��ƥ��" << endl;
			break;
		}
		else if (form[x][y].empty()) {//Ԥ���������ƥ�䵽һ��error��
			cout << "ƥ�����봮�е�" << index + 1 << "���ַ�'" << a << "'ʱ��������" << endl;
			break;
		}
		else {//��Ԥ����������ҵ���ƥ��Ĳ���ʽ
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
			if (form[x][y] == "e") {//�������ʽ��X->e
				//����Ҫѹ��ջStack
			}
			else {
				for (int i = form[x][y].length() - 1; i >= 0; i--) {//������ʽ�Ҳ�����ѹ��ջ
					Stack.push(form[x][y][i]);
				}
			}
		}
		X = Stack.top();//X���¸�ֵΪջ��Ԫ��
	}
	if (index == input.length()) {
		cout << "�˱��ʽ��ȷ" << endl;
		cout << "�ñ��ʽ���﷨����Ӧ���ַ���Ϊ" << endl;
		cout << resS << endl;
	}
	else {
		cout << "�˱��ʽ����" << endl;
	}
	cout << "\n��������˳�....." << endl;
	cin.get();
	cin.get();
	return 0;
}