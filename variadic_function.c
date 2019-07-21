// https://en.wikipedia.org/wiki/Variadic_function#Example_in_C

#include <stdio.h>
#include <stdarg.h>


int add( int num_element, ...){
    va_list ap;
    int sum = 0;
    va_start(ap,  num_element);
    for(int i = 0; i < num_element; ++i){
        sum += va_arg(ap, int);
    }
    va_end(ap);
    return sum;
}

float func_base(int a, int b){
    return a*b;
}

typedef struct{
    int a;
    int b;
} func_arg;

int var_func(func_arg in){
    int a = in.a? in.a : 10;
    int b = in.b? in.b : -1;
    return func_base(a, b);
}

#define func(...) var_func((func_arg){__VA_ARGS__})

int main(){
    printf("%d\n", add(4, 1, 2, 2, 2));//7
    printf("%d\n", func(3, 4));//3*4 = 12
    printf("%d\n", func(4));//4*-1 = -4
    printf("%d\n", func(0, 4));//10*4 = 40
    printf("%d\n", func());//10*-1 = -10
    return 0;
}