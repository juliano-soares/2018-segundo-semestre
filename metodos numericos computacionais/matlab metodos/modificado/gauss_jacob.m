% Metodo iterativo de Gauss-Jacob
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
for i = 1:n
    A(i,i) = 1000 * A(i,i);
end

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

% Teste de convergencia
if (norm(C, Inf) >= 1 & norm(C, 1) >= 1)
    fprintf(' - Nao ha garantia de convergecia do metodo.\n');
    return;
end

% Metodo de Gauss-Jacob
it = 0;
x1 = C * x0 + g';
err = norm(x1 - x0, Inf) / norm(x1);
while (it < itmax & tol < err)
    x1 = C * x0 + g';
    err = norm(x1 - x0, Inf) / norm(x1, Inf);
    x0 = x1;
    it = it + 1;
end

% Saida
if (it >= itmax)
    fprintf(' - Nao foi possivel solucao partindo desse x0. (nmax atingido)\n');
else
    fprintf(' - Vetor solucao:\n');
    for i = 1:n
        fprintf(' x(%d) = %f\n', i, x1(i));
    end
end
