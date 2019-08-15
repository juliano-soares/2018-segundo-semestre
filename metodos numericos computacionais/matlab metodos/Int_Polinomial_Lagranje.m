% Interpolacao Polinomial por Lagranje

% teste: xi = [1 2 3]
%        yi = [-1 3 -5]
% pn = -1*L1(x)+3*L2(x)-5*L3(x)
% L1 = (x-2)(x-3)/2
% L2 = (x-1)(x-3)/-1
% L3 = (x-1)(x-2)/2
% pn = -1*((x-2)(x-3)/2)+3*((x-1)(x-3)/-1)-5*((x-1)(x-2)/2)

% Entradas dos dados
x = input('digite os pontos x:'); 
y = input('digite os valores de y:');
% plotar os pontos no grafico
plot(x,y,'r+');
% pegar dados necessario
n = length(x); % tamanho do vetor x
gr = n-1;
pn=0; 
% Construcao dos Li(x) 
for i=1:n
    num='a';
    den=1;
    L='a';
    for j =1:n
       if i~=j
           if(num~='a')
               num=[num ' *(x-' num2str(x(j)) ')'];
               den = den*(x(i) - x(j));
           else
               num = ['(x-' num2str(x(j)) ')'];
               den = den * (x(i) - x(j));
           end
       end
    end
    L = [num ')/' num2str(den)];
    if pn~='a'
       pn = [pn '+' num2str(y(i)) '*(' L ') '];
    else
       pn = [num2str(y(i)) '*(' L ') '];
    end
end

disp('O polinomio e: ');
disp(pn);