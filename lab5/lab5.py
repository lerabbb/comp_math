import matplotlib.pyplot as plt
import numpy as np

LEFT = 0
RIGHT = 1
N = 1000
h = (RIGHT-LEFT)/N

A = [0] * (N+1)
f = [0] * (N+1)
alpha = [0] * (N+1)
beta = [0] * (N+1)
u = [0] * (N+1)
exactSol = [0]*(N+1)
x = [LEFT + j*h for j in range(0,N+1)]

for i in range(0,N+1):
    A[i] = [0] * (N+1)
    exactSol[i] = -x[i]*x[i] + x[i]

A[0][0] = 1; A[N][N] = 1
f[0] = 0; f[N] = 0

for i in range (1, N):
    f[i] = -2 * h * h
    for j in range (0, N+1):
        if j == i:
            A[i][j-1] = 1
            A[i][j] = -2
            A[i][j+1] = 1

alpha[0] = - A[0][1] / A[0][0]
beta[0] = f[0] / A[0][0]
for i in range (1, N):
    alpha[i] = -A[i][i+1] / (A[i][i] + A[i][i-1] * alpha[i-1])
    beta[i] = (f[i] - A[i][i-1] * beta[i-1]) / (A[i][i] + A[i][i-1] * alpha[i-1])

beta[N] = (f[N] - A[N][N-1] * beta[N-1]) / (A[N][N] + A[N][N-1] * alpha[N-1])

u[N] = beta[N]
for i in range(1, N+1):
    u[N-i] = alpha[N-i] * u[N-i+1] + beta[N-i]

fig, ax = plt.subplots()
plt.plot(x, exactSol, 'deeppink')
plt.show()