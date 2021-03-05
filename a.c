


#include "stdio.h"

#include "Windows.h"

    void virt_terminal_enable()
    {
        HANDLE h_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE h_std_in = GetStdHandle(STD_INPUT_HANDLE);
        
        DWORD mode = 0;

        GetConsoleMode(h_std_out, &mode);

        mode |=  (ENABLE_VIRTUAL_TERMINAL_PROCESSING); 
        SetConsoleMode(h_std_out, mode);
    
        GetConsoleMode(h_std_in, &mode);
        mode |= (ENABLE_VIRTUAL_TERMINAL_INPUT);
        SetConsoleMode(h_std_in, mode);

    }   

int main()
{
	virt_terminal_enable();
	printf("%s\n", "asdsdassahdaisduisduaiosdhuiasdhasidhyasy");	
	sleep(3);
	printf("\e[1;1H\e[2J");

}