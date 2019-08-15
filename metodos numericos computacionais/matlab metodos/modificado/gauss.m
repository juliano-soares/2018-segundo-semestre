% Metodo de Eliminacao de Gauss
% por juliano leonardo soares


% Limpeza
clear;
clc;
format short;

% Entrada
A = input('Digite a matriz A: ');
b = input('Digite o vetor b: ');

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

% Saida
fprintf('\n - Vetor solucao\n');
for i = 1:n
    fprintf(' x(%d) = %f\n', i, x(i));
end
