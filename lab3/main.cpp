#include <iostream>
#include <cmath>

double func(double x){
    return exp(x);
}

double trap_method(double a, double n, double h){
    double res = 0;
    for(int i = 0; i < n; i++){
        res += h * (func(a + h*i) + func(a + h*(i+1))) / 2;
    }
    return res;
}

double Simpsons_method(double a, double b, double h, double n){
    double res = func(a) + func(b);
    for(int i=1; i <= n/2; i++){
        res += 4 * func(a + (2*i-1) * h);
        if(i == n/2) continue;
        res += 2 * func(a + (2*i) * h);
    }
    res = res * h / 3;
    return res;
}

int main() {
    double a, b, n;
    double h, I, S1, S2, k;
    I = func(1) - 1;

    std::cout << "ENTER PARAMETERS [a, b, n]: \n";
    std::cin >> a >> b >> n;
    h = (b-a) / n;

    //trapezoid method
    S1 = trap_method(a, n, h);
    S2 = trap_method(a, 2*n, h/2);
    k = log2(fabs(S1 - I) / fabs(S2 - I));
    std::cout << "TRAPEZOID METHOD: S = " << S1 << " | k = " << k;

    //Simpson's method
    S1 = Simpsons_method(a, b, h, n);
    S2 = Simpsons_method(a, b, h/2, 2*n);
    k = log2(fabs(S1 - I) / fabs(S2 - I));
    std::cout << "\nSIMPSON'S METHOD: S = " << S1 << " | k = " << k;

    return 0;
}
