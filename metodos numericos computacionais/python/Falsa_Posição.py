"""
    Metodo da Falsa Posicao
    por Juliano Leonardo Soares
"""
from sympy import *

""" Limpeza """
clear;
clc;

""" Entrada """
f = str2sym(input('Digite a funcao: ', 's'));
a = input('Digite o valor inicial do intervalo: ');
b = input('Digite o valor final do intervalo: ');
while (subs(f, a) * subs(f, b) > 0):
    print(' - Intervalo invalido para o Teorema de Bolzano.\n');
    print(' - Entre com novos valores para o intervalo.\n');
    a = input('Digite o valor inicial do intervalo: ');
    b = input('Digite o valor final do intervalo: ');

nmax = input('Digite o numero maximo de iteracoes: ');
tol = input('Digite a tolerancia maxima desejada: ');

""" Verifica solucao nos extremos do intervalo """
if (subs(f, a) == 0):
    print('\n - Solucao exata encontrada no limite incial do intervalo: %f\n', a);
    return;
elif (subs(f, b) == 0):
    print('\n - Solucao exata encontrada no limite final do intervalo: %f\n', b);
    return;

""" Verifica intervalo invertido """
if (a > b):
    tmp = a;
    a = b;
    b = tmp;


""" Aqui f(a)*f(b) < 0, entao comeca o metodo """
intervalo = b - a;
cont = 1;

print('\n\n');
print('----------------------------------------------------------------------------------------------------------\n');
print(' Iteracao \t a \t\t\t f(a) \t\t b \t\t\t f(b) \t\t x \t\t f(x) \t\t tamanho do intervalo\n');
print('----------------------------------------------------------------------------------------------------------\n');

while (intervalo > tol and cont <= nmax):    
    fa = subs(f, a);
    fb = subs(f, b);
    x = (a*double(fb) - b*double(fa))/(double(fb) - double(fa));
    fx = subs(f, x);
  
    printf(' %2d \t\t %5.4f \t %5.4f \t %5.4f \t %5.4f \t %5.4f \t %5.4f \t %5.4f\n', cont, a, fa, b, fb, x, fx, intervalo);
    pause;
    
    if (abs(fx) < tol):
        print('\n - Solucao obtida pela imagem: %f\n', x);
        return;
    elif (fa * fx < 0):
        b = x;
    elif (fb * fx < 0):
        a = x;
    
    
    intervalo = b - a;
    cont = cont + 1;


""" Saida"""
x = (a*double(fb) - b*double(fa))/(double(fb) - double(fa));
print('\n - A solucao foi obtida pelo dominio: %f\n', x);




