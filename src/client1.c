#include <ncurses.h>
#include <locale.h>
#include "init.h"
#include "client.h"

// sudo apt-get install libncurses5-dev libncursesw5-dev 
// gcc -o client client.o init.o -lncursesw
int main(int argc, char* argv[])
{
	int mainscr = init();
	if(mainscr == 0){
		client(argv);
	}
	return 0;
}
