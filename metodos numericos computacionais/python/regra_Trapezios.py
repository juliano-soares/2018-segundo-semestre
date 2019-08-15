# -*- coding: utf-8 -*-
"""
Created on Wed Nov 28 17:56:48 2018

@author: Juliano
"""

clear;
clc;
function trap = somatrap(f,a,b,n)
    x = linspace(a,b,n+1)
    y = f(x);
    delta_X = (b-a)/n;
    lrs = sum (y(1:n))* delsta_X;
    scf();
    plot2d2(x,y,style=5,rect=[min(x),min([0 y]),max(x),max(y)]);
    A =gca();
    A.k_location = "origin";
    plot2d3(x,y,style=5);
    xx=lispace(a,b,50);
    plot2d(xx,f(xx));
    endfunction
    