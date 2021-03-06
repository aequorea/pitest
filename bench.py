#!/usr/bin/python
#
# bench.py -- benchmark insertion sort
#

import os

cc = "gcc"

def do_cmd(cmd):
    val = os.system(cmd)
    if val == 0:
        return
    print("\nCommand Failed !!")
    exit()

do_cmd("lscpu | grep \"Model name:\" | \
        sed \"s/Model name:          //\"")
do_cmd(cc +" --version | grep \"" + cc +"\"")
do_cmd(cc + " -O3 -o pitest pitest.c")
do_cmd("./pitest")
