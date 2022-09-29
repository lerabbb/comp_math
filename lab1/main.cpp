#include <iostream>
#include <cmath>
#include <float.h>

double eps = 0.000001;
double a=0;
double b=0;
double c=0;

double func(const double x){ //значение кубического уравнения в точке x
    return x*x*x + a*x*x + b*x + c;
}
double deriv_zero(double D, int sign){
    return (-2 * a + sign * sqrt(D)) / 6;
}

double root_onLimSegment(double left, double right) {
    //ограниченный отрезок
    double f_l, f_r, h, f;
    f_l = func(left);
    f_r = func(right);

    if(f_l <= -eps && f_r >= eps) {
        while (std::abs(left - right) >= eps) {
            h = (left + right) / 2;
            f = func(h);
            if (f >= eps) {
                right = h;
            } else if(f <=-eps){
                left = h;
            }
        }
    } else if(f_l >= eps && f_r <= -eps){
        while(std::abs(left-right) >= eps){
            h = (left + right) / 2;
            f = func(h);
            if(f >= eps){
                left = h;
            } else if(f <= -eps){
                right = h;
            }
        }
    }
    return (left+right)/2;
}

double root_onInfSegment(double left, double right){ //поиск корней на бесконечном отрезке
    double delta, temp, start, left2, right2;
    int k = 1, sign;
    delta = 3;

    if(std::abs(left) < DBL_MAX && right == DBL_MAX) {
        sign = 1;
        start = left;
    } else if(std::abs(right) < DBL_MAX && left == -DBL_MAX){
        sign = -1;
        start = right;
    }

    temp = func(start + sign * (k - 1) * delta);
    while(true){
        double temp2 =func(start + sign * k * delta);
        if(temp < 0 && temp2>0 || temp > 0 && temp2<0){
            break;
        }
        k++;
    }

    if(sign == 1) {
        left2 = start + (k - 1) * delta;
        right2 = start + k * delta;
    }else if(sign == -1) {
        left2 = start - k * delta;
        right2 = start - (k-1) * delta;
    }
    return root_onLimSegment(left2, right2);
}


int main() {
    double D, f, x[3], n;  //x[i] - корни; n - кол-во корней
    double alpha, beta, f_a, f_b;
    std::cout<<"Enter parameters [a, b, c]:\n";
    std::cin >> a >> b >> c;

    D = 4*a*a - 4*3*b; // дискриминант f'(x)

    if(D<=0){
        f=func(0);
        n = 1;
        if(std::abs(f) < eps){
            x[0] = 0;
        } else if(f < -eps){
            x[0] = root_onInfSegment(0, DBL_MAX);
        } else if(f > eps){
            x[0] = root_onInfSegment(-DBL_MAX, 0);
        }
    }

    else{
        alpha = deriv_zero(D, -1);
        beta = deriv_zero(D, 1);
        f_a = func(alpha);
        f_b = func(beta);

        if(f_a > eps){
            if(f_b > eps){
                n = 1;
                x[0] = root_onInfSegment(-DBL_MAX, alpha);
            }else if(std::abs(f_b) < eps){
                n = 2;
                x[0] = root_onInfSegment(-DBL_MAX, alpha);
                x[1] = beta;
            }else if(f_b < -eps){
                n = 3;
                x[0] = root_onInfSegment(-DBL_MAX, alpha);
                x[1] = root_onLimSegment(alpha, beta);
                x[2] = root_onInfSegment(beta, DBL_MAX);
            }
        } else if(f_b < -eps){
            if(std::abs(f_a) < eps){
                n = 2;
                x[0] = alpha;
                x[1] = root_onInfSegment(beta, DBL_MAX);
            } else if(f_a < -eps){
                n = 1;
                x[0] = root_onInfSegment(beta, DBL_MAX);
            }
        } else if(std::abs(f_a) < eps && std::abs(f_b) < eps){
            n = 1;
            x[0] = (alpha + beta) / 2;
        }
    }

    std::cout << "Number of roots: " << n;
    std::cout << "\nRoots:";
    for(int i=0; i<n; i++){
        std::cout << std::fixed << "\nx" << i+1 << " = " << x[i];
    }
    return 0;
}
