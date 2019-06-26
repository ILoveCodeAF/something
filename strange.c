#include <stdio.h>

#define Event 3
#define ECHO 2
#define SAY 1

void print(void* c){
	char* ch = (char*) c;
	printf("%s", ch);
}
void print_string(char* string, void func(void *)){
	func(string);
}


static void echo(void*);
static void say(void*);
static void (*func[Event])(void*) = {
	[ECHO] = echo,
	[SAY] = say
};

int main(){
	char* string = "hello";
	print_string(string, print);

	printf("\n ----------------------- \n");

	char* s = "just kidding";
	if(func[ECHO])
		(func[ECHO])(s);
	if(func[SAY])
		(func[SAY])(s);
	if(func[12])
		(func[12])(s);
	return 0;
}

void echo(void* v){
	char* str = (char*) v;
	printf("%s\n", str);
}
void say(void* v){
	char* str = (char*) v;
	int i = 0;
	while(str[i]){
		printf("%c\n", str[i]);
		++i;
	}
}
