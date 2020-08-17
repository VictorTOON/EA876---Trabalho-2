import json
import os

txt = ''
while True:
    try :
        txt += input() + '\n'
    except EOFError:
        break

json_dict = json.loads(txt)

for key in json_dict:
    os.system("echo 'doc/imgs/{}\ndoc/imgs/{}\n' | python3 plot-graph.py {}".format(json_dict[key].replace(".png","-1.png"),  json_dict[key].replace(".png","-2.png"), "logs/"+key ))


