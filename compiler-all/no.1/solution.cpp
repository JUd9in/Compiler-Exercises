#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>
#include <stack>
#include <set>
#include <map>
#include <queue>
#include <fstream>
using namespace std;

struct n  //nfa
{
    vector<int> a[2], e;
    bool f = 0;
    bool s = 0;
};

vector<n> nfa;

struct d  //dfa
{
    int a[2] = { -1,-1 };
    bool f = 0;
    bool s = 0;

};

vector<d> dfa;

stack<int> st;

int nfa_size, dfa_size;
string dispregex;

struct n init_nfa_state;

struct d init_dfa_state;

//未使用面向对象，直接用了全局变量

void custom_clear() {
    for (int i = 0; i < 5; i++) cout << endl;  //清屏
}

//正则到nfa

string insert_concat(string regexp) {  //解析输入的正则式
    string ret = "";
    char c, c2;
    string s;
    for (unsigned int i = 0; i < regexp.size(); i++) {
        s = regexp[i];
        if (s == "|") {
            c = '+';
        }
        else {
            c = regexp[i];
        }

        if (i + 1 < regexp.size()) {
            s = regexp[i+1];
            if (s == "|") {
                c2 = '+';
            }
            else {
                c2 = regexp[i+1];
            }
            ret += c;
            if (c != '(' && c2 != ')' && c != '+' && c2 != '+' && c2 != '*') {
                ret += '.';  
            }
        }
    }
    ret += regexp[regexp.size() - 1];
    return ret;
}

void character(int i)
{
    nfa.push_back(init_nfa_state);
    nfa.push_back(init_nfa_state);
    nfa[nfa_size].a[i].push_back(nfa_size + 1);
    st.push(nfa_size);
    nfa_size++;
    st.push(nfa_size);
    nfa_size++;
}

void union_() //+运算
{
    nfa.push_back(init_nfa_state);
    nfa.push_back(init_nfa_state);
    int d = st.top(); st.pop();
    int c = st.top(); st.pop();
    int b = st.top(); st.pop();
    int a = st.top(); st.pop();
    nfa[nfa_size].e.push_back(a);
    nfa[nfa_size].e.push_back(c);
    nfa[b].e.push_back(nfa_size + 1);
    nfa[d].e.push_back(nfa_size + 1);
    st.push(nfa_size);
    nfa_size++;
    st.push(nfa_size);
    nfa_size++;
}

void concatenation()  //连接运算
{
    int d = st.top(); st.pop();
    int c = st.top(); st.pop();
    int b = st.top(); st.pop();
    int a = st.top(); st.pop();
    nfa[b].e.push_back(c);
    st.push(a);
    st.push(d);
}

void kleene_star()  //星运算
{
    nfa.push_back(init_nfa_state);
    nfa.push_back(init_nfa_state);
    int b = st.top();
    st.pop();
    int a = st.top();
    st.pop();
    nfa[nfa_size].e.push_back(a);
    nfa[nfa_size].e.push_back(nfa_size + 1);
    nfa[b].e.push_back(a);
    nfa[b].e.push_back(nfa_size + 1);
    st.push(nfa_size);
    nfa_size++;
    st.push(nfa_size);
    nfa_size++;
}

void postfix_to_nfa(string postfix) //后缀转nfa
{
    for (unsigned int i = 0; i < postfix.size(); i++)
    {
        switch (postfix[i])
        {
        case 'a':
        case 'b': character(postfix[i] - 'a'); break;
        case '*': kleene_star(); break;
        case '.': concatenation(); break;
        case '+': union_();
        }
    }
}

