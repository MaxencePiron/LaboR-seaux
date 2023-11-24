
#include<stdlib.h>
#include <termios.h>
#include<stdio.h>

void gotoxy(int x,int y)
{
printf("%c[%d;%df",0x1B,y,x);
}

void clrscr(void)
{
    system("clear");
}

static struct termios old, new;

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}
 
/* 
Read 1 character without echo 
getch() function definition.
*/
char getch(void) 
{
  return getch_(0);
}
 
/* 
Read 1 character with echo 
getche() function definition.
*/
char getche(void) 
{
  return getch_(1);
}

int main()
{
  char c ;
  clrsc() ;
  gotoxy(24,25); //reposition cursor
  printf("hello world"); //display text
  gotoxy(1,48); // reposition cursor

  printf("(getche example) Please enter a character: ");
  c = getche();
  printf("\nYou entered: %c\n", c);
  printf("(getch example) Please enter a character: ");
  c = getch();
  printf("\nYou entered: %c\n", c);
  return(0) ;
} 


