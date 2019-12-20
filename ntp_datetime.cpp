#include <iostream>
#include <time.h>
#include <string.h>

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

time_t get_time(const char * dateInput){
	struct tm tm;
	memset(&tm, 0, sizeof(struct tm));
	strptime(dateInput, "%Y/%m/%d %H:%M:%S", &tm);
	return mktime(&tm);
}

int main(){
	unsigned char ntp[] = {225, 72, 52, 194};
	int length = 4;
	std::cout<<to_integer(ntp, length)<<std::endl;
	std::cout<<to_ms(2106946028)<<std::endl;
	time_t milestone = get_time("1900/01/01 00:00:00");
	std::cout<<"milestone: "<<milestone<<std::endl;
	time_t now = get_time("2019/10/09 17:28:27");
	long time70 = 2208988800L;//2209014400//2208989200
	std::cout<<"now: "<<now<<std::endl;
	std::cout<<(now+time70)<<std::endl;
	std::cout<<(now+time70)-to_integer(ntp, length)<<std::endl;
	return 0;
}