void display_nfa()
{
    cout << endl << endl;
    cout << "MYT算法将正则表达式转换成NFA\n";
    cout << "-----------------------------------------------------------------------------------------\n";
    cout << "状态\t|\ta\t|\tb\t|\te\t|是否为开始状态\t|是否为接受状态\t|" << endl;
    cout << "-----------------------------------------------------------------------------------------\n";
    for (unsigned int i = 0; i < nfa.size(); i++)
    {
        cout << i << "\t|\t";
        for (unsigned int j = 0; j < nfa[i].a[0].size(); j++)cout << nfa[i].a[0][j] << ' ';
        cout << "\t|\t";
        for (unsigned int j = 0; j < nfa[i].a[1].size(); j++)cout << nfa[i].a[1][j] << ' ';
        cout << "\t|\t";
        for (unsigned int j = 0; j < nfa[i].e.size(); j++)cout << nfa[i].e[j] << ' ';
        cout << "\t|\t";
        if (nfa[i].s)cout << "Yes"; else cout << "No";
        cout << "\t|\t";
        if (nfa[i].f)cout << "Yes"; else cout << "No";
        cout << "\t|\n";
    }
    cout << "-----------------------------------------------------------------------------------------\n";
}

void output_nfa(string path) {  //输出nfa到txt
    ofstream outfile(path);
    outfile.clear();
    outfile << endl << endl;
    outfile << "MYT算法将正则表达式转换成NFA\n";
    outfile << "-----------------------------------------------------------------------------------------\n";
    for (unsigned int i = 0; i < nfa.size(); i++)
    {
        if (nfa[i].a[0].size() > 0) {
            outfile << i << "\ta\t";
            for (unsigned int j = 0; j < nfa[i].a[0].size(); j++)outfile << nfa[i].a[0][j] << ' ';
            outfile << "\t\n";
        }

        if (nfa[i].a[1].size() > 0) {
            outfile << i << "\tb\t";
            for (unsigned int j = 0; j < nfa[i].a[1].size(); j++)outfile << nfa[i].a[1][j] << ' ';
            outfile << "\t\n";
        }

        if (nfa[i].e.size() > 0) {
            outfile << i << "\te\t";
            for (unsigned int j = 0; j < nfa[i].e.size(); j++)outfile << nfa[i].e[j] << ' ';
            outfile << "\t\n";
        }

    }
    outfile << "start state:";
    for (int i = 0; i < nfa.size(); i++) {
        if (nfa[i].s) outfile << i << "\t";
    }
    outfile<< endl << "accepting state:";
    for (int i = 0; i < nfa.size(); i++) {
        if (nfa[i].f) outfile << i << "\t";
    }
    outfile << endl;
    outfile << "-----------------------------------------------------------------------------------------\n";
    outfile.close();
}

int priority(char c) {  //区分优先级
    switch (c) {
    case '*': return 3;
    case '.': return 2;
    case '+': return 1;
    default: return 0;
    }
}

string regexp_to_postfix(string regexp) //转为后缀表达式
{
    string postfix = "";
    stack<char> op;
    char c;
    for (unsigned int i = 0; i < regexp.size(); i++)
    {
        switch (regexp[i])
        {
        case 'a':
        case 'b':
            postfix += regexp[i]; break;
        case '(':
            op.push(regexp[i]); break;
        case ')':
            while (op.top() != '(') {
                postfix += op.top();
                op.pop();
            }
            op.pop();
            break;
        default:
            while (!op.empty()) {
                c = op.top();
                if (priority(c) >= priority(regexp[i])) {
                    postfix += op.top();
                    op.pop();
                }
                else break;
            }
            op.push(regexp[i]);
        }
    }
    while (!op.empty())
    {
        postfix += op.top();
        op.pop();
    }
    return postfix;
}

//nfa到dfa

void output_dfa(string path) {
    ofstream outfile(path);
    outfile.clear();
    outfile << endl;
    outfile << "NFA到DFA的转换" << endl;
    outfile << "---------------------------------------------------------" << endl;
    for (int i = 0; i < dfa.size(); i++) {
        if (dfa[i].f || (dfa[i].a[0]) == i && dfa[i].a[1] == i) {
        }
        else {
            outfile << i << "\t" << "a\t" << dfa[i].a[0] << endl;
            outfile << i << "\t" << "b\t" << dfa[i].a[1] << endl;
        }

    }
    outfile << "start state:" << 0 << endl << "accepting state:";
    for (int i = 0; i < dfa.size(); i++) {
        if (dfa[i].f) outfile << i << "\t";
    }
    outfile << endl;
    outfile << "---------------------------------------------------------" << endl;
    outfile.close();
}

