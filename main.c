#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#define OFFSET 48 //for numbers
void drawMenu();

/*
  the problem is that inputs are typically buffered, so it's very hard to get a keypres

*/
int main() {
  int frameCount = 0;
  int running = 1;
  char no[5];
  while (running) {
    drawMenu();
    char* commands = "Since all command line inputs are buffered on Unix systems, please issue commands and press enter to update the screen.\n"
    "To execute the current screen's configuration, just press enter:\n";
    char c;

    while (c = getchar() != EOF && c != 10) {
      printf("frame = %d\n", frameCount++);
      if (c >= OFFSET && c <= OFFSET + 9) {
        strcat(no, &c);
      }
    } 
    printf("no = %s\n", no);
  }



  return 0;
}


void drawMenu() {

    
    char* menu = 
    "#####################################################################################\n"
    "#                                                                                   #\n"
    "# (_)(_)(_|_______|_______|_______|_)   (_|_______|_____ \\   (_____ (___) (_______) #\n"
    "#  _  _  _ _____   _______    _    _______ _____   _____) )   _____) ) _   ______   #\n"
    "# | || || |  ___) |  ___  |  | |  |  ___  |  ___) |  __  /   (_____ ( | | (_____ \\  #\n"
    "# | || || | |_____| |   | |  | |  | |   | | |_____| |  \\ \\    _____) )| |_ _____) ) #\n"
    "#  \\_____/|_______)_|   |_|  |_|  |_|   |_|_______)_|   |_|  (______(_____|______/  #\n"
    "#                                                                                   #\n"
    "#                                                                                   #\n"
    "#                                                                                   #\n"
    "#                                  Enter Zipcode:                                   #\n"
    "#                                      _____                                        #\n"
    "#                                                                                   #\n"
    "#                                                                                   #\n"
    "#                              Options (* is selected):                             #\n"
    "#                                                                                   #\n"
    "#                                  7 day forecast*                                  #\n"
    "#                                  1 day forecast                                   #\n"
    "#                                       exit                                        #\n"
    "#                                                                                   #\n"
    "#####################################################################################\n";
    printf("%s", menu);

    /*
    while (1) {
      //char e = getchar();
      printf("%d\n", getchar());
    }*/

    //s = 115
    //w = 119
    //0 = 48
    //4 = 52...
    //9 = 
}