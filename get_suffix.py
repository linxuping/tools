#!/usr/bin/env python
ret = set()
import os
for path, dirs, files in os.walk("./"):
  for f in files:
    tmps = f.rsplit(".")
    if len(tmps) == 2:
      ret.add(tmps[1])
print ret
