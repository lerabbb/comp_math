import matplotlib.pyplot as plt
import numpy as np
import csv

LEFT = -10
RIGHT = 10
T = 1
A = 5
N = 1000
h = (RIGHT-LEFT)/N
r = 1.25
tau = r * h / A
M = int(T / tau + 1)
N = N+1

u = [0] * M
exactSol = [0]*N
x = [LEFT + j*h for j in range(0,N)]

fig, ax = plt.subplots()

for n in range(0, M):
    u[n] = [0] * N
    u[n][0] = 3
    exactSol[0] = 3
    for j in range(1, N):
        if(n == 0):
            u[n][j] = 3 if x[j] <= 0 else 1
        else:
            u[n][j] = u[n-1][j] * (1-r) + r * u[n-1][j-1]
        
        exactSol[j] = 3 if x[j] <= 0 else 1

plt.plot(x, u[M-1], 'g')
for j in range(0, N):
    exactSol[j] = 3 if x[j] <= A*T else 1
plt.plot(x, exactSol, 'deeppink')
plt.show()