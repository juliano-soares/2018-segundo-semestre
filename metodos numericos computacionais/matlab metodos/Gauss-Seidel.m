% MÉTODO DE GAUSS SEIDEL
clc;                                                                       
clear;
% ENTRADAS
%recebe a ordem do sistema
ord = input('Ordem da matriz:');
%recebe a matriz dos coeficientes
A = input('matriz dos coeficientes:');
%recebe o vetor x inicial
X = input('Entre com o vetor X inicial:');
%recebe o vetor dos termos independentes B
B = input('Entre com o vetor b:');
%recebe o erro pre-estabelecido
tol = input('Entre com a tolerancia:');
%recebe o numero maximo de iteracoes
max = input('Entre com o numero maximo de iteracoes:');

%Processamento
k = 1;
for i=1:ord
    for j = 1:ord
        if i == j
            D(i,j) = 0;
            I(i,1) = B(i,1)/A(i,i);
        else
            D(i,j) = -A(i,j)/A(i,i);
        end
    end
end

while(k < max)
    X1 = X;
    for i = 1:ord
        X1(i,1) = D(i,:)*X1 + I(i,1);
    end
    for i = 1:ord
        ERX(i,1)= abs((X1(i,1)-X(i,1))/X1(i,1))*100;
        mtol(i,1)=tol;
    end
    if ERX < mtol
        fprintf('%1.5f\n',X1);
        break
    end
    X = X1;
    k = k+1;
end

if k == max
    fprintf('O numero maximo de iteracoes estourado');
end
