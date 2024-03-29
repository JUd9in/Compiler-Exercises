
# parsetab.py
# This file is automatically generated. Do not edit.
# pylint: disable=W,C,R
_tabversion = '3.10'

_lr_method = 'LALR'

_lr_signature = "NUMBER PRINT VARIABLEprogram : statementsstatements : statements statement\n                  | statement statement : assignment\n                  | operation\n                  | printassignment : VARIABLE '=' NUMBERoperation : VARIABLE '=' expressionexpression : expression '+' term\n                  | expression '-' term\n                  | term term : term '*' factor\n             | term '/' factor\n             | factorfactor : VARIABLE\n              | '(' expression ')'\n              | NUMBERprint : PRINT '(' sentence ')' sentence : word ',' sentence\n                | wordword : NUMBER\n            | VARIABLE"
    
_lr_action_items = {'VARIABLE':([0,2,3,4,5,6,9,10,11,12,13,14,15,16,17,22,23,24,25,27,28,29,30,31,32,33,34,],[7,7,-3,-4,-5,-6,-2,12,21,-15,-7,-8,-11,-14,12,12,12,12,12,-17,-18,21,-9,-10,-12,-13,-16,]),'PRINT':([0,2,3,4,5,6,9,12,13,14,15,16,27,28,30,31,32,33,34,],[8,8,-3,-4,-5,-6,-2,-15,-7,-8,-11,-14,-17,-18,-9,-10,-12,-13,-16,]),'$end':([1,2,3,4,5,6,9,12,13,14,15,16,27,28,30,31,32,33,34,],[0,-1,-3,-4,-5,-6,-2,-15,-7,-8,-11,-14,-17,-18,-9,-10,-12,-13,-16,]),'=':([7,],[10,]),'(':([8,10,17,22,23,24,25,],[11,17,17,17,17,17,17,]),'NUMBER':([10,11,17,22,23,24,25,29,],[13,20,27,27,27,27,27,20,]),'*':([12,13,15,16,27,30,31,32,33,34,],[-15,-17,24,-14,-17,24,24,-12,-13,-16,]),'/':([12,13,15,16,27,30,31,32,33,34,],[-15,-17,25,-14,-17,25,25,-12,-13,-16,]),'+':([12,13,14,15,16,26,27,30,31,32,33,34,],[-15,-17,22,-11,-14,22,-17,-9,-10,-12,-13,-16,]),'-':([12,13,14,15,16,26,27,30,31,32,33,34,],[-15,-17,23,-11,-14,23,-17,-9,-10,-12,-13,-16,]),')':([12,15,16,18,19,20,21,26,27,30,31,32,33,34,35,],[-15,-11,-14,28,-20,-21,-22,34,-17,-9,-10,-12,-13,-16,-19,]),',':([19,20,21,],[29,-21,-22,]),}

_lr_action = {}
for _k, _v in _lr_action_items.items():
   for _x,_y in zip(_v[0],_v[1]):
      if not _x in _lr_action:  _lr_action[_x] = {}
      _lr_action[_x][_k] = _y
del _lr_action_items

_lr_goto_items = {'program':([0,],[1,]),'statements':([0,],[2,]),'statement':([0,2,],[3,9,]),'assignment':([0,2,],[4,4,]),'operation':([0,2,],[5,5,]),'print':([0,2,],[6,6,]),'expression':([10,17,],[14,26,]),'term':([10,17,22,23,],[15,15,30,31,]),'factor':([10,17,22,23,24,25,],[16,16,16,16,32,33,]),'sentence':([11,29,],[18,35,]),'word':([11,29,],[19,19,]),}

_lr_goto = {}
for _k, _v in _lr_goto_items.items():
   for _x, _y in zip(_v[0], _v[1]):
       if not _x in _lr_goto: _lr_goto[_x] = {}
       _lr_goto[_x][_k] = _y
del _lr_goto_items
_lr_productions = [
  ("S' -> program","S'",1,None,None,None),
  ('program -> statements','program',1,'p_program','py_yacc.py',18),
  ('statements -> statements statement','statements',2,'p_statements','py_yacc.py',25),
  ('statements -> statement','statements',1,'p_statements','py_yacc.py',26),
  ('statement -> assignment','statement',1,'p_statement','py_yacc.py',37),
  ('statement -> operation','statement',1,'p_statement','py_yacc.py',38),
  ('statement -> print','statement',1,'p_statement','py_yacc.py',39),
  ('assignment -> VARIABLE = NUMBER','assignment',3,'p_assignment','py_yacc.py',46),
  ('operation -> VARIABLE = expression','operation',3,'p_operation','py_yacc.py',56),
  ('expression -> expression + term','expression',3,'p_expression','py_yacc.py',65),
  ('expression -> expression - term','expression',3,'p_expression','py_yacc.py',66),
  ('expression -> term','expression',1,'p_expression','py_yacc.py',67),
  ('term -> term * factor','term',3,'p_term','py_yacc.py',79),
  ('term -> term / factor','term',3,'p_term','py_yacc.py',80),
  ('term -> factor','term',1,'p_term','py_yacc.py',81),
  ('factor -> VARIABLE','factor',1,'p_factor','py_yacc.py',93),
  ('factor -> ( expression )','factor',3,'p_factor','py_yacc.py',94),
  ('factor -> NUMBER','factor',1,'p_factor','py_yacc.py',95),
  ('print -> PRINT ( sentence )','print',4,'p_print','py_yacc.py',112),
  ('sentence -> word , sentence','sentence',3,'p_sentence','py_yacc.py',121),
  ('sentence -> word','sentence',1,'p_sentence','py_yacc.py',122),
  ('word -> NUMBER','word',1,'p_word','py_yacc.py',133),
  ('word -> VARIABLE','word',1,'p_word','py_yacc.py',134),
]
