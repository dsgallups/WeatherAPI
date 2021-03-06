#include <stdlib.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <stdio.h>
#include <string.h>

/*
  Written and compiled on Ubuntu 16.04 LTS



  To add curl to visual studio, install vcpkg here: 
  https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=msvc-160
  
  Then, follow the instructions under "Building using vcpkg" at
  Then, reload vscode

  If that doesn't work,
  sudo apt-get install libcurl4-openssl-dev

  As for json-c, json-c is found here:
  https://github.com/json-c/json-c

  Follow instructions labeled "Building on Unix with git, gcc, and cmake"
  alternatively, just use vcpkg and install via command:
  vcpkg install json-c
  

  #######
  To compile, do
  gcc main.c -lcurl -ljson-c
*/

struct memory {
  char *memory;
  size_t size;
};

void drawMenu();
void drawData();
char* fetchAPI();
char* spaceMaker();
size_t writeCallback();

int main() {
  int running = 1;
    
      
  //store the user's action in option
  int option = 0;

  //holder for our zip code
  char zip[] =  "_____";
  while (running) {
    system("clear");
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
      
      //janky but I'd prefer the user to not see the menu drawn again.
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
      
      //give zip the value of command
      strncpy(zip, command, 5);

    }

    if (strstr(command, "go")) {
      char* result = fetchAPI(zip, option);
      system("clear");
      drawData(result, option);

      //if a user types anything, it will exit. I know I said type 'exit' to exit, but this is more user friendly.
      char dump[60];
      scanf("%s", dump);
    }

  }
  return 0;
}

//Returns white space. Helpful for building the menu.
char* spaceMaker(int length) {
  char *str = malloc(length + 1);
  memset(str, ' ', length);
  str[length] = 0;
  return str;
}

