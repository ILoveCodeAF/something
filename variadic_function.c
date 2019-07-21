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

int main(){
    printf("%d\n", add(4, 1, 2, 2, 2));
    return 0;
}