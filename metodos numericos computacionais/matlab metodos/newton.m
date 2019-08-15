% MÉTODO DE NEWTON

clc;                                                                       
clear;
sf = input('Digite a funcao: ', 's');
f = str2sym(sf);
xi = input('digite o ponto inicial: ');
p = input('Digite a precisão: ');
n = input('Digite o numero maximo de execucoes: ');
 
erro = 1;
nexe = 0;
xa = 0;
flagerro = 0;

while(erro > p && nexe < n)
    fx = subs(f,xi);
    fd =  diff(f);
    fdxi = subs(fd, xi);
    if(not(flagerro))
        x2 = xi - (fx/fdxi);
        if(abs(fdxi) >= p)
            fdx0 = fdxi;
        else
            fprintf('O metodo de newton falhou.\n');
            flagerro = 1;
            pause();
        end
    end
    if(flagerro)
        x2 = xi - (fx/fdx0);
        dfx2 = subs(fd, x2);
        if(abs(dfx2) >= p)
            flagerro = 0;
        end
    end
    fx2 = subs(f,x2);
    fprintf('xi= %2.5f | fx= %2.5f | fdx = %2.5f -- abs(fx) = %2.5f | abs(fdx) = %2.5f | x2 = %2.5f -- fx2 = %2.5f\n', xi, fx, fdxi, abs(fx), abs(fdxi), x2, fx2);
    if(abs(fx2) < p)
        fprintf('O metodo convergiu pela imagem e a solução é: %2.5f\n', x2);
        break;
    end 
    if(erro < p && abs(fx2) >= p)
        fprintf('O metodo convergiu pelo dominio e a solucao é: %2.5f\n', xi);
        break;
    elseif(nexe >= n)
        disp('O metodo atingiu o numero maximo de execuções');
        break;
    end
    % função f:
    grid on;
    hold on;
    fplot(f);
    % ponto na função (x0,f(xo))
    plot(xi,fx,'o');
    % ponto no eixo X = x0
    plot(xi,0,'o');
    % ponto x2 (x2 = X-(f(xo)/f'(xo)) , 0)
    plot(x2,0,'o');
    % linha de x1 a x0
    plot([x2,xi],[0,fx]);
    
    erro = abs(x2-xi)/abs(x2);
    xi = x2;
    nexe = nexe + 1;
    pause();
end


