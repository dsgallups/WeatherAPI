#include <stdlib.h>
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

/*
  To add curl to visual studio, install vcpkg here: 
  https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=msvc-160
  
  Then, follow the instructions under "Building using vcpkg" at
  https://curl.se/docs/install.html

  Then, reload vscode


  #######
  To compile, do
  gcc main.c -lcurl
*/

#define OFFSET 48 //for numbers
void drawMenu();

/*
  the problem is that inputs are typically buffered, so it's very hard to get a keypres

*/
int main() {
  int running = 1;
  CURL *curl = curl_easy_init();

  if (!curl) {
    fprintf(stderr, "init failed\n");
    return 0;
  }

  curl_easy_cleanup(curl);

  //set options
  char* API_KEY = "45223ea54f34186ce02503668baf1306";
  char* url = "api.openweathermap.org/data/2.5/forecast/daily?zip=";

  //curl_easy_setopt(curl, CURLOPT_URL, "");

  //perform action


  //store the user's action
  int option = 0;
  char* zip = "_____";
  while (running) {
    printf("test\n");
    drawMenu(zip, option);

    printf("For help, type \"help\".\n> ");
    COM: ;
    char command[20];
    scanf("%s", command);
    
    if (strstr(command, "help")) {
      char* help =
      "To use this program, the following tokens are valid:\n"
      "\"help\" - Displays this dialog\n"
      "Numbers - Inserts the numbers into zipcode. To overwrite the zipcode, type in new numbers.\n"
      "w - Moves the cursor up.\n"
      "s - Moves the cursor down.\n"
      "enter (no other input) - Executes the displayed configurations.\n"
      "exit - exits the program.\n";
      printf("%s", help);
      goto COM;
    }
    if (strstr(command, "exit")) {
      running = 0;
    }
    if (strcmp(command, "w") == 0) {
      option = 0;
    }
    if (strcmp(command, "s") == 0) {
      option = 1;
    }
    printf("%s", command);
  }
  return 0;
}


void drawMenu(char* zip, int option) {

    char menu[1807];
    char* menu0 = 
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
    "#                                  Enter Zipcode:                                   #\n";
    
    strcat(menu, menu0);
    char zipm[86];
    zipm[0] = '\0';
    strcat(zipm, "#                                      ");
    strcat(zipm, zip);
    strcat(zipm, "                                        #\n");

    char* options =
    "#                                                                                   #\n"
    "#                                                                                   #\n"
    "#                              Options (* is selected):                             #\n"
    "#                                                                                   #\n"
    "#                                  7 day forecast*                                  #\n"
    "#                                  1 day forecast                                   #\n"
    "#                                                                                   #\n"
    "#                                                                                   #\n"
    "#####################################################################################\n";

    if (option == 0) {
      options =
    "#                                                                                   #\n"
    "#                                                                                   #\n"
    "#                              Options (* is selected):                             #\n"
    "#                                                                                   #\n"
    "#                                  7 day forecast*                                  #\n"
    "#                                  1 day forecast                                   #\n"
    "#                                                                                   #\n"
    "#                                                                                   #\n"
    "#####################################################################################\n";
    } else if (option == 1) {
       options =
    "#                                                                                   #\n"
    "#                                                                                   #\n"
    "#                              Options (* is selected):                             #\n"
    "#                                                                                   #\n"
    "#                                  7 day forecast                                   #\n"
    "#                                  1 day forecast*                                  #\n"
    "#                                                                                   #\n"
    "#                                                                                   #\n"
    "#####################################################################################\n";     
    }

    strcat(menu, zipm);
    strcat(menu, options);
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