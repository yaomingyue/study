#include <unistd.h>

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <time.h>

#include <sys/time.h>

#include <curses.h>

#include <pthread.h>

#include <semaphore.h>

#include <signal.h>

void *checkkey (void *arg);

void *changekey (void *arg);

void *isover (void *arg);

WINDOW *a_win,*b_win,*c_win;

pthread_t main_tid;

sem_t sem_one,sem_two;

int location,hit=0,n=400000,FLAG=1,hited_num=0,typed_num=0;

void contin ()

{

        touchwin(a_win);wrefresh(a_win);

}

void paus ()

{

        touchwin(b_win);wrefresh(b_win);

        pause();

}

void game_over ()

{

        touchwin(c_win);wrefresh(c_win);

        pause();

        FLAG=0;

        return;

}

void stop (int usec)

{

        struct timeval tv;

        tv.tv_sec=0;

        tv.tv_usec=usec;

        select(0,NULL,NULL,NULL,&tv);

}

int main ()

{

    //int i,j,res,s=0,randnum;

        struct sigaction to_pause,to_continue,to_over;

        initscr();

        noecho();cbreak();keypad(stdscr,TRUE);curs_set(0);

        char *darwscr=(char *)malloc((LINES-2)*(COLS-16));

        if(darwscr==NULL)

        {

                perror("Malloc Failure");endwin();exit(1);

        }

        pthread_t new_one,new_two;

        WINDOW *topwin,*pausewin,*overwin,*numwin;

        topwin=newwin(LINES-2,COLS-16,0,8);

        pausewin=newwin(1,COLS/2,LINES/2,COLS/4);

        overwin=newwin(3,COLS/2,LINES/2+1,COLS/4);

        numwin=newwin(1,9,LINES-1,COLS/2+18);

        if(topwin==NULL || pausewin==NULL || overwin==NULL || numwin==NULL)

        {

                perror("Create window Failure");endwin();exit(1);

        }

        a_win=topwin;b_win=pausewin;c_win=overwin;

        if(!has_colors())

        {

                perror("Devices not support colors");

                delwin(topwin);delwin(pausewin);delwin(overwin);

                delwin(numwin);endwin();exit(1);

        }

        if(start_color()!=OK)

        {

                perror("Initialize Colors Failure");

                delwin(topwin);delwin(pausewin);delwin(overwin);

                delwin(numwin);endwin();exit(1);

        }

        init_pair(1,4,4);init_pair(2,7,4);

        init_pair(3,1,1);init_pair(4,7,1);

        clear();

        for(i=0;i<LINES;i++)

        {

                move(i,7);vline(0,1);

                move(i,COLS-7);vline(0,1);

        }

        wattron(stdscr,COLOR_PAIR(1));

        for(i=0;i<COLS;i++) mvwaddch(stdscr,LINES-1,i,'a');

        wattroff(stdscr,COLOR_PAIR(1));

        wattron(stdscr,COLOR_PAIR(2));

        mvwprintw(stdscr,LINES-1,(COLS-30)/2,"%s","Press '1' to PAUSE,'2' to QUIT");

        wattroff(stdscr,COLOR_PAIR(2));

        wattron(numwin,COLOR_PAIR(2));

        refresh();

        mvwprintw(numwin,0,0,"[%3d/%-3d]",hited_num,typed_num);

        wrefresh(numwin);

        wattron(pausewin,COLOR_PAIR(1));

        for(i=0;i<COLS/2;i++) mvwaddch(pausewin,0,i,'a');

        wattroff(pausewin,COLOR_PAIR(1));

        wattron(pausewin,COLOR_PAIR(2));

        mvwprintw(pausewin,0,2,"%s","Press 'CTRL-C' to Continue.");

        wattroff(pausewin,COLOR_PAIR(2));

        wattron(overwin,COLOR_PAIR(3));

        for(i=0;i<3;i++)

        {

                for(j=0;j<COLS/2;j++) mvwaddch(overwin,i,j,'a');

        }

        wattroff(overwin,COLOR_PAIR(3));

        wattron(overwin,COLOR_PAIR(4));

        mvwprintw(overwin,1,COLS/4-4,"%s","GAME OVER");

        mvwprintw(overwin,2,COLS/4-8,"%s","'CTRL-C' to QUIT");

        wattroff(overwin,COLOR_PAIR(4));

        memset(darwscr,'\0',sizeof(darwscr));

        to_pause.sa_handler=paus;

        sigemptyset(&to_pause.sa_mask);

        to_pause.sa_flags=0;

        sigaction(SIGUSR1,&to_pause,0);

        to_continue.sa_handler=contin;

        sigemptyset(&to_continue.sa_mask);

        to_continue.sa_flags=0;

        sigaction(SIGINT,&to_continue,0);

        to_over.sa_handler=game_over;

        sigemptyset(&to_over.sa_mask);

        to_over.sa_flags=0;

        sigaction(SIGUSR2,&to_over,0);

        main_tid=pthread_self();

        res=pthread_create(&new_one,NULL,checkkey,(void *)darwscr);

        res=pthread_create(&new_two,NULL,changekey,(void *)darwscr);

        if(res!=0)

        {

                perror("Thread Create Failure");

                delwin(topwin);delwin(pausewin);delwin(overwin);

                delwin(numwin);endwin();exit(1);

        }

        res=sem_init(&sem_one,0,0);

        res=sem_init(&sem_two,0,0);

        if(res!=0)

        {

                perror("Semaphore Initialize Failure");

                delwin(topwin);delwin(pausewin);delwin(overwin);

                delwin(numwin);endwin();exit(1);

        }

        s=(int)time(NULL);

        while(FLAG)

        {

                s+=n/1000;

                srand(s);

                for(i=0;i<COLS-16;i++)

                {

                        randnum=(int)(rand()/(double)RAND_MAX*1000);

                        if(randnum<994)  *(darwscr+i)=' ';

                        else

                        {

                                randnum=(int)(rand()/(double)RAND_MAX*(123-97)+97);

                                *(darwscr+i)=(char)randnum;

                        }

                }

                for(i=0;i<LINES-2;i++)

                        mvwaddstr(topwin,i,0,darwscr+i*(COLS-16));

                wrefresh(topwin);

                sem_post(&sem_one);

                sem_wait(&sem_two);

                memmove(darwscr+COLS-16,darwscr,(LINES-3)*(COLS-16));

                mvwprintw(numwin,0,0,"[%3d/%-3d]",hited_num,typed_num);

                wrefresh(numwin);

        }

        free(darwscr);sem_destroy(&sem_one);sem_destroy(&sem_two);

        delwin(topwin);delwin(pausewin);delwin(numwin);

        delwin(overwin);endwin();exit(0);

}