void print_dfa() {
    cout << endl;
    cout << "NFA到DFA的转换" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "状态\t|\t" << "a" << "\t|\t" << "b" << "\t|\t" << "接受状态" << "|" << endl;
    cout << "---------------------------------------------------------" << endl;
    for (int i = 0; i < dfa.size(); i++) {
        cout << i << "\t|\t";
        if (dfa[i].f || (dfa[i].a[0]) == i && dfa[i].a[1] == i) {
            cout << "\\" << "\t|\t";
            cout << "\\" << "\t|\t";
        }
        else {
            cout << dfa[i].a[0] << "\t|\t";
            cout << dfa[i].a[1] << "\t|\t";
        }
        if (dfa[i].f) cout << "Yes\t|"; else cout << "No\t|";
        cout << endl;
    }
    cout << "start state:\t" << 0 << endl;
    cout << "---------------------------------------------------------" << endl;
}

void epsilon_closure(int state, set<int>& si) {  //求闭包，递归
    for (unsigned int i = 0; i < nfa[state].e.size(); i++) {
        if (si.count(nfa[state].e[i]) == 0) {
            si.insert(nfa[state].e[i]);
            epsilon_closure(nfa[state].e[i], si);
        }
    }
}

set<int> state_change(int c, set<int>& si) {  
    set<int> temp;
    if (c == 1) {
        for (std::set<int>::iterator it = si.begin(); it != si.end(); ++it) {
            for (unsigned int j = 0; j < nfa[*it].a[0].size(); j++) {
                temp.insert(nfa[*it].a[0][j]);
            }
        }
    }
    else {
        for (std::set<int>::iterator it = si.begin(); it != si.end(); ++it) {
            for (unsigned int j = 0; j < nfa[*it].a[1].size(); j++) {
                temp.insert(nfa[*it].a[1][j]);
            }
        }
    }
    return temp;
}

void nfa_to_dfa(set<int>& si, queue<set<int> >& que, int start_state) {
    map<set<int>, int> mp;
    mp[si] = -1;
    set<int> temp1;
    set<int> temp2;
    int ct = 0;
    si.clear();
    si.insert(0);
    epsilon_closure(start_state, si);
    if (mp.count(si) == 0) {
        mp[si] = ct++;
        que.push(si);
    }
    int p = 0;
    bool f1 = false;
    bool s1 = false;
    while (que.size() != 0) {
        dfa.push_back(init_dfa_state);
        si.empty();
        si = que.front();
        f1 = false;
        //s1 = false;  //额外设置一个flag不可行
        for (set<int>::iterator it = si.begin(); it != si.end(); ++it) {
            if (nfa[*it].f == true)
                f1 = true;
        }
        //for (set<int>::iterator it = si.begin(); it != si.end(); ++it) {
        //    if (nfa[*it].s == true)
        //        s1 = true;
        //}
        //dfa[p].s = s1;
        dfa[p].f = f1;
        temp1 = state_change(1, si);
        si = temp1;
        for (set<int>::iterator it = si.begin(); it != si.end(); ++it) {
            epsilon_closure(*it, si);
        }
        if (mp.count(si) == 0) {
            mp[si] = ct++;
            que.push(si);
            dfa[p].a[0] = ct - 1;
        }
        else {
            dfa[p].a[0] = mp.find(si)->second;
        }
        temp1.clear();

        si = que.front();
        temp2 = state_change(2, si);
        si = temp2;
        for (set<int>::iterator it = si.begin(); it != si.end(); ++it) {
            epsilon_closure(*it, si);
        }
        if (mp.count(si) == 0) {
            mp[si] = ct++;
            que.push(si);
            dfa[p].a[1] = ct - 1;
        }
        else {
            dfa[p].a[1] = mp.find(si)->second;
        }
        temp2.clear();
        que.pop();
        p++;
    }
    for (int i = 0; i < p; i++) {
        if (dfa[i].a[0] == -1)dfa[i].a[0] = p;
        if (dfa[i].a[1] == -1)dfa[i].a[1] = p;
    }
    dfa.push_back(init_dfa_state);
    dfa[p].a[0] = p;
    dfa[p].a[1] = p;
}

