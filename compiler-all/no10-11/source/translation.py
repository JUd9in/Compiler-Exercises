#! /usr/bin/env python
# coding=utf-8
from __future__ import division

v_table = {}  # variable table


def update_v_table(name, value):
    v_table[name] = value


def trans(node):
    for c in node.getchildren():
        trans(c)

    # Translation

    # Assignment
    if node.getdata() == '[ASSIGNMENT]':
        ''' statement : VARIABLE '=' NUMBER'''
        value = node.getchild(2).getvalue()
        node.getchild(0).setvalue(value)
        # update v_table
        update_v_table(node.getchild(0).getdata(), value)

    # Operation
    elif node.getdata() == '[OPERATION]':
        value = node.getchild(2).getvalue()
        node.getchild(0).setvalue(value)
        update_v_table(node.getchild(0).getdata(), value)

    elif node.getdata() == '[FACTOR]':
        if len(node.getchildren()) == 3:
            arg0 = node.getchild(1).getvalue()
            node.setvalue(arg0)
        else:
            if type(node.getchild(0).getvalue()) == (float or int):
                node.setvalue(node.getchild(0).getvalue())
            else:
                arg0 = v_table[node.getchild(0).getdata()]
                node.setvalue(arg0)
                update_v_table(node.getchild(0).getdata(), arg0)

    elif node.getdata() == '[TERM]':
        if len(node.getchildren()) == 1:
            arg0 = node.getchild(0).getvalue()
            node.setvalue(arg0)
        else:
            arg0 = node.getchild(0).getvalue()
            arg1 = node.getchild(2).getvalue()
            op = node.getchild(1).getdata()
            if op == '*':
                value = arg0 * arg1
            else:
                value = arg0 / arg1
            node.setvalue(value)

    elif node.getdata() == '[EXPR]':
        if len(node.getchildren()) == 3:
            arg0 = node.getchild(0).getvalue()
            arg1 = node.getchild(2).getvalue()
            op = node.getchild(1).getdata()
            if op == '+':
                value = arg0 + arg1
            else:
                value = arg0 - arg1
        else:
            value = node.getchild(0).getvalue()
        node.setvalue(value)

    # Print
    elif node.getdata() == '[PRINT]':
        value = node.getchild(2).getvalue()
        for i in range(len(value)):
            if i != len(value) - 1:
                print(value[i], end=' , ')
            else:
                print(value[i], end='\n')

    elif node.getdata() == '[SENTENCE]':
        if len(node.getchildren()) == 1:
            value = [node.getchild(0).getvalue()]
        else:
            value = [node.getchild(0).getvalue()] + node.getchild(2).getvalue()
        node.setvalue(value)

    elif node.getdata() == '[WORD]':
        if type(node.getchild(0).getvalue()) == (int or float):
            node.setvalue(node.getchild(0).getvalue())
        else:
            value = v_table[node.getchild(0).getdata()]
        node.setvalue(value)
        update_v_table(node.getchild(0).getdata(), value)
