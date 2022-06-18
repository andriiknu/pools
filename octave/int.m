clc, clear

pkg load symbolic
syms x
f = (x^3 + x)/(x^4 + 1)
I = int(f, x, 0, 1)

output_precision(16)
double(I)