import matplotlib.pyplot as plt
import numpy as np
import re
from sys import argv

with open(argv[1], 'r') as f:
    txt = f.read()
linear, thread, process = [], [], []
for line in txt.split('\n'):
    if 'thread' in line:
        thread.append(float(re.findall(r'\d+[.]\d+', line)[0]))
    elif 'process' in line:
        process.append(float(re.findall(r'\d+[.]\d+', line)[0]))
    elif 'linear' in line:
        linear.append(float(re.findall(r'\d+[.]\d+', line)[0]))
linear = np.asarray(linear)
thread = np.asarray(thread)
process = np.asarray(process)
plt.ylabel("tempo")
plt.xlabel("execução")
plt.plot(linear,label='linear')
plt.plot(thread,label='thread')
plt.plot(process,label='process')
plt.legend()
plt.show()
plt.hist(thread,label='thread')
plt.hist(linear, label='linear')
plt.hist(process, label='process')
plt.legend()
plt.show()
