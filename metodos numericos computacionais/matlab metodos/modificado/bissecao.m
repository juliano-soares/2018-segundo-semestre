% Metodo da Bissecao
% por Juliano Leonardo Soares 

% Limpeza
clear;
clc;

% Entrada
f = str2sym(input('Digite a funcao: ', 's'));
a = input('Digite o valor inicial do intervalo: ');
b = input('Digite o valor final do intervalo: ');
while subs(f, a) * subs(f, b) > 0 % f(a)*f(b) > 0
    fprintf(' - Intervalo invalido para o Teorema de Bolzano.\n');
    fprintf(' - Entre com novos valores para o intervalo.\n');
    a = input('Digite o valor inicial do intervalo: ');
    b = input('Digite o valor final do intervalo: ');
end
nmax = input('Digite o numero maximo de iteracoes: ');
tol = input('Digite a tolerancia maxima desejada: ');

% Verifica solucao nos extremos do intervalo
if subs(f, a) == 0 % f(a) = 0
    fprintf('\n - Solucao exata encontrada no limite incial do intervalo: %f\n', a);
    return;
elseif subs(f, b) == 0 % f(b) = 0
    fprintf('\n - Solucao exata encontrada no limite final do intervalo: %f\n', b);
    return;
end

% Verifica intervalo invertido
if a > b
    tmp = a;
    a = b;
    b = tmp;
end

% Aqui f(a)*f(b) < 0, entao comeca o metodo
intervalo = b - a;
cont = 1;

fprintf('\n\n');
fprintf('----------------------------------------------------------------------------------------------------------\n');
fprintf(' Iteracao \t a \t\t\t f(a) \t\t b \t\t\t f(b) \t\t pm \t\t f(pm) \t\t tamanho do intervalo\n');
fprintf('----------------------------------------------------------------------------------------------------------\n');

while intervalo > tol && cont <= nmax
    fa = subs(f, a);
    fb = subs(f, b);
    pm = (a + b)/2;
    fpm = subs(f, pm);
    
    % Grafico
    clf reset;
    hold on;
    grid on;
    plot([a, b], [0, 0], 'k-');
    fplot(f, [a, b], 'r');
    plot(pm, 0,'g*');
    hold off;
    
    fprintf(' %2d \t\t %5.4f \t %5.4f \t %5.4f \t %5.4f \t %5.4f \t %5.4f \t %5.4f\n', cont, a, fa, b, fb, pm, fpm, intervalo);
    pause;
    
    if abs(fpm) < tol
        fprintf('\n - Solucao obtida pela imagem: %f\n', pm);
        return;
    elseif fa * fpm < 0
        b = pm;
    elseif fb * fpm < 0
        a = pm;
    end
    
    intervalo = b - a;
    cont = cont + 1;
end

% Saida
pm = (a + b)/2;
fprintf('\n - A solucao foi obtida pelo dominio: %f\n', pm);

% Grafico final
clf reset;
hold on;
grid on;
plot([a, b], [0, 0], 'k-');
fplot(f, [a, b], 'r-');
plot(pm, 0,'g*');
hold off;
