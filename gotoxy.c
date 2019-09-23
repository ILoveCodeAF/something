#include <stdio.h>

void gotoxy(int x, int y){
	printf("%c[%d;%df", 0x1B, y, x);
}

int main(){
	gotoxy(10, 1);
	printf("hello there");
	int n;
	scanf("%d", &n);
	return 0;
}
