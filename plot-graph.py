# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import numpy as np
import re
from sys import argv
import matplotlib.backends.backend_pdf
if len(argv) > 1:
    with open(argv[1], 'r') as f:
        txt = f.read()
else:
    txt = ''
    while True:
        try:
            txt += input() + '\n'
        except EOFError:
            break
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

pdf = matplotlib.backends.backend_pdf.PdfPages("output.pdf")

fig = plt.figure()

plt.hist(linear,label='linear')
plt.hist(thread,label='thread')
plt.hist(process,label='process')
plt.legend()

pdf.savefig(fig,bbox_inches = 'tight') 

fig, (ax1, ax2) = plt.subplots(2) 
ax1.set_ylabel("Tempo (em segundos) ")
ax1.set_xlabel("Execuções feitas")
ax1.plot(linear,label='linear')# {:.3f} ± {:.3f}'.format(linear_avg,linear_std))
ax1.plot(thread,label='thread')# {:.3f} ± {:.3f}'.format(thread_avg,thread_std))
ax1.plot(process,label='process')# {:.3f} ± {:.3f}'.format(process_avg,process_std))
ax1.legend()
#plt.show()
#ax = plt.gca()
ax2.get_xaxis().set_visible(False)
ax2.get_yaxis().set_visible(False)
#ax2.box(on=None)
table = np.array([
    [thread_avg, thread_std],
    [process_avg, process_std],
    [linear_avg, linear_std],
    ])
table = list(map(lambda x: '{:.3f} {:.3f}'.format(*x).split(), table))
the_table = ax2.table(cellText=table,
                      cellLoc="center", 
                      rowLabels=["thread", "process","linear"],
                      colLabels=["Média (em segundos) ", "Desvio Padrão (em segundos)"],
                      loc='center')
the_table.scale(1, 1.3) 
ax2.axis("off")


pdf.savefig(fig,bbox_inches = 'tight') 

pdf.close()
