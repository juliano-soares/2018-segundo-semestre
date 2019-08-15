# -*- coding: utf-8 -*-
"""
METODO DA BISSECAO
@author: juliano leonardo soares
"""
" Método da bisseção "
import matplotlib.pyplot as plt
from sympy import *

" Recebe a função"
x = Symbol('x');
f = input('Digite a funcao:');

df = f.diff(x);

fab = 10;
dab = -5;

while (fab>0 or dab<0):
    " Recebe os intervalos"
    a = input('Informe o intervalo inferior:, a=');
    b = input('Informe o intervalo superior, b=');
    fa = f.evalf(subs = {x: a});
    fb = f.evalf(subs = {x: b});
    da = df.evalf(subs = {x: a});
    db = df.evalf(subs = {x: b});   
    fab = fa*fb;
    dab = da*db;

" Começando o método da Bisseção"
" Recebe a precisão"
Prec = input ('entre com a precisão, E=');
" Recebe o n° máximo de iterações desejada"
Max = input ('entre com o numero de iterações, MAX=');

y = 10;" valor para poder entrar no while"
n_iter = 0;
I = 1;
print('   intervalos A B     | função em A  | função em B | ponto médio | erro precisão | Nº iterações \n');
while (abs(y) > Prec and I <= Max):
    x1 = (a+b)/2;
    y = f.evalf(subs = {x: x1});
    n_iter = n_iter+1;
    
    p1 = plot(f);
    p2 = plt.plot(a,0,'.');
    p3 = plt.plot(b,0,'.');    
    print('A= %2.5f B= %2.5f | Fa= %2.5f | FB= %2.5f | X1= %2.5f | ERRO= %2.5f | Iter= %f\n',a,b,fa,fb,x1,y,n_iter);
    pause;
    
    if (fa * y < 0):
        b = x1;
        fb = y;
    else:
        a = x1;
        fa = y;
    I = I + 1;  
    
if (I > Max):
    print('O numero maximo de iterações atingido!!!!\n');    
print('A raiz obtida é: %2.5f \n',x1);
