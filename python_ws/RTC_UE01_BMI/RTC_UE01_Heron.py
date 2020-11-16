#!/usr/bin/env python3
# RTC_UE01_Heron.py
# Gerald Hebinck 09th Nov 2020

def w(n, x):
    if (n == 0):
        return 1
    else:
        return 0.5 * (w(n-1, x) + (x / (w(n-1, x))))


print(w(10, 25))
