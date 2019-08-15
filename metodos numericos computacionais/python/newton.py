# -*- coding: utf-8 -*-
"""
MÉTODO DE NEWTON
@author: juliano leonardo soares
"""
import matplotlib.pyplot as plt
from sympy import * 


x = Symbol('x');
f = input('Digite a funcao:');

xi = input('digite o ponto inicial: ');
p = input('Digite a precisao: ');
n = input('Digite o numero maximo de execucoes: ');
 
erro = 1;
nexe = 0;
xa = 0;
flagerro = 0;

while(erro > p and nexe < n):
    fx = f.evalf(subs = {x: xi});
    fd =  f.diff(x);
    print fd;
    fdxi = fd.evalf(subs = {x: xi});
    if(not(flagerro)):
        x2 = xi - (fx/fdxi);
        if(abs(fdxi) >= p):
            fdx0 = fdxi;
        else:
            print('O metodo de newton falhou.\n');
            flagerro = 1;
            pause();
    if(flagerro):
        x2 = xi - (fx/fdx0);
        dfx2 = fd.evalf(subs = {x: x2});
        if(abs(dfx2) >= p):
            flagerro = 0;
    fx2 = f.evalf(subs = {x:x2});
    print('xi= %2.5f', xi,' | fx= %2.5f',fx, '| fdx = %2.5f',fdxi, '-- abs(fx) = %2.5f', abs(fx), '| abs(fdx) = %2.5f',abs(fdxi), '| x2 = %2.5f', x2, '-- fx2 = %2.5f\n', fx2);
    if(abs(fx2) < p):
        print('O metodo convergiu pela imagem e a solucao e: %2.5f\n', x2);
        break; 
    if(erro < p and abs(fx2) >= p):
        print('O metodo convergiu pelo dominio e a solucao e: %2.5f\n', xi);
        break; 
    elif(nexe >= n):
        disp('O metodo atingiu o numero maximo de execucoes');
        break; 
    "funcao f:"   
    "plot(f,(xi,fx));"
    
    p1 = plot(f);
    xGR = [xi,xi,x2];
    yGR = [0,fx,0];
    e1 = [xi,x2];
    e2 = [fx,0];
    p2 = plt.plot(xGR,yGR,'.');
    p3 = plt.plot(e1,e2);
    p1.extend(p2);
    p1.extend(p3);
     
    erro = abs(x2-xi)/abs(x2);
    xi = x2;
    nexe = nexe + 1;
   

