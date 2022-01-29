# coding=utf-8
import ply.yacc as yacc
from ExpLex import tokens


class Atom(object):
    def __init__(self, symbol, count):
        self.symbol = symbol
        self.count = count

    def __repr__(self):
        return "Atom(%r, %r)" % (self.symbol, self.count)


def p_op1(p):
    'species_list : species_list species'
    p[0] = p[1] + p[2]


def p_op2(p):
    'species_list : species'
    p[0] = p[1]


def p_op3(p):
    'species : SYMBOL'
    p[0] = 1


def p_op4(p):
    'species : SYMBOL SYMBOL_COUNT'
    p[0] = p[2]


def p_error(p):
    print("Syntax error in input!")


def atom_count(s: str) -> int:
    parser = yacc.yacc()
    result = parser.parse(s)
    return result


if __name__ == '__main__':
    string_list = ['He', 'H2', 'H2SO4', 'CH3COOH', 'NaCl', 'C60H60']
    for s in string_list:
        a1 = Atom(s, atom_count(s))
        print(a1)
        pass
