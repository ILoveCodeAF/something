#include <stdio.h>
#include <stdlib.h>

#define BYTE_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_BINARY(byte) \
	(byte & 0x80? '1':'0'), \
	(byte & 0x40? '1':'0'), \
	(byte & 0x20? '1':'0'), \
	(byte & 0x10? '1':'0'), \
	(byte & 0x08? '1':'0'), \
	(byte & 0x04? '1':'0'), \
	(byte & 0x02? '1':'0'), \
	(byte & 0x01? '1':'0')

char* to_binary(int a){
//	int bytes = sizeof int;
	int bits = 8*sizeof(int);
	char* bin = (char*)malloc(bits);
	unsigned int b = (unsigned int)1<<(bits-1);
	int i = 0;
	while(i<bits){
		bin[i] = '0';
		++i;
	}
	i = 0;
	while(b && i<bits){
		if(b & a){
			bin[i] = '1';
		}
		i += 1;
		b >>= 1;
	}
	return bin;
}

int main()
{
	char c = 'a';
	printf(BYTE_PATTERN"\n", BYTE_BINARY(c));
	printf("%s\n", to_binary(c));
	return 0;
}
