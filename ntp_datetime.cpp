#include <iostream>
#include <time.h>


// T1 bit: 16->23
// T2 bit: 32->39
// T3 bit: 40->17
long to_integer(unsigned char* ntp, int length){
	long integer = 0;
	for(int i = 0; i < length; ++i){
		integer = (integer<<8) + ntp[i];
	}
	return integer;
}

float to_ms(long integer){
	return (float)integer/((long)1<<32);
}

int main(){
	unsigned char ntp[] = {225, 72, 52, 194};
	int length = 4;
	std::cout<<to_integer(ntp, length)<<std::endl;
	std::cout<<to_ms(2106946028)<<std::endl;
	return 0;
}
