fname = "time"
f = open(fname, "w")
f.close()

import os

for i in range(1, 13):
    quary = './a.out -t ' + str(i) +' >> ' + fname
    print(quary)
    os.system(quary)

    
