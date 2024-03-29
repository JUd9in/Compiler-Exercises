#! /usr/bin/env python
# coding=utf-8
from __future__ import division

v_table = {}  # variable table

break_flag=True

def update_v_table(name, value):
    v_table[name] = value



def trans(node):
    global break_flag
    # for c in node.getchildren():
    #     trans(c)

    # Translation
    if node.getdata() == '[STATEMENTS]':
        for c in node.getchildren():
            trans(c)
        if len(node.getchildren()) == 2:
            if False in [node.getchild(0).getvalue(), node.getchild(1).getvalue()]:
                node.setvalue(False)
        else:
            node.setvalue(node.getchild(0).getvalue())
    elif node.getdata() == '[STATEMENT]':
        for c in node.getchildren():
            trans(c)
        node.setvalue(node.getchild(0).getvalue())
    # Assignment
    elif node.getdata() == '[ASSIGNMENT]':
        for c in node.getchildren():
            trans(c)
        if len(node.getchildren()) == 3:
            value = node.getchild(2).getvalue()
            node.getchild(0).setvalue(value)
            # update v_table
            update_v_table(node.getchild(0).getdata(), value)
        else:
            value_list = node.getchild(3).getvalue()
            node.getchild(0).setvalue(value_list)
            update_v_table(node.getchild(0).getdata(), value_list)


    elif node.getdata() == '[IF]':
        r'''if : IF '(' condition ')' '{' statements '}'
           | IF '(' condition ')' '{' statements '}' ELIF '(' condition ')' '{' statements '}' ELSE '{' statements '}' '''
        if len(node.getchildren()) == 2:
            children = node.getchildren()
            trans(children[0])
            condition = children[0].getvalue()
            if condition:
                for c in children[1:]:
                    trans(c)
        else:
            children = node.getchildren()
            trans(children[0])
            trans(children[2])
            c1 = children[0].getvalue()
            c2 = children[2].getvalue()
            if c1:
                trans(children[1])
            elif c2:
                trans(children[3])
            else:
                trans(children[4])
                if children[4].getchild(0).getdata() == 'break' and children[4].getchild(0).getvalue() == False:
                    node.setvalue(False)


    # While
    elif node.getdata() == '[WHILE]':
        r'''while : WHILE '(' condition ')' '{' statements '}' '''
        children = node.getchildren()
        while trans(children[0]):
            trans(children[1])
            if break_flag is False:
                break


    elif node.getdata() == '[BREAK]':
        node.getchild(0).setvalue(False)
        node.setvalue(False)
        break_flag=False

    # For
    elif node.getdata() == '[FOR]':
        '''for : FOR '(' operation ';' condition ';' operation ')' '{' statements '}' '''
        children = node.getchildren()
        trans(children[0])
        # v=v_table[children[0].getchild(0).getdata()]
        while trans(children[1]):
            trans(children[3])
            trans(children[2])

    # Condition
    elif node.getdata() == '[CONDITION]':
        '''condition : VARIABLE '>' VARIABLE
                     | VARIABLE '<' VARIABLE'''
        for c in node.getchildren():
            trans(c)
        if len(node.getchildren()) == 3:
            arg0 = v_table[node.getchild(0).getdata()]
            try:
                if (type(eval(node.getchild(2).getdata())) == int) or (type(eval(node.getchild(2).getdata())) == float):
                    arg1 = eval(node.getchild(2).getdata())
            except NameError:
                arg1 = v_table[node.getchild(2).getdata()]
            op = node.getchild(1).getdata()
            if op == '>':
                node.setvalue(arg0 > arg1)
            elif op == '<':
                node.setvalue(arg0 < arg1)
        elif len(node.getchildren()) == 4:
            arg0 = v_table[node.getchild(0).getdata()]
            arg1 = v_table[node.getchild(3).getdata()]
            node.setvalue(arg0 <= arg1)
        else:
            arg0 = v_table[node.getchild(0).getdata()]
            num1 = int(node.getchild(2).getvalue())
            arg1 = v_table[node.getchild(5).getdata()]
            op = node.getchild(4).getdata()
            if op == '>':
                node.setvalue(arg0[num1] > arg1)
            elif op == '<':
                node.setvalue(arg0[num1] < arg1)


    # Modification
    elif node.getdata() == '[MODIFICATION]':
        for c in node.getchildren():
            trans(c)
        if len(node.getchildren()) == 4:
            arg0 = v_table[node.getchild(0).getdata()]
            num1 = int(node.getchild(1).getvalue())
            arg1 = v_table[node.getchild(2).getdata()]
            num2 = int(node.getchild(3).getvalue())
            arg0[num1] = arg1[num2]
            update_v_table(node.getchild(0).getdata(), arg0)
        elif len(node.getchildren()) == 3:
            arg0 = v_table[node.getchild(0).getdata()]
            num1 = int(node.getchild(1).getvalue())
            value = v_table[node.getchild(2).getdata()]
            arg0[num1] = value
            update_v_table(node.getchild(0).getdata(), arg0)

    # Operation
    elif node.getdata() == '[OPERATION]':
        for c in node.getchildren():
            trans(c)
        if len(node.getchildren()) == 3:
            value = node.getchild(2).getvalue()
            node.getchild(0).setvalue(value)
            update_v_table(node.getchild(0).getdata(), value)
        elif len(node.getchildren()) == 1:
            value = v_table[node.getchild(0).getdata()]
            value += 1
            node.getchild(0).setvalue(value)
            update_v_table(node.getchild(0).getdata(), value)
            # print(v_table)

    elif node.getdata() == '[FACTOR]':
        for c in node.getchildren():
            trans(c)
        if len(node.getchildren()) == 3:
            arg0 = node.getchild(1).getvalue()
            node.setvalue(arg0)
        else:
            if (type(node.getchild(0).getvalue()) == float) or (type(node.getchild(0).getvalue()) == int):
                node.setvalue(node.getchild(0).getvalue())
            else:
                arg0 = v_table[node.getchild(0).getdata()]
                node.setvalue(arg0)
                update_v_table(node.getchild(0).getdata(), arg0)

    elif node.getdata() == '[TERM]':
        for c in node.getchildren():
            trans(c)
        if len(node.getchildren()) == 1:
            arg0 = node.getchild(0).getvalue()
            node.setvalue(arg0)
        else:
            arg0 = node.getchild(0).getvalue()
            arg1 = node.getchild(2).getvalue()
            op = node.getchild(1).getdata()
            if op == '*':
                value = arg0 * arg1
            elif op == '/':
                value = arg0 // arg1
            else:
                value = arg0 // arg1
            node.setvalue(value)

    elif node.getdata() == '[EXPR]':
        for c in node.getchildren():
            trans(c)
        if len(node.getchildren()) == 3:
            if node.getchild(1).getdata() == '+' or node.getchild(1).getdata() == '-':
                arg0 = node.getchild(0).getvalue()
                arg1 = node.getchild(2).getvalue()
                op = node.getchild(1).getdata()
                if op == '+':
                    value = arg0 + arg1
                else:
                    value = arg0 - arg1
            else:
                arg0 = node.getchild(1).getvalue()
                # len()
                value = len(arg0)
        elif len(node.getchildren()) == 1:
            value = node.getchild(0).getvalue()
        else:
            temp_l = v_table[node.getchild(0).getdata()]
            num = int(node.getchild(2).getvalue())
            value = temp_l[num]
        node.setvalue(value)

    # Print
    elif node.getdata() == '[PRINT]':
        for c in node.getchildren():
            trans(c)
        value = node.getchild(2).getvalue()
        for i in range(len(value)):
            if i != len(value) - 1:
                print(value[i], end=' , ')
            else:
                print(value[i], end='\n')

    elif node.getdata() == '[SENTENCE]':
        for c in node.getchildren():
            trans(c)
        if len(node.getchildren()) == 1:
            value = [node.getchild(0).getvalue()]
        else:
            value = [node.getchild(0).getvalue()] + node.getchild(2).getvalue()
        node.setvalue(value)

    elif node.getdata() == '[WORD]':
        for c in node.getchildren():
            trans(c)
        try:
            if (type(eval(node.getchild(0).getdata())) == int) or (type(eval(node.getchild(0).getdata())) == float):
                # print(node.getchild(0).getvalue(),end='haha\n')
                node.setvalue(node.getchild(0).getvalue())
        except Exception:
            value = v_table[node.getchild(0).getdata()]
            node.setvalue(value)
            update_v_table(node.getchild(0).getdata(), value)
    else:
        for c in node.getchildren():
            trans(c)
    # for c in node.getchildren():
    #     trans(c)
    return node.getvalue()
