import ply.lex as lex

tokens = ["WORD", "STRING", "NUMBER", "QUOTE", "OBRACE", "EBRACE", 'PLUS',
          'MINUS',
          'EQUAL',
          'TIMES',
          'DIVIDE',
          'LPAREN',
          'RPAREN', "LESS", "MORE", "OUTPUT_SYM", "INPUT_SYM", "SEMICOLON"]
reserved = {  # 匹配保留字的正确方法，建立一个reserved字典
    'if': 'IF',
    'then': 'THEN',
    'else': 'ELSE',
    'while': 'WHILE',
    'int': 'INT',
    'cout': 'COUT',
    'endl': 'ENDL'
}
tokens = tokens + list(reserved.values())

t_PLUS = r'\+'  # +
t_MINUS = r'-'  # -
t_TIMES = r'\*'  # *
t_DIVIDE = r'/'  # /
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_OBRACE = r'\{'
t_EBRACE = r'\}'
t_EQUAL = r'\='
t_SEMICOLON = r'\;'
t_LESS = r'\<'
t_MORE = r'\>'
t_OUTPUT_SYM = r'\<<'
t_INPUT_SYM = r'\>>'
# t_STRING = r'(?<=")([a-zA-Z\s]+[\.])(?=")'


# precedence = (
#     ('WORD'),
#     ('STRING')
# )


def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)
    return t

# 通过设置函数的顺序显式地定义优先级！

def t_STRING(t):
    # r'\"[a-zA-Z](.*)\"'
    r'(?<=")([a-zA-Z\s]+[\.])(?=")'
    t.value = str(t.value)
    return t

def t_WORD(t):
    r'([a-zA-Z][a-zA-Z0-9-]*)'
    # t.value = str(t.value)
    t.type = reserved.get(t.value, 'WORD')
    return t

def t_QUOTE(t):
    r'"'
    t.value = str(t.value)
    return t


def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)


t_ignore = ' \t'


def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


lexer = lex.lex()


def read(path):
    of = open(path, "r")
    stri = of.read()
    of.close()
    return stri


s = read("prog.txt")
lexer.input(s)
while True:
    tok = lexer.token()
    if not tok: break
    print(tok)
