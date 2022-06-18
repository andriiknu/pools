f = open("analysis.txt", "w")
f.close()

import os

n = 10**7

for i in range(1, 13):
    command = 'mpirun -np ' + str(i) + ' ./build/mpi ' + str(n)
    print(command)
    os.system(command)

