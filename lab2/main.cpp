#include <iostream>
#include <cmath>
#define IT_NUM 2

double func(double x_n){
    return pow(x_n, 2) - 5;
}
double deriv(double x_n){ //derivative of function
    return 2 * x_n;
}

double Newton_method(double x_0){
    double temp = x_0;
    for(int i = 1; i <= IT_NUM; i++){
        temp = temp - (func(temp) / 2 / temp);
    }
    return temp;
}

double one_tang_method(double x_0){
    double der_x0 = deriv(x_0);  //derivative value in point x_0
    double temp = x_0;
    for(int i = 1; i <= IT_NUM; i++){
        temp = temp - (func(temp) / der_x0);
    }
    return temp;
}

double secant_method(double x_0){
    double prevX, curX, nextX;
    prevX = x_0;
    curX = x_0 - (func(x_0) / 2 / x_0);
    for(int i = 2; i <= IT_NUM; i++) {
        nextX = curX - (func(curX) * (curX - prevX) / (func(curX) - func(prevX)));
        prevX = curX;
        curX = nextX;
    }
    return nextX;
}

int main() {
    double x_0 = 3;
    double val = sqrt(5);
    double Newton_res, tang_res, sec_res;

    Newton_res = Newton_method(x_0);
    tang_res = one_tang_method(x_0);
    sec_res = secant_method(x_0);

    std::cout << "NEWTON'S METHOD: x3 = " << Newton_res << " | variation = " << std::abs(Newton_res - val);
    std::cout << "\nONE TANGENT METHOD:  x3 = " << tang_res << " | variation = "<< std::abs(tang_res - val);
    std::cout << "\nSECANT METHOD: x3 = " << sec_res << " | variation = " << std::abs(sec_res - val);

    if(Newton_res < tang_res && Newton_res < sec_res){
        std::cout << "\nNewton's method is the best\n";
    } else if(tang_res < Newton_res && tang_res < sec_res){
        std::cout << "\nOne tangent method is the best\n";
    } else if(sec_res < Newton_res && sec_res < tang_res){
        std::cout << "\nSecant method is the best\n";
    }
    return 0;
}
