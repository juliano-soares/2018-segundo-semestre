% metodo dos minimos quadrados

clc;
clear;
%Entrada vetor x=[x1 x2 x3 ... x4]
x = input('Entre com vetor x:');
%Entrada vetor y
y = input('Entre com vetor y:');
%Diagrama de dispersao plot(
%Escolhe o grau do polinomio m=4
m = input('Entre com o grau do polinomio:');
n = length(x);
A=zero(m+1,m+1);
b=zero(m+1,1);

for i=1:(m+1)
    for j = 1:(m+1)
        aux=2*m-i-j+;
        A(i,j)=sum(x.^(aux));
    end
    b(i)=sum(y.*(x.^(m-i+1)));
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

coef = num2str(x'); % Cria o polinomio a partir dos coeficientes
p = [coef(1,:) '* x^' num2str(n-1)]
for i=2:n
	p = [p ' + (' coef(i,:) ')* x^' num2str(n-1)]
end

disp('O polinomio e: ');
disp(p);
erro = 0;
for i = 1:quant
	erro = erro + (subs(p,a(i))-b(i))^2;
end
erro = sqrt(erro^(1/2));

fplot(p,[min(a),max(a)]);
hold on;
grid on;
plot(a,b,'ro');
title('Polinomio de Ajuste');
xlabel('x');
% metodo de eliiminacao de gauss jacobi