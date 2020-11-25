function [outputArg1,outputArg2] = resolver(inputArg1,inputArg2)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

syms p000 p100 p010 p001 p200 p110 p101 p020 p011 p002 


%%valori probabilità di routing
pDelay = 0.063996;
pMulti = 0.948820;
p = 0.8;
%%%%%%%%%%%%%%%%


prevLambda1 = 0.05;
prevLambda2 = 0.066667;
prevLambda3 = 0.083333;
sumPrevLambda = prevLambda1 + prevLambda2 + prevLambda3;

prevMu1 = 0.116667;
prevMu2 = 0.116667;
prevMu3 = 0.116667;
sumPrevMu = prevMu1 + prevMu2 + prevMu3;

rho = sumPrevLambda / sumPrevMu;
rho1 = prevLambda1/prevMu1;
rho2 = prevLambda2/prevMu2;
rho3 = prevLambda3/prevMu3;

p1 = (prevLambda1)/(prevLambda1+prevLambda2+prevLambda3);
p2 = (prevLambda2)/(prevLambda1+prevLambda2+prevLambda3);
p3 = (prevLambda3)/(prevLambda1+prevLambda2+prevLambda3);

if (rho1 <= 1)
    nextL1 = prevLambda1;
else 
    nextL1 = prevMu1;
end

if (rho2 <= 1)
    nextL2 = prevLambda2;
else 
    nextL2 = prevMu2;
end

if (rho3 <= 1)
    nextL3 = prevLambda3;
else 
    nextL3 = prevMu3;
end

fprintf('%.5f\n', nextL1);
fprintf('%.5f\n', nextL2);
fprintf('%.5f\n', nextL3);


%lambda1 = nextL1 * pDelay;
%lambda2 = nextL2 * pDelay;
%lambda3 = nextL3 * pDelay;

lambda1 = nextL1 * pMulti + 0.016667*p;
lambda2 = nextL2 * pMulti + 0.016667*p;
lambda3 = nextL3 * pMulti + 0.016667*p;

mu1 = 0.066667;
mu2 = 0.083333;
mu3 = 0.1;

%%Altri server
eqn1 = (lambda1 + lambda2+ lambda3)*p000 == (mu1)*p100 + (mu2)*p010 + (mu3)*p001;
eqn2 = (lambda1 + lambda2+ lambda3+ mu1)*p100 == (lambda1)*p000 + (mu1)*p200 + (mu2)*p110 + (mu3)*p101;
eqn3 = (lambda1 + lambda2+ lambda3+ mu2)*p010 == (lambda2)*p000 + (mu1)*p110 + p020*(mu2) + p011*(mu3);
eqn4 = (lambda1 + lambda2+ lambda3+ mu3)*p001 == p000*(lambda3) + p101*(mu1) + p011*(mu2) + p002*(mu3);
eqn5 = (mu1)*p200 == (lambda1)*p100;
eqn6 = (mu1+mu2)*p110 == (lambda2)*p100 + (lambda1)*p010;
eqn7 = (mu3+mu1)*p101 == (lambda3)*p100 + (lambda1)*p001;
eqn8 = (mu2)*p020 == (lambda2)*p010;
eqn9 = (mu3+mu2)*p011 == (lambda3)*p010 + (lambda2)*p001;
eqn10 = p000 + p100 + p010 + p001 + p200 + p110 + p101 + p020 + p011 + p002 == 1;

%%Multiserver
%eqn1 = (lambda1 + lambda2+ lambda3)*p000 == (mu1)*p100 + (mu2)*p010 + (mu3)*p001;
%eqn2 = (lambda1 + lambda2+ lambda3+ mu1)*p100 == (lambda1)*p000 + (mu1)*2*p200 + (mu2)*p110 + (mu3)*p101;
%eqn3 = (lambda1 + lambda2+ lambda3+ mu2)*p010 == (lambda2)*p000 + (mu1)*p110 + p020*2*(mu2) + p011*(mu3);
%eqn4 = (lambda1 + lambda2+ lambda3+ mu3)*p001 == p000*(lambda3) + p101*(mu1) + p011*(mu2) + p002*2*(mu3);
%eqn5 = (mu1)*2*p200 == (lambda1)*p100;
%eqn6 = (mu1+mu2)*p110 == (lambda2)*p100 + (lambda1)*p010;
%eqn7 = (mu3+mu1)*p101 == (lambda3)*p100 + (lambda1)*p001;
%eqn8 = (mu2)*2*p020 == (lambda2)*p010;
%eqn9 = (mu3+mu2)*p011 == (lambda3)*p010 + (lambda2)*p001;
%eqn10 = p000 + p100 + p010 + p001 + p200 + p110 + p101 + p020 + p011 + p002 == 1;
sol = solve([eqn1, eqn2, eqn3,eqn4,eqn5,eqn6,eqn7,eqn8,eqn9,eqn10], [p000, p100, p010, p001, p200, p110, p101, p020, p011, p002]);
p00Sol = sol.p000
p10Sol = sol.p100
p01Sol = sol.p010
p11Sol = sol.p001
p20Sol = sol.p200
p02Sol = sol.p110
p12Sol = sol.p101
p21Sol = sol.p020
p30Sol = sol.p011
p03Sol = sol.p002
%p40Sol = sol.x11
fprintf('%.25f\n', p00Sol);
fprintf('%.25f\n', p10Sol);
fprintf('%.25f\n', p01Sol);
fprintf('%.25f\n', p11Sol);
fprintf('%.25f\n', p20Sol);
fprintf('%.25f\n', p02Sol);
fprintf('%.25f\n', p12Sol);
fprintf('%.25f\n', p21Sol);
fprintf('%.25f\n', p30Sol);
fprintf('%.25f\n', p03Sol);
%fprintf('%.25f\n', p40Sol);
end