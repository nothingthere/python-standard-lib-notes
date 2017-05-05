#!/usr/bin/python3
# Author: Claudio <3261958605@qq.com>
# Created: 2017-05-03 21:36:31
# Commentary:
# Code:
import argparse

parser = argparse.ArgumentParser(prog='argparse_demo_prog')
parser.add_argument('--foo', help='foo help of the %(prog)s program')
args = parser.parse_args()
