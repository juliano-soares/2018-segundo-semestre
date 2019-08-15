% Metodo de Gauss-Seidel
% por juliano leonardo soares


% Limpeza
clear;
clc;
format long;

% Entrada
A = input('Digite a matriz A: ');
b = input('Digite o vetor b: ');
x0 = input('Digite o vetor inicial x0: ');
itmax = input('Digite o numero max de iteracoes: ');
tol = input('Digite a tolerancia: ');
fprintf('\n');

n = size(A);

% Construcao matriz C e vetor G

% ajustar diagonal para passar pelo teste
% de convergencia para casos com rand
%for i = 1:n
%    A(i,i) = 1000 * A(i,i);
%end

for i = 1:n
    for j = 1:n
        if (i == j)
            C(i,j) = 0;
        else
            C(i,j) = -A(i,j) / A(i,i);
        end
    end
    g(i) = b(i) / A(i,i);
end

% Teste de convergencia (Criterio de Sassenfeld)
beta(1) = sum(abs(C(1,2:n)));
for i = 2:n
    soma1 = 0;
    for j = 1:(i-1)
        soma1 = soma1 + abs(C(i,j)) * beta(j);
    end
    beta(i) = soma1 + sum(abs(C(i,(i+1):n)));
end

if (max(beta) >= 1)
    fprintf(' - Nao ha garantia de convergecia do metodo.\n');
    return;
end

% Metodo de Gauss-Seidel
it = 0;
while (it < itmax)
    for i = 1:n
        x = 0;
        for j = 1:n
            if (j ~= i)
                x = x + A(i,j) * x0(j);
            end
        end
        x0(i) = (b(i) - x) / A(i,i);
    end
    if (norm(x) - norm(x0) > tol)
        break;
    end
    it = it + 1;
end

% Saida
if (it >= itmax)
    fprintf(' - Nao foi possivel solucao partindo desse x0. (nmax atingido)\n');
else
    fprintf(' - Vetor solucao:\n');
    for i = 1:n
        fprintf(' x(%d) = %f\n', i, x0(i));
    end
end