#include <stdio.h>
#include <sys/ioctl.h>
#include <signal.h>

void sighandler(){
	struct winsize ws;
	ioctl(fileno(stdout), TIOCGWINSZ, &ws);
	printf("terminal size: w = %d | h = %d\n", ws.ws_col, ws.ws_row);
}

int main(){
	int n;
	signal(SIGWINCH, sighandler);
	scanf("%d", &n);
	return 0;
}
