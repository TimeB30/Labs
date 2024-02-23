#include "functions.h"
int is_prime(int number){
    if(number == 1){
        return 0;
    }
    int root = (int)ceil(sqrt(number));
    if(number%2){
        for( int i = 3; i <= root; i += 2 ){
            if(number%i == 0) return 0;
        }
    }else{
        for( int i = 2; i <= root; i++ ){
            if(number%i == 0) return 0;
        }
    }
    return 1;
}

double root_of_power(double x, int exponent, double eps){
    if(exponent > INT_MAX / 2 ){
        return INFINITY;
    }
    double value_current = 1;
    double value_next = (1.0/exponent)*((exponent - 1) * value_current + x/ binary_power(value_current, exponent-1));
    while(fabs(value_current - value_next) > eps){
        value_current = value_next;
        value_next = (1.0/exponent)*((exponent - 1) * value_current + x/ binary_power(value_current, exponent-1));
    }
    return value_next;
}

double old_approximate_power(double base, double exponent){
    union {
        double d;
        long long i;
    } u = {base};
    u.i = (long long)(4606853616395542500L + exponent * (u.i - 4606853616395542500L));
    return u.d;
}

double binary_power(double base, unsigned long long exponent){
    double v = 1.0;
    while(exponent){
        if(exponent & 1){
            v *= base;
        }
        base *= base;
        exponent >>= 1;
    }
    return v;
}

double row_one_over_n(double n){
    double value = 0.0;
    for(int i = 1; i <= n; i++){
        value += 1.0/i;
    }
    return value;
}

double lim_e(double eps, int n){
    return binary_power((1+1.0/n), n);
}
double lim_ln2(double eps, int n){
    double value = n * (root_of_power(2, n, eps) - 1);
    return value;
}

double lim_pi(double eps, int n){
    double value = 1.0 * n * n;

    for(int i = n + 1; i <= 2 * n; i++) {
        value *= i - n;
        value /= i;
        value *= i - n;
        value *= 16;
        value /= i;
    }
    value /= n;
    value /= n;
    value /= n;
    return value;
}

double lim_sqrt2(double eps){ //which is in fact a ROW, thus different prototype
    double value_current = -0.5;
    double value_next = value_current - (binary_power(value_current, 2) / 2) + 1;
    while(fabs(value_current - value_next) > eps){
        value_current = value_next;
        value_next = value_current - (binary_power(value_current, 2) / 2) + 1;
    }
    return value_next;
}

double lim_gamma(double eps, int n){

    double value = row_one_over_n(n) - log(n);
    return value;
}

double lim(double (*limit)(double, int), double epsilon){
    int n = 1;
    double value_current = limit(epsilon, n);
    double value_next = limit(epsilon, n+1);

    while(fabs(value_next - value_current) > epsilon){
        n++;
        if(n == INT_MAX || value_current < epsilon){
            return value_next;
        }
        value_current = value_next;
        value_next = limit(epsilon, n+1);
    }
    return value_next;
}

double row_e(double eps, int n){
    double result = 1.0;
    if(n == 0){
        return result;
    }
    for( int i = 1; i <= n; i++){
        result /= i;
    }
    return result;
}

double row_pi(double eps, int n){
    double value = 1.0;
    n++;
    value = binary_power(-1, n-1) / (2*n - 1);
    return 4 * value;

}
double row_ln2(double eps, int n){
    double value = 1.0;
    n++;
    value = binary_power(-1, n-1) / n;
    return value;
}

double row_sqrt2(double eps, int n){
    n = 2;
    double numerator = binary_power(2, n-1) - 1;
    double denominator = binary_power(2, n);
    double value_current = old_approximate_power(2, numerator/denominator);
    double numerator_next = binary_power(2, n) - 1;
    double denominator_next = binary_power(2, n + 1);
    double value_next = old_approximate_power(2, numerator_next/denominator_next);

    while(fabs(value_next - value_current) > eps){
        n++;
        value_current = value_next;
        numerator_next = binary_power(2, n) - 1;
        denominator_next = binary_power(2, n + 1);
        value_next = old_approximate_power(2, numerator_next/denominator_next);
    }
    return value_next;
}

double row_gamma(double eps, int n){
    n++;
    double value;
    if(n < 2){
        value = (-1)*binary_power(M_PI, 2)/6;
        return value;
    }
    int square_current = 1;
    int number_next = 3;

    while(square_current + number_next <= n){
        square_current += number_next;
        number_next += 2;
    }
    if(n == square_current){
        return binary_power(-1, n) * eps * 2;
    }

    value = (1.0/square_current) - (1.0/n);
    return value;
}

double row(double(*row_)(double, int), double epsilon){
    int n = 0;
    double value_current = row_(epsilon, n);
    double value_next = value_current + row_(epsilon, n+1);

    while(fabs(value_next - value_current) > epsilon){
        //printf("\n%d  %.30f  %.30f", n, value_current, value_next);
        n++;
        value_current = value_next;
        value_next += row_(epsilon, n+1);
    }
    return value_current;
}

double eq_e(double argument, double eps){
    return log(argument) - 1;
}

double eq_pi(double argument, double eps){
    return sin(argument);
}

double eq_ln2(double argument, double eps){
    return old_approximate_power(lim_e(0, (int)2000000000), argument) - 2;
}

double eq_sqrt2(double argument, double eps){
    return binary_power(argument, 2) - 2;
}


double eq(double(*eq_)(double, double), double epsilon){
    double a = 0.1;
    double b = 4.0;
    while(fabs(a-b) > epsilon){
        //printf("\n%f %f %f %f", a, b, eq_((a+b)/2, epsilon), (a+b)/2);
        if(eq_(a, epsilon) * eq_((a + b) / 2, epsilon) > 0){
            a = (a + b) / 2;
        }else if(eq_(b, epsilon) * eq_((a + b) / 2, epsilon) > 0) {
            b = (a + b) / 2;
        }else{
            return (a+b) / 2;
        }
    }
    return (a+b)/2;
}

double eq_gamma(double epsilon){
    double a = 0.1;
    double b = 4.0;
    double value_current;
    double value_next;

    int t = 3;

    value_current = log(2) * 0.5;
    value_next = log(3) * 1.0/3;
    double product = 1.0/3;
    while(fabs(value_current - value_next) > epsilon){
        t++;
        if(is_prime(t)) {
            product *= (1.0 - 1.0/t);
        }
        value_current = value_next;
        value_next = log(t) * product;
    }

    while(fabs(a-b) > epsilon){
        double argument = (a+b)/2;
        double value_at_the_left = value_next - exp(-a);
        double value_at_the_middle = value_next - exp(-argument);
        double value_at_the_right = value_next - exp(-b);
        if(value_at_the_left * value_at_the_middle > 0){
            a = (a + b) / 2;
        }else if(value_at_the_middle * value_at_the_right > 0){
            b = (a+b)/2;
        }else{
            return (a+b)/2;
        }
    }
    return (a+b)/2;
}