#!/usr/bin/python
#
# bench.py -- benchmark insertion sort
#

cc = "gcc"

import os

def prGreen(skk): print("\033[92m {}\033[00m" .format(skk)) 
def prYellow(skk): print("\033[93m {}\033[00m" .format(skk)) 

def do_cmd(cmd):
    val = os.system(cmd)
    if val == 0:
        return
    prYellow("\nCommand Failed !!")
    exit()

def show_cmd(cmd):
    prGreen("$ " + cmd)
    do_cmd(cmd)

def dolink(cmd):
    show_cmd(cmd)
    show_cmd("./pitest")

do_cmd("lscpu | grep \"Model name:\" | sed \"s/Model name:   /\"")
do_cmd(cc +" --version | grep \"" + cc +"\"")
dolink(cc + " -O3 -o pitest pitest.c")