void *checkkey (void *arg)

{

        int i,key;

        char *p=(char *)arg;

        while(1)

        {

                key=getch();

                ++typed_num;

                if(key=='1') pthread_kill(main_tid,SIGUSR1);

                else if(key=='2') FLAG=0;

                else if(key>='a' && key<='z') 

                {

                        for(i=(LINES-2)*(COLS-16)-1;i>=0;i--)

                        {

                                if(*(p+i)==key) 

                                {

                                        location=i;

                                        hit=1;

                                        ++hited_num;

                                        break;

                                }

                        }

                }

        }

}

void *changekey (void *arg)

{

        const char *space=" ";

        const char *over="@";

        char *p=(char *)arg;

        int last_location=0,times=0,m;

        while(1)

        {

                sem_wait(&sem_one);

                ++times;

                if(times<30) n=400000;

                else if(times>=30 && times <60) n=350000;

                else if(times>=60 && times<100) n=300000;

                else if(times>=100 && times<160) n=250000;

                else if(times>=160 && times <220) n=200000;

                else n=150000;

                stop(n);

                if(last_location) memcpy(p+last_location,space,1);

                last_location=0;

                if(hit) 

                {

                        memcpy(p+location,over,1);

                        last_location=location+COLS-16;

                }

                for(m=(LINES-2)*(COLS-16)-1;m>(LINES-3)*(COLS-16);m--)

                {

                        if(*(p+m)>='a' && *(p+m)<='z')

                                pthread_kill(main_tid,SIGUSR2);

                }

                sem_post(&sem_two);

                hit=0;

        }

}
