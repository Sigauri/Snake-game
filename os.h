


//disable line buffering if sel == 0, otherwise enable
void line_buf(int sel);		



#ifdef _WIN32
	#include "Windows.h"
    #include "conio.h"
	void clr_scr();
	void set_cursor_pos(int xPos, int yPos);
	
#else

    #include <sys/select.h>
    #include <termios.h>
    #include "sys/ioctl.h"
    #include "unistd.h"
    #include "stdio_ext.h"

	void set_cursor_pos(int xPos, int yPos);
	#define clr_scr() printf("\e[1;1H\e[2J");	
	int _kbhit();

#endif