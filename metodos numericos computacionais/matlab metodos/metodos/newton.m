% Metodo de Newton
% por juliano leonardo soares

% Limpeza
clear;
clc;

% Entrada
f = str2sym(input('Digite a funcao: ', 's'));
x0 = input('Digite o ponto inicial Xo: ');
tol = input('Digite a tolerancia desejada: ');
nmax = input('Digite o numero maximo de iteracoes: ');

% Metodo de Newton
i = 1;
erro = 0;
fx0 = subs(f, x0);
dfx = diff(f);
dfx0 = subs(dfx, x0);
if dfx0 == 0
    fprintf('\n - O metodo de Newton falhou. Tente utilizar outro ponto inicial.\n');
    return;
end
x1 = x0 - (fx0 / dfx0);
fx1 = subs(f, x1);
intervalo = abs(x1 - x0) / abs(x1);

fprintf('\n\n');
fprintf('----------------------------------------------------------------------------------------------------------\n');
fprintf(' Iteracao \t x0 \t\t f(x0) \t\t Df(x0) \t\t x1 \t\t\t f(x1) \t\t tamanho do intervalo\n');
fprintf('----------------------------------------------------------------------------------------------------------\n');

while intervalo > tol && i <= nmax
    fx0 = subs(f, x0);
    dfx = diff(f);
    dfx0 = subs(dfx, x0);
    
    if ~erro
        x1 = x0 - (fx0 / dfx0);
        if abs(dfx0) < tol
            erro = 1;
            fprintf(' - O metodo de Newton falhou. Continuando...\n');
            pause;
        else
            dfxa = dfx0;
        end
    end
    if erro
        x1 = x0 - (fx0 / dfxa);
        dfx1 = subs(dfx, x1);
        if abs(dfx1) > tol
            erro = 0;
        end
    end

    fx1 = subs(f, x1);
    
    % Grafico
    clf reset;
    hold on;
    grid on;
    plot([x0, x1], [0, 0], 'k-');
    if double(x0) > double(x1)
        fplot(f, [double(x1), double(x0)], 'r-');
    else
        fplot(f, [double(x0), double(x1)], 'r-');
    end
    plot([x1, double(x0)], [0, double(fx0)], 'g-');
    plot(x0, 0,'b*');
    plot(x1, 0,'g*');
    hold off;
    
    fprintf(' %2d \t\t %5.4f \t %5.4f \t %5.4f \t\t %5.4f \t\t %5.4f \t %5.4f\n', i, x0, fx0, dfx0, x1, fx1, intervalo);
    pause;
    
    if abs(fx1) < tol
        fprintf('\n - O metodo convergiu pela imagem e a solucao eh %5.4f.\n', x1);
        return;
    end
    
    intervalo = abs(x1 - x0) / abs(x1);
    x0 = x1;
    i = i + 1;
end

% Saida
if i >  nmax
    fprintf('\n - Nao foi possivel obter a solucao em %d iteracoes.\n', nmax);
    fprintf('   Pode ser que a funcao %s nao corte o eixo x.\n', f);
else
    fprintf('\n - O metodo convergiu pelo dominio e a solucao eh %5.4f.\n', x1);
end
