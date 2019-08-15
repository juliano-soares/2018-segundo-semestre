% Fatoracao LU
% por juliano leonardo soares

% Limpeza
clear;
clc;
format long;

% Entrada
U = input('Digite a matriz A: ');

n = size(U);
L = eye(n);

% Metodo LU
for i = 1:n
    if (U(i,i) == 0)
        for j = (i+1):n
            if (U(j,i) ~= 0)
                U([i j],:) = U([j i],:);
                break;
            end
        end
    end
    
    for j = i+1:n
        L(j,i) = U(j,i) / U(i,i);
        U(j,:) = U(j,:) - L(j,i) * U(i,:);
    end
end

% Saida
fprintf('\n - Matriz U:\n');
disp(U);
fprintf('\n - Matriz L:\n');
disp(L);
