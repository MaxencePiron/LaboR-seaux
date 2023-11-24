#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
 
static struct termios old, new;
 
//clrscr() function definition
// #include <stdlib.h>
void ClrScr(void)
{
    system("clear");
}

void Gotoxy(int x,int y)    
{
    printf("%c[%d;%df",0x1B,y,x);
}

/* Initialize new terminal i/o settings */
// #include <stdio.h>
// #include <stdlib.h>

void initTermios(int echo) 
{
  tcgetattr(0, &old); //grab old terminal i/o settings
  new = old; //make new settings same as old settings
  new.c_lflag &= ~ICANON; //disable buffered i/o
  new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &new); //apply terminal io settings
}
 
/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}
 
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
char Getch(void) 
{
  return getch_(0);
}
 
/* 
Read 1 character with echo 
getche() function definition.
*/
char GetchE(void) 
{
  return getch_(1);
}

char Gets(char *Resultat)
{
  char ch ;
  int i ;
  i = 0 ;
  ch = GetchE() ; 
  while( ch != '\n')
  {
   Resultat[i]=ch ;
   i++ ;
   ch = GetchE() ;
  }
  Resultat[i]=0 ;
}

 
int main(void) {
  char c;
  int y ;
  char Chaine[30] ;
  ClrScr() ;
  printf("(GetchE example) Please enter a character: ");
  c = GetchE();
  printf("\nYou entered: %c\n", c);
  printf("(Getch example) Please enter a character: ");
  c = Getch();
  printf("\nYou entered: %c\n", c);
  printf("Gets example) Please enter a String: ");
  Gets(Chaine);
  printf("\n you entered:%s:",Chaine) ;

  for ( int i = 8 ; i <=16 ; i++)
  {
   Gotoxy(10, i) ;
   printf("essai %d:",i) ;
  }
  Gotoxy(1,20) ;
  return 0;
}