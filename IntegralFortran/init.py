fname = "analysis.txt"
f = open(fname, "w")
f.close()



import os

n = 10**7
f = open("n", "w")
f.write(str(n))
f.close()


for i in range(1, 13):
    quary = 'mpirun -np ' + str(i) + ' ./3d '
    quary += '< n'
    quary += ' >> ' + fname
    print(quary)
    os.system(quary)
    
with open(fname, "r+") as f:
    lines = f.readlines()
    f.seek(0)
    f.truncate()
    for i in range(12):
        line = lines[i]
        line = line.split()[-1]
        f.write(str(i+1) + '\t' + line + '\n')


        