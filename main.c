#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "list.h"
#include "time.h"
#include "os.h" 


#define FIELD_WIDTH 80
#define FIELD_HEIGHT 15

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define START_DIRECTION UP
#define START_SIZE 5

#define START_X_COORD 5
#define START_Y_COORD 5

#define WALL '@'
#define HEAD '0'
#define BODY '#'
#define FRUIT '$'

struct coords
{
    int x;
    int y;
};

struct snake
{
    struct list *info_turn;

    struct coords head_coords;
    struct coords tail_coords;

    int direction;
    int score;

    int speed;
};


void init()
{
    clr_scr();
    line_buf(0);
}


void quit()
{
    clr_scr();
    line_buf(1);
}


static int fruit_x, fruit_y;


void put_char_at_pos(struct coords *crds, char ch)
{
    set_cursor_pos(crds->x, crds->y);
    putchar(ch);    
}

void set_coords(struct coords *crds, int x, int y)
{
    crds->x = x;
    crds->y = y;
}

void draw_field()
{

    for(int i = 0; i < FIELD_HEIGHT; i++)
    {
        set_cursor_pos(0, i);
        putchar(WALL);
        set_cursor_pos(FIELD_WIDTH, i);
        putchar(WALL);
    }   

    for(int i = 0; i < FIELD_WIDTH; i++)
    {
        set_cursor_pos(i, 0);
        putchar(WALL);
        set_cursor_pos(i, FIELD_HEIGHT);
        putchar(WALL);
    }   

}


void init_snake(struct snake *snk)
{   

    struct node *start_info = malloc(sizeof(struct node));
    
    snk->info_turn = malloc(sizeof(struct list));
    snk->info_turn->first = snk->info_turn->last = NULL;
    start_info->values = (int *)malloc(sizeof(int) * 2);
    
    snk->score = 0;
    snk->speed = 500;


    start_info->values[0] = START_DIRECTION;
    start_info->values[1] = START_SIZE;

    insert_end(snk->info_turn, start_info);

    snk->direction = START_DIRECTION;
    set_coords(&snk->head_coords, START_X_COORD, START_Y_COORD);

    int add_x = 0;
    int add_y = 0;
    switch(snk->direction)
    {
        case UP:
        add_y = (START_SIZE);
        break;

        case DOWN:
        add_y = 0-(START_SIZE);
        break;

        case LEFT:
        add_x = (START_SIZE);
        break;

        case RIGHT:
        add_x = 0-(START_SIZE);
        break;
    }
    set_coords(&snk->tail_coords, START_X_COORD + add_x, START_Y_COORD + add_y);
}



void display_info(struct snake *snk)
{
    set_cursor_pos(5, 17);
    printf("%s%d", "&first = ", snk->info_turn->first);
    set_cursor_pos(5, 18);
    printf("%s%d", "&last = ", snk->info_turn->last);

    set_cursor_pos(5, 20);
    printf("%s%d", "first->values[0] = ", snk->info_turn->first->values[0]);
    set_cursor_pos(5, 21);
    printf("%s%d", "first->values[1] = ", snk->info_turn->first->values[1]);

    set_cursor_pos(5, 23);
    printf("%s%d", "last->values[0] = ", snk->info_turn->last->values[0]);
    set_cursor_pos(5, 24);
    printf("%s%d", "last->values[1] = ", snk->info_turn->last->values[1]);

    set_cursor_pos(5, 26);
    printf("%s%d", "&values[0] = ", &snk->info_turn->last->values[0]);
    set_cursor_pos(5, 27);
    printf("%s%d", "&values[1] = ", &snk->info_turn->last->values[1]);

    set_cursor_pos(5, 28);
    printf("%s%d", "speed", snk->speed);


}



void draw_snake(struct snake *snk)
{

    int add_x = 0;
    int add_y = 0;

    switch(snk->info_turn->first->values[0])
    {
        case UP: 
        add_y = -1;
        add_x = 0;
        break;

        case DOWN: 
        add_y = 1;
        add_x = 0;
        break;
        
        case LEFT: 
        add_y = 0;
        add_x = -1;
        break;

        case RIGHT: 
        add_y = 0;
        add_x = 1;
        break;

    }
    snk->head_coords.x += add_x;
    snk->head_coords.y += add_y;

    put_char_at_pos(&snk->head_coords, HEAD);


    snk->info_turn->first->values[1]++;
    snk->info_turn->last->values[1]--;



    put_char_at_pos(&snk->tail_coords, ' ');


    switch(snk->info_turn->last->values[0])
    {
        case UP: 
        add_y = -1;
        add_x = 0;
        break;

        case DOWN: 
        add_y = 1;
        add_x = 0;
        break;
        
        case LEFT: 
        add_y = 0;
        add_x = -1;
        break;

        case RIGHT: 
        add_y = 0;
        add_x = 1;
        break;
    }

    snk->tail_coords.x += add_x;
    snk->tail_coords.y += add_y;


    struct coords crds;
    crds.x = snk->tail_coords.x;
    crds.y = snk->tail_coords.y;

    struct node *current = snk->info_turn->last;

    while(current)
    {
        switch(current->values[0])
        {
            case UP: 
            add_y = -1;
            add_x = 0;
            break;

            case DOWN: 
            add_y = 1;
            add_x = 0;
            break;
            
            case LEFT: 
            add_y = 0;
            add_x = -1;
            break;

            case RIGHT: 
            add_y = 0;
            add_x = 1;
            break;
        }

        for(int i = 0; i < current->values[1]; i++)
        {
            set_cursor_pos(crds.x, crds.y);
            putchar(BODY);

            crds.x += add_x;
            crds.y += add_y;

                      
        }
    
        current = current->prev;  
    
    }

    
    if(snk->info_turn->first != snk->info_turn->last)
    {
        if(snk->info_turn->last->values[1] == 0) 
        {
            snk->info_turn->last = snk->info_turn->last->prev;
        }
    }
}

