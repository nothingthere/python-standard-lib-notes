#!/usr/bin/python3
# Author: Claudio <3261958605@qq.com>
# Created: 2017-04-29 20:15:46
# Commentary:

# 使用difflib实现的类diff命令，提供下面4种格式：
# * ndiff： 列出每行，并高亮行内区别
# * context：结合上下文高亮修改，使用“前/后”格式。
# * unified：结合上下文高亮修改，使用inline个数。
# * html：生成将比较结果生成HTML表格。

# Code:

import argparse
import difflib
import os
import sys
import time
from datetime import datetime, timezone


def file_mtime(path):
    t = datetime.fromtimestamp(os.stat(path).st_mtime, timezone.utc)
    return t.astimezone().isoformat()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', action='store_true', default=True,
                        help='Produce a context format diff (default)')
    parser.add_argument('-u', action='store_true',
                        default=False, help='Produce a unified format diff')
    parser.add_argument('-m', action='store_true', default=False,
                        help='Produce HTML side by side diff '
                        '(can use -c and -l in conjunction)')
    parser.add_argument('-n', action='store_true',
                        default=False, help='Produce a ndiff format diff')
    parser.add_argument('-l', '--lines', type=int, default=3,
                        help='Set number of context lines (default 3)')
    parser.add_argument('fromfile')
    parser.add_argument('tofile')
    options = parser.parse_args()

    n = options.lines
    fromfile = options.fromfile
    tofile = options.tofile

    fromdate = file_mtime(fromfile)
    todate = file_mtime(tofile)

    with open(fromfile) as ff:
        fromlines = ff.readlines()
    with open(tofile) as tf:
        tolines = tf.readlines()

    if options.u:
        diff = difflib.unified_diff(fromlines, tolines, fromdate, todate, n=n)
    elif options.n:
        diff = difflib.ndiff(fromlines, tolines)
    elif options.m:
        diff = difflib.HtmlDiff().make_file(fromlines, tolines, fromfile,
                                            tofile, context=options.c, numlines=n)
    else:
        diff = difflib.context_diff(
            fromlines, tolines, fromfile, tofile, fromdate, todate, n=n)

    sys.stdout.writelines(diff)
    # print(diff)


if __name__ == '__main__':
    main()
