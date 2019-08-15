% Método da Falsa Posicao 

clear;
clc;
syms x;
sf = input('Digite a funcao: ', 's');
f = str2sym(sf);
x0 = input('Informe o intervalo inferior:'); 
x1 = input('Informe o intervalo superior:'); 
erro = input('Informe o erro maximo:'); 
n = input('Informe o numero de iteracoes maxima: '); 
k=0; 
fx0 = subs(f,x0);
fx1 = subs(f,x1);
x=(x1*fx0-x0*fx1)/(fx0-fx1); 
fx = subs(f,x);
while (abs(fx) >= erro && k <= n)
    fx = subs(f,x);
    fx0 = subs(f,x0);
    fx1 = subs(f,x1);
    if (fx1*fx)<0 
       x0=x; 
    else
       x1=x;  
    end
    x = (x1*fx-x0*fx1)/(fx-fx1); 
    fprintf('x0= %2.5f | x1= %2.5f | x2 = %2.5f | fx0 = %2.5f  | fx1 =  %2.5f | nexe = %f \n', x0,x1,x,fx0,fx1,k);
    fprintf('raiz x = %2.5f | f(x) = %2.5f | |B - A| = %2.5f \n',x,fx,abs(x0-x1));

    % função f:
    grid on;
    hold on;
    fplot(f);
    % ponto na função (x0,f(xo))
    plot(x0,fx0,'o');
    % ponto no eixo X = x0
    plot(x0,0,'o');
    % ponto na função (x1,f(x1))
    plot(x1,fx1,'o');
    % ponto no eixo X = x0
    plot(x1,0,'o');
    % ponto medio
    plot(x,0,'*');
    % linha de x1 a x0
    plot([x1,x0],[fx1,fx0]);
    
    pause(); 
    k = k+1;
end
fprintf('x = %2.5f | f(x) = %2.5f | |b-a| = %2.5f \n',x,fx,abs(x0-x1));