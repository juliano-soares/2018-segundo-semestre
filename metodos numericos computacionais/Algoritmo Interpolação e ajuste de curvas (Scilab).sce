clc;clear;
function [x]=sist_lin(mat,y)
[l,k]=size(mat)
mat(:,k+1)=y
condicionado=%T
for j=1:k
        pivor=max(abs(mat(j:l,j)))
        if pivor<>0
            for i=j:l
                if abs(mat(i,j))==pivor
                    temp=mat(j,:)
                    mat(j,:)=mat(i,:)
                    mat(i,:)=temp
                 break
             end
             end
             for i=j+1:l
                 mat(i,:)=mat(i,:)-(mat(i,j)/mat(j,j))*mat(j,:)
             end
        else
         condicionado=%F
        end
end
if condicionado
x(k)=mat(l,k+1)/mat(l,k)
for i=k-1:-1:1
    soma=0
    for j=i+1:k
        soma=soma+mat(i,j)*x(j)
    end
   x(i)=(mat(i,k+1)-soma)/mat(i,i)
end
else
disp("Erro ao solucionar o sistema de equações.")
abort
end
endfunction
printf('| INTERPOLAÇÃO |\nPontos Conhecidos\n')
printf("-----------------------------------------------------------------------\n")
printf("Valores das abscissas:\n1)Para intervalos constantes;\n2)Para os inserir.\n")
z=input('')
if z==1 then
    a=input("Limite inferior:")
    b=input("Limite superior:")
    q=input("Quntidade de pontos desejados:")
    X=linspace(a,b,q)'
else
    X=input('Entre com os valores na forma [x₁ x₂ ...]:')'
end
[m,n]=size(X)
inf=min(X);sup=max(X)
var=(sup-inf)/100
inf=inf-50*var
sup=sup+50*var
printf("-----------------------------------------------------------------------\n")
printf('Valores das ordenadas:\n1)Para obtê-los via função;\n2)Para os inserir.\n')
z=input('')
if z==1 then
    deff('[y]=f(x)','y='+input("Entre com a função seguindo os parâmetros do Scilab:","s"))
    Y=f(X)
    clf;fplot2d(inf:var:sup,f)
else
    Y=input('Entre com os valores na forma [f(x₁) f(x₂) ...]:\n')'
end
for i=1:m
   M(:,i)=X.^(m-i)
end
A=sist_lin(M,Y)
A=A(m:-1:1)
function [y]=p(x)
    y=0
    for i=0:m-1
        y=y+A(i+1)*x^(i)
    end
endfunction
pol=pol2str(poly(A,'x','c'))
fplot2d(inf:var:sup,p,style=5)
xtitle('','x','y')
legend('f(x)','P(x)',4)
function [c]=lag(x)
    c=0
for i=1:m
    L=1
    for j=1:m
        if j<>i
            L=L*(x-X(j))/(X(i)-X(j))
         end
     end
     c=c+L*Y(i)
end
endfunction
printf('\n-----------------------------------------------------------------------')
printf('\nPOLINÔMIO INTERPOLADOR:\nP(x)='+pol)
printf('\n-----------------------------------------------------------------------')
printf('\nEntre com um valor x para obter P(x) e Lag(x) ou insira espaço para finalizar:')
c=input('','s')
while c<>' '
px=p(strtod(c));lagx=lag(strtod(c))
printf("P('+c+')=%f\nLag('+c+')=%f\n",px,lagx)
if z==1
    exat=f(strtod(c))
    printf('Valor exato:%f\n',exat)
    printf('Erro para P('+c+')=%f%%\n',(px-exat)/exat*100)
    printf('Erro para Lag('+c+')=%f%%',(lagx-exat)/exat*100)
end
c=input('','s')
end
clf;clc
printf('| MÍNIMOS QUADRADOS |\nPontos Experimentais')
printf('\nInsira os pontos na forma [x₁ x₂ ...;y₁ y₂...]:');pontos=input('')
X=pontos(1,:)';Y=pontos(2,:)'
[m,n]=size(X)
printf('Insira as funções g(x) na forma [''g₁(x)'' ''g₂(x)'' ...]:');gs=input('')
[n,qtd_ter]=size(gs)
function [y]=g(x,t)
deff ('[y]=gi(x)','y='+gs(t))
y=gi(x)
endfunction
A=zeros(qtd_ter,qtd_ter);b=zeros(qtd_ter,1)
for i=1:qtd_ter
    for j=1:i
        for k=1:m
            A(i,j)=A(i,j)+g(X(k),i)*g(X(k),j)
            if i==qtd_ter
                b(j)=b(j)+Y(k)*g(X(k),j)
            end
        end
        A(j,i)=A(i,j)
    end
end
coef=sist_lin(A,b)
coefstr=string(int(10000*coef)/10000)
astr=''
for i=qtd_ter:-1:1
    sinal=''
    if coef(i)>=0
        sinal='+'
    end
    astr=astr+sinal+coefstr(i)+string(gs(i))
end
function [y]=a(x)
    y=0
    for i=1:qtd_ter
        y=y+coef(i)*g(x,i)
    end
endfunction
inf=min(X);sup=max(X)
var=(sup-inf)/150
plot (X,Y,'o')
fplot2d(inf:var:sup,a,style=5)
xtitle('','x','y')
legend('Experimental','a(x)='+astr,4)
printf('\n-----------------------------------------------------------------------')
printf('\nFUNÇÃO AJUSTADA: a(x)='+astr)
printf('\n-----------------------------------------------------------------------')
