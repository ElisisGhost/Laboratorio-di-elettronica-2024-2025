syms  a b c d e k q l
eqns=[a+b == c+d, a*k-b*k == q*c-q*d, c*exp(1i*q*l)+d*exp(-1i*q*l) == e*exp(1i*k*l), q*c*exp(1i*q*l)-q*d*exp(-1i*q*l) == k*e*exp(1i*k*l), b, c, d, e];
S = solve(eqns);