//最小化dfa

pair<int, vector<tuple<int, int, bool> > > minimize_dfa(vector<d> dfa) {
    vector<int> grp(dfa.size());   
    vector<vector<int> > part(2, vector<int>());  

    //初始化groups
    part[0].push_back(0);
    for (int i = 1; i < (int)grp.size(); i++) {
        if (dfa[i].f == dfa[0].f) {
            grp[i] = 0;
            part[0].push_back(i);
        }
        else {
            grp[i] = 1;
            part[1].push_back(i);
        }
    }

    if (!part[1].size()) part.erase(part.end());

    ///循环到没有partition创建
    bool chk = true; 
    int strt = 0;   // 开始状态
    while (chk) {
        chk = false;

        for (int i = 0; i < part.size(); i++) {
            for (int j = 0; j < 2; j++) {
                vector<pair<int, int> > trans(part[i].size());   /// 分区状态的转换
                for (int k = 0; k < part[i].size(); k++) {
                    if (dfa[part[i][k]].a[j] >= 0)
                        trans[k] = make_pair(grp[dfa[part[i][k]].a[j]], part[i][k]);
                    else
                        trans[k] = make_pair(-1, part[i][k]);
                }
                sort(trans.begin(), trans.end());

                if (trans[0].first != trans[trans.size() - 1].first) {
                    chk = true;

                    int k, m = part.size() - 1;

                    part[i].clear();
                    part[i].push_back(trans[0].second);
                    for (k = 1; k < trans.size() and (trans[k].first == trans[k - 1].first); k++) {
                        part[i].push_back(trans[k].second);
                    }

                    while (k < trans.size()) {
                        if (trans[k].first != trans[k - 1].first) {
                            part.push_back(vector<int>());
                            m++;
                        }
                        grp[trans[k].second] = m;
                        part[m].push_back(trans[k].second);
                        k++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < part.size(); i++) {
        for (int j = 0; j < part[i].size(); j++) {
            if (part[i][j] == 0) strt = i;
        }
    }

    vector<tuple<int, int, bool> > ret(part.size());
    for (int i = 0; i < (int)part.size(); i++) {
        //cout<<grp[part[i][0]]<<endl;
        get<0>(ret[i]) = (dfa[part[i][0]].a[0] >= 0) ? grp[dfa[part[i][0]].a[0]] : -1;
        get<1>(ret[i]) = (dfa[part[i][0]].a[1] >= 0) ? grp[dfa[part[i][0]].a[1]] : -1;
        get<2>(ret[i]) = dfa[part[i][0]].f;
    }

    return make_pair(strt, ret);
}

void print_menu() {
    cout << "\n---------------------------------------\n";
    cout << "输入的正则式: " << dispregex << endl << endl;
    cout << "1. NFA\n";
    cout << "2. 转为DFA\n";
    cout << "3. 最小化DFA\n";
    //cout << "4. Simulation\n";
    cout << "输入其他键以退出...\n\n";
}

void output_minDFA(string path, int st_state, vector<tuple<int, int, bool> > min_dfa) {
    ofstream outfile(path);
    outfile.clear();
    outfile << "最小化DFA" << endl;
    outfile << "---------------------------------------------------------" << endl;
    for (int i = 0; i < (int)min_dfa.size(); i++) {
        
        if ((get<2>(min_dfa[i])) || (get<0>(min_dfa[i]) == i && get<1>(min_dfa[i]) == i)) {

        }
        else {
            outfile << i << "\ta\t" << get<0>(min_dfa[i]) << endl;
            outfile << i << "\tb\t" << get<1>(min_dfa[i]) << endl;
        }

    }
    outfile << "start state:" << st_state << endl << "accepting state:";
    for (int i = 0; i < (int)min_dfa.size(); i++) {
        if (get<2>(min_dfa[i])) outfile << i << "\t";
    }
    outfile << endl;
    outfile << "---------------------------------------------------------" << endl;
    outfile.close();
}

void print(vector<tuple<int, int, bool> > min_dfa) {
    cout << "最小化DFA" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "状态\t|\ta\t|\ta\t|\t结束状态|" << endl;
    cout << "---------------------------------------------------------" << endl;
    for (int i = 0; i < (int)min_dfa.size(); i++) {
        cout << i << "\t|\t";
        if ((get<2>(min_dfa[i]))||(get<0>(min_dfa[i])==i && get<1>(min_dfa[i]) == i)) {
            cout << "\\" << "\t|\t";
            cout << "\\" << "\t|\t";
        }
        else {
            cout << get<0>(min_dfa[i]) << "\t|\t";
            cout << get<1>(min_dfa[i]) << "\t|\t";
        }
        if (get<2>(min_dfa[i])) cout << "Yes\t|"; else cout << "No\t|";
        cout << endl;
    }
    cout << "---------------------------------------------------------" << endl;
}



int main()
{
    custom_clear();
    string regexp,postfix;
    cout << "本程序支持的正则符号有|, +, *, (, ), 其中+与|均表示或运算\n";
    cout<<"输入正则表达式: ";
    cin>>regexp;
    dispregex=regexp;
    regexp=insert_concat(regexp);
    postfix = regexp_to_postfix(regexp);
    cout<<"转为后缀表达式: "<<postfix<<endl;  
    postfix_to_nfa(postfix);

    int final_state=st.top();st.pop();
    int start_state=st.top();st.pop();
    nfa[final_state].f=1;
    nfa[start_state].s = 1;

    set<int> si;
    queue<set<int> > que;
    nfa_to_dfa(si,que,start_state);

    cout<<endl<<endl;

    pair<int,vector<tuple<int,int,bool> > > min_dfa_tmp = minimize_dfa(dfa);

    vector<tuple<int,int,bool> >  min_dfa= min_dfa_tmp.second;
    int start_st = min_dfa_tmp.first;

    getchar();
    custom_clear();


    while(1){
        print_menu();
        char choice;
        choice=getchar();
        custom_clear();

        switch(choice) {
        case '1':
            display_nfa();
            output_nfa(".\\output1.txt");
            getchar();
            break;
        case '2':
            print_dfa();
            output_dfa(".\\output2.txt");
            getchar();
            break;
        case '3':
            print(min_dfa);
            output_minDFA(".\\output3.txt", start_st, min_dfa);
            cout << "start state:\t" << start_st << endl;
            getchar();
            break;
        default:
            exit(EXIT_SUCCESS);
        }
    }
    cout<<endl<<endl;
    cout<<"Enter string : ";
    string input;
    cin.ignore();
    getline(cin,input);
    int curr_state,next_state;
    while(input!=""){
        //cout<<input<<endl;
        curr_state=start_st;
        for(unsigned i=0;i<input.size();i++){
            if(curr_state>=0){
                if(input[i]=='a')
                    next_state=get<0>(min_dfa[curr_state]);
                else
                    next_state=get<1>(min_dfa[curr_state]);
                if(next_state>=0){
                    cout<<input[i]<<" : 状态 "<<curr_state<<" -> 状态 "<<next_state<<endl;
                }
                else cout<<input[i]<<" : 状态 "<<curr_state<<" -> 俘获状态"<<endl;
            }
            else cout<<input[i]<<" : 俘获"<<endl;
            curr_state=next_state;
        }
        if(curr_state>=0&&get<2>(min_dfa[curr_state]))cout<<"accepted"; else cout<<"rejected";
        cout<<endl<<endl;
        cout<<"Enter string : ";
        getline(cin,input);
    }
    return 0;
}

