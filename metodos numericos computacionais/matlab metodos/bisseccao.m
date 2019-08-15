% MÉTODO DA BISSEÇÃO

clc;                                                                       
clear;
syms x;

% Recebe a função
sf = input('Digite a funcao: ', 's');
fx = str2sym(sf);
df = diff(fx);

fab = 10;
dab = -5;
while fab>0 | dab<0
    % Recebe os intervalos
    a = input('Informe o intervalo inferior:, a=');
    b = input('Informe o intervalo superior, b=');
    fa = subs(fx,a);
    fb = subs(fx,b);
    da = subs(df,a);
    db = subs(df,b);    
    fab = fa*fb;
    dab = da*db;
end

% Começando o método da Bisseção
% Recebe a precisão
Prec = input ('entre com a precisão, E=');
% Recebe o n° máximo de iterações desejada
Max = input ('entre com o numero de iterações, MAX=');

y = 10;%valor para poder entrar no while
n_iter = 0;
I = 1;
fprintf('   intervalos A B     | função em A  | função em B | ponto médio | erro precisão | Nº iterações \n');
while abs(y) > Prec && I <= Max
    x1 = (a+b)/2;
    y = subs(fx,x1);
    n_iter = n_iter+1;
    plot(a,0,'.');
    xlim([a,b]);
    hold on;
    plot(b,0,'.');
    zoom(1);
    fplot(fx);
    grid on;
    title ('Gráficos - Bisseção');
    xlabel ('eixo X');
    ylabel ('eixo Y');
    
    fprintf('A= %2.5f B= %2.5f | Fa= %2.5f | FB= %2.5f | X1= %2.5f | ERRO= %2.5f | Iter= %f\n',a,b,fa,fb,x1,y,n_iter);
    pause;
    
    if fa * y < 0
        b = x1;
        fb = y;
    else
        a = x1;
        fa = y;
    end
    I = I + 1;  
end

if I > Max
    fprintf('O numero maximo de iterações atingido!!!!\n');
end    
fprintf('A raiz obtida é: %2.5f \n',x1);



