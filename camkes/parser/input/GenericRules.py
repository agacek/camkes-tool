#
# Copyright 2014, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

'''Common parsing rules relevant for all grammars. See accompanying docs for
more information.'''

from camkes.ast import Import, Include
from .. import Exceptions

def p_import_statement(t):
    '''import_statement : relative_import_statement
                        | builtin_import_statement'''
    t[0] = t[1]

def p_relative_import_statement(t):
    '''relative_import_statement : import STRING SEMI'''
    t[0] = Import(t[2], relative=True, filename=t.lexer.filename, \
        lineno=t.lexer.lineno)

def p_builtin_import_statement(t):
    '''builtin_import_statement : import ANGLE_STRING SEMI'''
    t[0] = Import(t[2], relative=False, filename=t.lexer.filename, \
        lineno=t.lexer.lineno)

def p_include_statement(t):
    '''include_statement : relative_include_statement
                         | builtin_include_statement'''
    t[0] = t[1]

def p_relative_include_statement(t):
    '''relative_include_statement : include STRING SEMI'''
    t[0] = Include(t[2], relative=True, filename=t.lexer.filename, \
        lineno=t.lexer.lineno)

def p_builtin_include_statement(t):
    '''builtin_include_statement : include ANGLE_STRING SEMI'''
    t[0] = Include(t[2], relative=False, filename=t.lexer.filename, \
        lineno=t.lexer.lineno)

def p_list(t):
    '''list : LSQUARE list_contents RSQUARE'''
    t[0] = t[2]

def p_list_contents(t):
    '''list_contents :
                     | container_element
                     | container_element COMMA list_contents'''
    if len(t) == 1:
        t[0] = []
    elif len(t) == 2:
        t[0] = [t[1]]
    else:
        assert len(t) == 4
        t[0] = [t[1]] + t[3]

def p_container_element(t):
    '''container_element : NUMBER
                         | DECIMAL
                         | STRING
                         | list
                         | dict'''
    t[0] = t[1]

def p_dict(t):
    '''dict : LBRACE dict_contents RBRACE'''
    t[0] = t[2]

def p_dict_contents(t):
    '''dict_contents :
                     | dict_key COLON container_element
                     | dict_key COLON container_element COMMA dict_contents'''
    if len(t) == 1:
        t[0] = {}
    elif len(t) == 4:
        t[0] = {t[1]:t[3]}
    else:
        assert len(t) == 6
        t[0] = dict([(t[1], t[3])] + t[5].items())

def p_dict_key(t):
    '''dict_key : NUMBER
                | DECIMAL
                | STRING'''
    t[0] = t[1]

def p_error(t):
    raise Exceptions.CAmkESSyntaxError(t)