void drawData(char* data, int option) {
  if (option == 0) {
    //Template

    /*
    frames[8] =
    "#####################################################################################\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# Today, May 2    | High: 75f  | Low: 63f  | Weather: Thunderstorms                 #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# May 3           | High: 79f  | Low: 48f  | Weather: Windy                         #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# May 4           | High: 69f  | Low: 39f  | Weather: Cloudy                        #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# May 5           | High: 68f  | Low: 45f  | Weather: Cloudy                        #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# May 6           | High: 72f  | Low: 50f  | Weather: Clear                         #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# May 7           | High: 75f  | Low: 61f  | Weather: Clear                         #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# May 8           | High: 73f  | Low: 64f  | Weather: Windy                         #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "#                                                                                   #\n"
    "#                                                                                   #\n"
    "#                                       Exit*                                       #\n"
    "#                                                                                   #\n"
    "#####################################################################################\n";
    */
    struct json_object *parsed_json;
    parsed_json = json_tokener_parse(data);
    struct json_object *days;
    json_object_object_get_ex(parsed_json, "daily", &days);
    //We just need to get the high and lows and weather, located at
    //daily[i].temp.min
    //daily[i].temp.max
    //daily[i].weather[0].main

    //All these variables are necessary to decrease the scope of each JSON value.
    struct json_object *day;
    struct json_object *temp;
    struct json_object *min;
    struct json_object *max;
    struct json_object *weather;
    struct json_object *weatheri;
    struct json_object *weatherval;

    char render[2000];
    strcpy(render, "#####################################################################################\n");
    for (int i = 0; i < 8; i++) {
      strcat(render, "#-----------------------------------------------------------------------------------#\n");
      day = json_object_array_get_idx(days, i);
      json_object_object_get_ex(day, "temp", &temp);
      json_object_object_get_ex(temp, "min", &min);
      json_object_object_get_ex(temp, "max", &max);

      json_object_object_get_ex(day, "weather", &weather);
      weatheri = json_object_array_get_idx(weather, 0);
      json_object_object_get_ex(weatheri, "main", &weatherval);
      const char* minVal = json_object_get_string(min);
      const char* maxVal = json_object_get_string(max);
      const char* wVal = json_object_get_string(weatherval);


      char line[200];
      strcpy(line, "# ");
      char dayval[10];
      if (i == 0) {
        strcpy(dayval, "Today");
      } else if (i == 1) {
        strcpy(dayval, "Tomorrow");
      } else {
        strcpy(dayval, "Day ");
        char buffer[2];
        sprintf(buffer, "%d", (i+1));
        strcat(dayval, buffer);
      }
      sprintf(line, "# %s %s| High: %.2sf | Low %.2sf | Weather: %s %s #\n", dayval, spaceMaker(12-strlen(dayval)), maxVal, minVal, wVal, spaceMaker(34-strlen(wVal)));
      strcat(render, line);

      

    }

    char* bottom = 
    "#-----------------------------------------------------------------------------------#\n"
    "#                                                                                   #\n"
    "#                                                                                   #\n"
    "#                              Type 'exit' to exit                                  #\n"
    "#                                                                                   #\n"
    "#####################################################################################\n";
    strcat(render, bottom);

    printf("%s", render);
  } else if (option == 1) {
    /*
    "#####################################################################################\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# Now, 12pm     | High: 75f  | Low: 63f  | Weather: Thunderstorms                   #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# 3pm           | High: 79f  | Low: 48f  | Weather: Windy                           #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# 6pm           | High: 69f  | Low: 39f  | Weather: Cloudy                          #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# 9pm           | High: 68f  | Low: 45f  | Weather: Cloudy                          #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# Tomorrow, 12am| High: 72f  | Low: 50f  | Weather: Clear                           #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# 3am           | High: 75f  | Low: 61f  | Weather: Clear                           #\n"
    "#-----------------------------------------------------------------------------------#\n"
    "# Additional details:                                                               #\n"
    "#  Sunrise: 7:14am                                                                  #\n"
    "#  Sunset: 7:51pm                                                                   #\n"
    "#  Humidity: 97                                                                     #\n"
    "#  Visibility: 10000                                                                #\n"
    "#                                       Exit*                                       #\n"
    "#####################################################################################\n";
    */
    struct json_object *parsed_json;
    parsed_json = json_tokener_parse(data);
    struct json_object *current;
    struct json_object *sunrise;
    struct json_object *sunset;
    struct json_object *humidity;
    struct json_object *visibility;
    json_object_object_get_ex(parsed_json, "current", &current);
    json_object_object_get_ex(current, "sunrise", &sunrise);
    json_object_object_get_ex(current, "sunset", &sunset);
    json_object_object_get_ex(current, "humidity", &humidity);
    json_object_object_get_ex(current, "visibility", &visibility);

    char render[2000];
    strcpy(render, "#####################################################################################\n");
    
    struct json_object *hours;
    struct json_object *hour;
    struct json_object *temp;
    struct json_object *weatherarr;
    struct json_object *weatheri;
    struct json_object *weatherval;
    for (int i = 0; i <= 15; i += 3) {
      json_object_object_get_ex(parsed_json, "hourly", &hours);
      hour = json_object_array_get_idx(hours, i);
      json_object_object_get_ex(hour, "temp", &temp);
      json_object_object_get_ex(hour, "weather", &weatherarr);
      weatheri = json_object_array_get_idx(weatherarr, 0);
      json_object_object_get_ex(weatheri, "main", &weatherval);

      strcat(render, "#-----------------------------------------------------------------------------------#\n");
      char line[90];

      sprintf(line, "# Hour %.2d %s | Temperature: %.2sf | Weather %s %s #\n", i, spaceMaker(7), json_object_get_string(temp), json_object_get_string(weatherval), spaceMaker(35 - json_object_get_string_len(weatherval)));

      strcat(render, line);
    }
    
    //Unix time to readable time
    char sunrisebuf[80];
    time_t sunriset;
    sunriset = (time_t) json_object_get_int(sunrise);
    struct tm ts;
    ts = *localtime(&sunriset);
    strftime(sunrisebuf, sizeof(sunrisebuf), "%H:%M", &ts);


    char sunsetbuf[80];
    time_t sunsett;
    sunsett = (time_t) json_object_get_int(sunset);
    struct tm ts2;
    ts2 = *localtime(&sunsett);
    strftime(sunsetbuf, sizeof(sunsetbuf), "%H:%M", &ts2);

    strcat(render, "#-----------------------------------------------------------------------------------#\n");
    strcat(render, "# Additional details:                                                               #\n");
    strcat(render, "#  Sunrise: ");
    strcat(render, sunrisebuf);
    strcat(render, spaceMaker(67));
    strcat(render, "#\n");
    strcat(render, "#  Sunset: ");
    strcat(render, sunsetbuf);
     strcat(render, spaceMaker(68));
    strcat(render, "#\n");
    strcat(render, "#  Humidity: ");
    strcat(render, json_object_get_string(humidity));
     strcat(render, spaceMaker(69));
    strcat(render, "#\n");
    strcat(render, "#  Visibility: ");
    strcat(render, json_object_get_string(visibility));
     strcat(render, spaceMaker(64));
    strcat(render, "#\n");
    char *bottom =
    "#                               Type 'exit' to exit                                 #\n"
    "#####################################################################################\n";
    strcat(render, bottom);
    printf("%s",render);
  }

}
size_t writeCallback(char *contents, size_t size, size_t nmemb, void *userp) {
  

  size_t realsize = size * nmemb;

  struct memory *mem = (struct memory *) userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);

  if (ptr == NULL) {
    return 0;
  }

  mem->memory = ptr;
  memcpy(&mem->memory[mem->size], contents, realsize);
  mem-> size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

