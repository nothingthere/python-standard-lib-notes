#!/usr/bin/python3
# Author: Claudio <3261958605@qq.com>
# Created: 2017-05-03 18:29:29
# Commentary:
# Code:
import argparse

parser = argparse.ArgumentParser(description='处理整数。')

parser.add_argument('integers', metavar='N', type=int, nargs='+',
                    help='用于加法的整数')
parser.add_argument('--sum', dest='accumulate', action='store_const',
                    const=sum, default=max,
                    help='整数相加（默认：找到最大值）')

args = parser.parse_args()
print(args.accumulate(args.integers))