int process_input(struct snake *snk)
{

    int ch = 0;
    struct node *nd = NULL;

    while(_kbhit())
    {
        ch = getchar();
    }

    if(ch)
    {
        switch(ch)
        {
            case 'w':
            if(snk->direction != DOWN)
            {
                snk->direction = UP;
                nd = malloc(sizeof(struct node));
                nd->values = malloc(sizeof(int) * 2);
                nd->values[0] = UP;
                nd->values[1] = 0;
                insert_beginning(snk->info_turn, nd);
            }
            break;
        
            case 's':
            if(snk->direction != UP)
            {
                snk->direction = DOWN;
                nd = malloc(sizeof(struct node));
                nd->values = malloc(sizeof(int) * 2);
                nd->values[0] = DOWN;
                nd->values[1] = 0;
                insert_beginning(snk->info_turn, nd);
            }
            break;

            case 'd':
            if(snk->direction != LEFT)
            {
                snk->direction = RIGHT;
                nd = malloc(sizeof(struct node));
                nd->values = malloc(sizeof(int) * 2);
                nd->values[0] = RIGHT;
                nd->values[1] = 0;
                insert_beginning(snk->info_turn, nd);
            }
            break;

            case 'a':
            if(snk->direction != RIGHT)
            {
                snk->direction = LEFT;
                nd = malloc(sizeof(struct node));
                nd->values = malloc(sizeof(int) * 2);
                nd->values[0] = LEFT;
                nd->values[1] = 0;
                insert_beginning(snk->info_turn, nd);

            }
            break;

            case 'q': 
            return 1;


        }
    }

    return 0;
}


struct node *create_node(int val1, int val2)
{
    struct node *nd = malloc(sizeof(struct node));
    nd->values = malloc(sizeof(int) * 2);
    nd->values[0] = val1;
    nd->values[1] = val2;
    nd->next = nd->prev = NULL;
    return nd;
}


void wait(int msec_to_wait)
{
    int msec = 0, trigger = msec_to_wait;
    clock_t before = clock();

    do
    {
        clock_t difference  = clock() - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;

    }while(msec < trigger);


}

int get_random_int(int min, int max)
{
    srand(time(0));
    static int r = 0;

    int tmp = 0;
    do
    {   
        tmp = (rand() % (max - min + 1)) + min;
        
    }while(tmp == r);

    r = tmp;
    return r;
}



void place_fruit()
{
    fruit_x = get_random_int(5, FIELD_WIDTH - 10);
    fruit_y = get_random_int(5, FIELD_HEIGHT - 10);
    set_cursor_pos(fruit_x, fruit_y);
    putchar(FRUIT);
}

void eat(struct snake *snk)
{
    int add_x = 0;
    int add_y = 0;

    switch(snk->info_turn->last->values[0])
    {
        case UP: 
            add_y--;
            add_x = 0;
            break;
        case DOWN:
            add_y++;
            add_x = 0;
            break;
        case LEFT:
            add_x--;
            add_y = 0;
            break;
        case RIGHT:
            add_x++;
            add_y = 0;
            break;
    }

    if(snk->head_coords.x == fruit_x && snk->head_coords.y == fruit_y)
    {
        snk->tail_coords.x += 0 - (add_x);
        snk->tail_coords.y += 0 - (add_y);

        snk->score++;
        snk->info_turn->last->values[1]++;
            
        // snk->speed-=20;

        place_fruit();    
    }
    
}

int wall_hit(struct snake *snk)
{
    int head_x = snk->head_coords.x;
    int head_y = snk->head_coords.y;

    int ret_value = 0;

    if(head_x < 1 || head_x > (FIELD_WIDTH - 1)) ret_value = 1;
    if(head_y < 1 || head_y > (FIELD_HEIGHT - 1)) ret_value = 1;
    return ret_value;
}

int main()
{

    init();
    struct snake snk;
    init_snake(&snk);

    draw_field();

    place_fruit();
    int exit = 0;

    while(!exit)
    {
        fflush(stdout);
        eat(&snk);
        draw_snake(&snk);
        display_info(&snk);
        exit = process_input(&snk);
        exit = wall_hit(&snk);
        wait(50);  
    } 

    quit();


}