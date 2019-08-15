% interpolacao polinomial

% Entradas dos dados
x = input('digite os pontos x:'); 
y = input('digite os valores de y:');

% plotar os pontos no grafico
plot(x,y,'r+');

% pegar dados necessario
n = length(x); % tamanho do vetor x
gr = n-1;      % 

% construir A, B:
A=zeros(n+1,n+1); % criando a matrix A
B=zeros(n+1,1);   % criando a matrix B
% segundo Ax = B
% {1 x^2 x^3 ...][a0 a1 a2 ...]T = B
% y = a0 + a1x + a2x^2 + a3x^3 ...
for i=1:(n+1)
    for j = 1:(n+1)
        aux=2*n-i-j+n;
        A(i,j)=sum(x.^(aux));
    end
    B(i)=sum(y.*(x.^(n-i+1)));
end

% Solução do sistema linear 
x = zeros(1,n);
x(n) = A(n,n+1)/A(n,n);
for i=n-1:-1:1
	soma = 0;
	for j = i+1:n
		soma = soma + A(i,j)*x(j);
	end
	x(i) = (A(i,n+1)-soma)/A(i,i);
end
C=inv(x)*y;
pn1=C'*(Um*x').^([0:n-1]'*ones(1,m)); % valores interpolados

disp('O polinomio e: ');
disp(p);
plot(p);
hold on;
grid on;
plot(A,B,'r+');
title('Polinomio de Ajuste');
xlabel('x');
