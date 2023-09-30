import time
dt = "1970-01-01"
ta = time.strptime(dt,"%Y-%m-%d")
print(ta)
ts = time.mktime(ta)
print(ts)
local_t = time.strftime("%Y-%m",ta)
print(local_t)