char* fetchAPI(char* zip, int option) {
  /*
    To use the openweather api, we have to convert our zip code into a lat long coordinate system.
    We can do this via google's api

    Basically, we use two api's to fetch the weather..
  */
  CURL *curl = curl_easy_init();

  if (!curl) {
    fprintf(stderr, "init failed\n");
    return 0;
  }
  char* googleAPIKey = "&key=AIzaSyCOlNBG5t9nUor7R4UjrFvUcwnd9EzNIFI";
  char googleURL[1024];
  strcpy(googleURL, "https://maps.googleapis.com/maps/api/geocode/json?address=");
  strcat(googleURL, zip);
  strcat(googleURL, googleAPIKey);


  struct memory chunk;

  chunk.memory = NULL;
  chunk.size = 0;

  curl_easy_setopt(curl, CURLOPT_URL, googleURL);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
  //printf("chunk: %s\n", chunk);

  CURLcode result = curl_easy_perform(curl);
  if (result != CURLE_OK) {
    fprintf(stderr, "download problem: %s\n", curl_easy_strerror(result));

  }

  curl_easy_cleanup(curl);
  //now that we have our chunk, we should convert it into useable data (latitude and longitude)
  /*
    grab the lat and long at:
    results[0].geometry.location.lat
    results[0].geometry.location.lng
  */
  struct json_object *parsed_json;
  parsed_json = json_tokener_parse(chunk.memory);
  struct json_object *results;
  json_object_object_get_ex(parsed_json, "results", &results);
  struct json_object *resulti;
  resulti = json_object_array_get_idx(results, 0);
  struct json_object *geometry;
  json_object_object_get_ex(resulti, "geometry", &geometry);
  struct json_object *location;
  json_object_object_get_ex(geometry, "location", &location);
  struct json_object *lat;
  struct json_object *lng;
  json_object_object_get_ex(location, "lat", &lat);
  json_object_object_get_ex(location, "lng", &lng);


  char url[512];
  strcpy(url, "https://api.openweathermap.org/data/2.5/onecall?appid=a3ecd4b0cfeef827dfd555ab2a365fd1&lat=");
  strcat(url, json_object_to_json_string(lat));
  strcat(url, "&lon=");
  strcat(url, json_object_to_json_string(lng));
  strcat(url, "&units=imperial");
  if (option == 0) {
    strcat(url, "&exclude=current,minutely,hourly,alerts");
  } else if (option == 1) {
    strcat(url, "&exclude=minutely,daily,alerts");
  }

  CURL *curl2 = curl_easy_init();

  if (!curl2) {
    fprintf(stderr, "init failed\n");
    return 0;
  }

  //Copy/paste of previous code to get JSON out of buffer
  struct memory chunk2;

  chunk2.memory = NULL;
  chunk2.size = 0;
  curl_easy_setopt(curl2, CURLOPT_URL, url);
  curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, writeCallback);
  curl_easy_setopt(curl2, CURLOPT_WRITEDATA, &chunk2);

  CURLcode result2 = curl_easy_perform(curl2);
  if (result2 != CURLE_OK) {
    fprintf(stderr, "download problem: %s\n", curl_easy_strerror(result2));

  }
  curl_easy_cleanup(curl2);
  return chunk2.memory;
  //potential memory leak?
  free(chunk.memory);
  free(chunk2.memory);
}

void drawMenu(char* zip, int option) {

    char menu[1807];
    menu[0] = '\0';
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

}