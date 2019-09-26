#include "stdio.h"

#include "unicode.h"

int main(){
	char white_square[] = {0xE2, 0x96, 0xA1};
	char black_square[] = {0xE2, 0x96, 0xA0};
	char* wc = wchar_to_utf8(9646);
	char* bc = wchar_to_utf8(9647);
	char* full_block = wchar_to_utf8(9617);//9608 full block
	char fb[] = {0xE2, 0x96, 0x88};
	printf("%s\n%s\n%s\n%s\n%s\n%s%s\n", 
			white_square, black_square, wc, bc, full_block, fb, fb);
	return 0;
}
