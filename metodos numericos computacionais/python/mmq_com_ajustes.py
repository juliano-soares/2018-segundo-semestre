# -*- coding: utf-8 -*-
"""
Created on Wed Nov 28 17:56:21 2018

@author: Juliano
"""

clear;
clc;
format long;

% Entrada
x = input('- Digite o vetor x: ');
y = input('- Digite o vetor y: ');
n = length(x);

% Diagrama de dispersao
%plot(x, y, 'r*');

% Switch case do metodo
fprintf('- Escolha um metodo.\n');
fprintf('1) Polinomio\n');
fprintf('2) Hiperbolico\n');
fprintf('3) Exponencial de base e\n');
fprintf('4) Exponencial de uma base qualquer\n');
fprintf('5) Curva Geometrica\n');
metodo = input('- Selecione o metodo desejado: ');

m = 1;
switch (metodo)
    case 1
        m = input('- Escolha o grau do polinomio: ');
    case 2
        y = 1 ./ y;
    case 3
        y = log(y);
    case 4
        y = log(y);
    case 5
        x = log(x);
        y = log(y);
end

% Inicio
A = zeros(m+1, m+1);
b = zeros(m+1, 1);

% Construcao da matriz A e do vetor b
for i = 1:(m+1)
    for j = 1:(m+1)
        A(i,j) = sum(x.^(2*m-i-j+2));
    end
    b(i) = sum(y.*(x.^(m-i+1)));
end

% Resolucao do sistema
result = gauss(A,b);

% Construcao do polinomio
cef = num2str(result');
switch (metodo)
    case 1
        p = ['(' cef(1,:) ') * x^' num2str(m)];
        for i = 2:(m+1)
            p = [p ' + (' cef(i,:) ') * x^' num2str(m+1-i)];
        end
    case 2
        p = ['1 / (' cef(1,:) ' * x + ' cef(2,:) ')'];
    case 3
        p = [cef(2,:) ' * exp(' cef(1,:) ' * x)'];
    case 4
        p = [cef(2,:) ' * ' cef(1,:) '^x'];
    case 5
        p = [cef(2,:) ' * x^' cef(1,:)];
end

fprintf('\n - O polinomio (pelo metodo %d) eh:\n', metodo);
disp(p);

% Erro
erro = 0;
for i = 1:n
	erro = erro + (subs(str2sym(p), x(i)) - y(i))^2;
end
erro = sqrt(erro);

fprintf('\n - O erro eh ');
disp(erro);

% Grafico
hold on;
fplot(str2sym(p), [min(x),max(x)]);
plot(x, y, 'ro');
grid on;
hold off;

% --- Funcoes auxiliares ---
function result = gauss(A,b)
    [n m] = size(A);
    matriz = [A b];

    % Metodo de Eliminacao de Gauss
    for i = 1:n-1
        for j = i+1:n
            % se pivo for zero, permuta (com o maior)
            if (matriz(i,i) == 0)
                maior = 0;
                for k = i+1:n
                    if (matriz(k,i) ~= 0 & (maior == 0 | k > maior))
                        maior = k;
                    end
                end

                if (maior == 0)
                    fprintf(' - Todos valores das colunas restantes sao iguais a zeros.\n')
                    fprintf(' - Nao foi possivel encontrar a solucao.\n');
                    return;
                else
                    matriz([i maior],:) = matriz([maior i],:);
                end
            end

            mul(j,i) = matriz(j,i) / matriz(i,i);
            matriz(j,:) = matriz(j,:) - mul(j,i) * matriz(i,:);
        end
    end

    % Sistema triangular
    x(n) = matriz(n,n+1) / matriz(n,n);
    for i = n-1:-1:1
        soma = 0;
        for j = i+1:n
            soma = soma + matriz(i,j) * x(j);
        end
        x(i) = (matriz(i,n+1) - soma) / matriz(i,i);
    end
    result = x;
end