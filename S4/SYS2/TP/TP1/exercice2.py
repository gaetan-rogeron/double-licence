#!/usr/bin/env python3
import os

dic = os.environ
for c in dic:
    print(f"{c} : {dic[c]}")

