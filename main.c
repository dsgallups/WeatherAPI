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
char* fetchAPI();

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


  //perform action


  //store the user's action
  int option = 0;
  char zip[] =  "_____";
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
      "go - Executes the displayed configurations.\n"
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
    if (strspn(command, "0123456789") == 5 && strlen(command) == 5) {
      printf("in here\n");
      
      //this is sticky. I just want zip to take in command's value
      //zip = command;
      printf("%lu\n", sizeof(zip));
      strncpy(zip, command, 5);
      printf("%s", zip);

    }

    if (strstr(command, "go")) {
      char* result = fetchAPI(curl, zip, option);
    }

    //if user hits enter with no input
    if (strlen(command) == 0)
    printf("%s\n%lu\n", command, strlen(command));
  }
  return 0;
}

char* fetchAPI(CURL *curl, char* zip, int option) {
  /*
    To use the openweather api, we have to convert our zip code into a lat long coordinate system.
    We can do this via google's api
  */
  char* googleAPIKey = "&key=AIzaSyCOlNBG5t9nUor7R4UjrFvUcwnd9EzNIFI";
  char googleURL[1024];
  strcpy(googleURL, "https://maps.googleapis.com/maps/api/geocode/json?address=");
  strcat(googleURL, zip);
  strcat(googleURL, googleAPIKey);
  printf("submitted url:%s\n", googleURL);

  /*
    grab the lat and long at:
    results[0].geometry.location.lat
    results[0].geometry.location.lng
  */
  curl_easy_setopt(curl, CURLOPT_URL, googleURL);

  CURLcode result = curl_easy_perform(curl);
  if (result != CURLE_OK) {
    fprintf(stderr, "download problem: %s\n", curl_easy_strerror(result));

  }








  //set options
  /*
  char* API_KEY = "&appid=a3ecd4b0cfeef827dfd555ab2a365fd1";

  char url[512];
  if (option == 0) {
    strcpy(url, "https://api.openweathermap.org/data/2.5/onecall?zip=");
    strcat(url, zip);
    strcat(url, API_KEY);
    strcat(url, "&cnt=7&units=imperial");
  } else if (option == 1) {
    strcpy(url, "pro.openweathermap.org/data/2.5/forecast/hourly?zip=");
    strcat(url, zip);
    strcat(url, API_KEY);
    strcat(url, "&cnt=7&units=imperial");
  }

  curl_easy_setopt(curl, CURLOPT_URL, url);

  CURLcode result = curl_easy_perform(curl);
  if (result != CURLE_OK) {
    fprintf(stderr, "download problem: %s\n", curl_easy_strerror(result));

  }
  */
  curl_easy_cleanup(curl);
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