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
linear_avg,linear_std  = linear.mean(), linear.std()
thread_avg,thread_std  = thread.mean(), thread.std()
process_avg,process_std  = process.mean(), process.std()

plt.ylabel("tempo")
plt.xlabel("execução")
plt.plot(linear,label='linear: {:.3f} ± {:.3f}'.format(linear_avg,linear_std))
plt.plot(thread,label='thread: {:.3f} ± {:.3f}'.format(thread_avg,thread_std))
plt.plot(process,label='process: {:.3f} ± {:.3f}'.format(process_avg,process_std))
plt.legend()
plt.show()
plt.hist(linear,label='linear: {:.3f} ± {:.3f}'.format(linear_avg,linear_std))
plt.hist(thread,label='thread: {:.3f} ± {:.3f}'.format(thread_avg,thread_std))
plt.hist(process,label='process: {:.3f} ± {:.3f}'.format(process_avg,process_std))
plt.legend()
plt.show()
