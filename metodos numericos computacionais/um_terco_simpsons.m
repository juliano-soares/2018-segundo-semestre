% regra de 1/3 de simpsons
% Juliano Leonardo Soares

% Limpeza
clear;
clc;
function trap = simpsons(f,a,b,n){
    if(n==0)
        fprintf('Divisao por zero');
    end
    else
        if(n<0)
            fprintf('Intervalo Inválido');
        end
        if(n/2 ? 0)
            n = n + 1;
        end
        h =(xn-x0)/n;
        x = x0+h;
        SomaPares = 0;
        SomaImpares = 0;
        for(i = 1;n-1;i++){
            if (i / 2 = 0)
                SomaPares = SomaPares+f(x);
            end
            else
                SomaImpares = SomaImpares+f(x);
                x=x+h;
            end
        R = h / 3 * (f(x0) + f(xn) + 4 * SomaImpares + 2 * SomaPares);
        fprintf('O resultado da integral da função f é ', R);
    end
end function
