#include <stdio.h>

void myflush ( FILE *in )
{
  int ch;

  do
    ch = fgetc ( in ); 
  while ( ch != EOF && ch != '\n' ); 

  clearerr ( in );
}

void mypause ( void ) 
{ 
  printf ( "Press [Enter] to continue . . ." );
  fflush ( stdout );
  getchar();
} 

int main ( void )
{
  int number;

  // Test with an empty stream
  printf ( "Hello, world!\n" );
  mypause();

  // Leave extra input in the stream
  printf ( "Enter more than one character" );

  myflush ( stdin );
  mypause();

  return 0;
}