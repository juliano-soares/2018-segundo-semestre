% MÉTODO DA SECANTE 

clc;                                                                       
clear;
syms x;
sf = input('Digite a funcao: ', 's');
f = str2sym(sf);
x0 = input('Informe o intervalo inferior:'); 
x1 = input('Informe o intervalo superior:'); 
erro = input('Informe o erro maximo:'); 
n = input('Informe o numero de iteracoes maxima: '); 

fa = subs(f,x0);
fb = subs(f,x1);
nexe = 1;
while(abs(fa)>erro && nexe <= n)
    x2 = x0 - fa*(x1-x0)/(fb-fa);
    grid on;
    hold on;
    % função
    fplot(f);
    % pontos do eixo x: X0, X1, X2
    plot([x0,x0],[0,fa]);
    plot([x1,x1],[0,fb]);
    plot(x2,0,'o');
    % pontos na função f(x): f(x0), f(x1)
    plot(x0,fa,'o');
    plot(x1,fb,'o');
    % linha de x1,x0 a x2
    plot([x2,x1,x0],[0,fb,fa]);
    fprintf('x0= %2.5f | x1= %2.5f | x2 = %2.5f | fa = %2.5f  | fb =  %2.5f | nexe = %f \n', x0,x1,x2,fa,fb,nexe);
    pause();
    clf;
    x1 = x0;
    x0 = x2;
    fa = subs(f,x0);
    fb = subs(f,x1);
    nexe=nexe+1;
    
end
fprintf('A raiz é: %2.5f \n',x0);
close;