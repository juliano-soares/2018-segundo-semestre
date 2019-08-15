% Metodo da Falsa Posicao
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
fprintf(' Iteracao \t a \t\t\t f(a) \t\t b \t\t\t f(b) \t\t x \t\t f(x) \t\t tamanho do intervalo\n');
fprintf('----------------------------------------------------------------------------------------------------------\n');

while intervalo > tol && cont <= nmax    
    fa = subs(f, a);
    fb = subs(f, b);
    x = (a*double(fb) - b*double(fa))/(double(fb) - double(fa));
    fx = subs(f, x);
    
    % Grafico
    clf reset;
    hold on;
    grid on;
    plot([a, b], [0, 0], 'k-');
    plot([a, b], [fa, fb], 'b-');
    fplot(f, [a, b], 'r-');
    plot(x, 0,'g*');
    hold off;
    
    fprintf(' %2d \t\t %5.4f \t %5.4f \t %5.4f \t %5.4f \t %5.4f \t %5.4f \t %5.4f\n', cont, a, fa, b, fb, x, fx, intervalo);
    pause;
    
    if abs(fx) < tol
        fprintf('\n - Solucao obtida pela imagem: %f\n', x);
        return;
    elseif fa * fx < 0
        b = x;
    elseif fb * fx < 0
        a = x;
    end
    
    intervalo = b - a;
    cont = cont + 1;
end

% Saida
x = (a*double(fb) - b*double(fa))/(double(fb) - double(fa));
fprintf('\n - A solucao foi obtida pelo dominio: %f\n', x);

% Grafico final
clf reset;
hold on;
grid on;
plot([a, b], [0, 0], 'k-');
plot([a, b], [fa, fb], 'r-');
fplot(f, [a, b], 'b-');
plot(x, 0,'g*');
hold off;
