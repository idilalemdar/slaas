#!/usr/bin/env python3

from subprocess import Popen
import time

EXPERIMENT_COUNT = 500

for i in range(EXPERIMENT_COUNT):
    args = ["./main", str(i), "0.3", "0.3", "2", "1"]
    p = Popen(args)
    p.wait()
    time.sleep(1)
