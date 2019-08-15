% Metodo da Secante
% por juliano leonardo soares


% Limpeza
clear;
clc;

% Entrada
f = str2sym(input('Digite a funcao: ', 's'));
x0 = input('Digite o ponto inicial x0: ');
x1 = input('Digite o ponto inicial x1: ');
tol = input('Digite a tolerancia desejada: ');
nmax = input('Digite o numero maximo de iteracoes: ');

% Metodo da Secante
i = 1;
erro = 0;
fx0 = subs(f, x0);
fx1 = subs(f, x1);
x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);

intervalo = abs(x1 - x0) / abs(x1);

fprintf('\n\n');
fprintf('----------------------------------------------------------------------------------------------------------\n');
fprintf(' Iteracao \t x0 \t\t f(x0) \t\t x1 \t\t\t f(x1) \t\t x2 \t\t\t f(x2) \t\t tamanho do intervalo\n');
fprintf('----------------------------------------------------------------------------------------------------------\n');

while intervalo > tol && i <= nmax
    fx0 = subs(f, x0);
    fx1 = subs(f, x1);
    
    if (fx1 - fx0) == 0
        fprintf('\n - O metodo da Secante falhou (div por 0).\n');
        fprintf('   Tente utilizar outros pontos iniciais.\n');
        return;
    end
    
    x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
    fx2 = subs(f, x2);
    
    fprintf(' %2d \t\t %5.4f \t %5.4f \t %5.4f \t\t %5.4f \t %5.4f \t\t %5.4f \t %5.4f \n', i, x0, fx0, x1, fx1, x2, fx2, intervalo);
    pause;
    
    if abs(fx2) < tol
        fprintf('\n - O metodo convergiu pela imagem e a solucao eh %5.4f.\n', x2);
        return;
    end
    
    x0 = x1;
    x1 = x2;
    intervalo = abs(x1 - x0) / abs(x1);
    i = i + 1;
end

% Saida
if i > nmax
    fprintf('\n - Nao foi possivel obter a solucao em %d iteracoes.\n', nmax);
    fprintf('   Pode ser que a funcao %s nao corte o eixo x.\n', f);
else
    fprintf('\n - O metodo convergiu pelo dominio e a solucao eh %5.4f.\n', x2);
end
