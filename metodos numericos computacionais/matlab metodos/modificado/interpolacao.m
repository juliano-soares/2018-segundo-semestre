% Interpolacao Polinomial
% por juliano leonardo soares


% Limpeza
clear;
clc;
format long;

% Entrada
x = input('Digite o vetor x: ');
y = input('Digite o vetor y: ');

% Plotar os pontos
hold on;
grid on;
plot(x,y,'r*');

% Inicio variaveis
n = length(x);
gr = n - 1;

% Construir A,b
A = zeros(n, n);
for i = 1:n
    for j = 1:n
        A(i,j) = x(i)^(n-j);
    end
end
b = y';

% Resolucao sistema linear
resp = gauss(A,b);

% Construcao do polinomio
cef = num2str(resp');
p = [' (' cef(1,:) ' * x^' num2str(n-1) ' ) '];
for i=2:n
    p = [p ' + (' cef(i,:) ' * x^' num2str(n-i) ' )'];
end

fprintf(' - O polinomio eh:\n');
disp(p);

% Plotar o polinomio
fplot(str2sym(p), [min(x), max(x)]);
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