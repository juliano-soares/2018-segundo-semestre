% Metodo da falsa posi��o
clc                                                                         
clear
syms x
fx=input('Entre com a fun��o, fx=')
df=diff(fx);
fab=10;
dab=-5;
while fab>0 |  dab<0
    a=input('entre com o valor de a, a=')
    b=input ('entre com o valor de b, b=')
    fa=subs(fx,a);
    fb=subs (fx,b);
    da=subs(df,a);
    db=subs(df,b);
    fab=fa*fb;
    dab=da*db;
end
%come�ando o m�todo da Bisse��o
E = input ('entre com a precis�o, E=')
max = input ('entre com o numero de itera��es, MAX=')
y = 10;
k = 0;
I = 1;
while abs(y)>E && I < max
    x1=(a+b)/2
    y=subs(fx,x1)
    k=k+1;
    if fa*y<0
    b=x1
    fb=y
    else
        a=x1;
        fa=y;
    end
    I=I+1;
end
disp ('O numero de intera��o �:')
k
disp('A raiz �:')
x1
disp ('o erro �:')
y