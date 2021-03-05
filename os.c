

#include "os.h"

//For Windows
#ifdef _WIN32


    void set_cursor_pos(int xPos, int yPos)
    {
        HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD dwCursorPos;
        dwCursorPos.X = xPos;
        dwCursorPos.Y = yPos;

        SetConsoleCursorPosition(hConsoleOutput, dwCursorPos);
    }


    void clr_scr()
    {
        HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);

        COORD screen_coord = {0, 0};
        DWORD chars_written;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD con_size;

        GetConsoleScreenBufferInfo(h_out, &csbi);
        con_size = csbi.dwSize.X * csbi.dwSize.Y;

        FillConsoleOutputCharacter(h_out, ' ', con_size, screen_coord, &chars_written);

        GetConsoleScreenBufferInfo(h_out, &csbi);
        
        FillConsoleOutputAttribute(h_out, csbi.wAttributes, con_size, screen_coord, &chars_written);
    }


    //disable line buffering if sel == 0, otherwise enable
    void line_buf(int sel)
    {
        HANDLE h_std_in = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode = 0;

        GetConsoleMode(h_std_in, &mode);

        if(sel)
        {
            mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
        }
        else mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
        SetConsoleMode(h_std_in, mode);            
    
    }



//For unix-likes
#else


    void set_cursor_pos(int xPos, int yPos)
    {
        printf("\033[%d;%dH", yPos+1, xPos+1);
    }

    void line_buf(int sel)
    {

        struct termios term;
        tcgetattr(STDIN_FILENO, &term);
        
        if(sel)
        {
            term.c_lflag |= ICANON;   
            term.c_lflag |= ECHO;        
        }
        else
        {
            term.c_lflag &= ~ICANON;
            term.c_lflag &= ~ECHO;    
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &term);
        setbuf(stdin, NULL);
    }



    int _kbhit()
    {
        const static int STDIN = 0;
        int bytesWaiting;
        struct timeval timeout;
        fd_set rdset;

        FD_ZERO(&rdset);
        FD_SET(STDIN, &rdset);
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        return select(STDIN + 1, &rdset, NULL, NULL, &timeout);
    }


#endif















