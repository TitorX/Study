#!/bin/python2
# coding=utf-8

"""
    The code calls the dynamic link library implemented by C language.
    The code is used to judge whether the symbol in text is balanced.
"""

import ctypes

lib = ctypes.cdll.LoadLibrary('./balance_symbol.so')

with open('test_text.txt') as f:
    texts = f.readlines()

for line in range(len(texts)):
    if lib.balance_symbol(texts[line]):
        print('Line: %d. Symbol is balanced!' % (line + 1))
    else:
        print('Line: %d. Symbol is not balanced!' % (line + 1))
