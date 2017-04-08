#include <iostream>
#include <time.h>
#include <string>

using namespace std;

int main(int argc, const char* argv[]){

  time_t t = time(NULL);
  struct tm * date = localtime(&t);
  string day;
  string month;
  string hours = to_string(date->tm_hour);
  string mins = to_string(date->tm_min);
  string secs = to_string(date->tm_sec);

  if(date->tm_hour < 10)
    hours = "0" + to_string(date->tm_hour);

  if(date->tm_min < 10)
    mins = "0" + to_string(date->tm_min);
  
  if(date->tm_sec < 10)
    secs = "0" + to_string(date->tm_sec);

  switch(date->tm_wday) {
  case 0:
    day = "Sun";
    break;
  case 1:
    day = "Mon";
    break;
  case 2:
    day = "Tue";
    break;
  case 3:
    day = "Wed";
    break;
  case 4:
    day = "Thu";
    break;
  case 5:
    day = "Fri";
  case 6:
    day = "Sat";
    break;
  }

  switch(date->tm_mon){
  case 0:
    month = "Jan";
    break;
  case 1:
    month = "Feb";
    break;
  case 2:
    month = "Mar";
    break;
  case 3:
    month = "Apr";
    break;
  case 4:
    month = "May";
    break;
  case 5:
    month = "Jun";
    break;
  case 6:
    month = "Jul";
    break;
  case 7:
    month = "Aug";
    break;
  case 8:
    month = "Sep";
  case 9:
    month = "Oct";
    break;
  case 10:
    month = "Nov";
    break;
  case 11:
    month = "Dec";
    break;
  }


  cout << (day) << " "
       << (month) << " "
       << (date->tm_mday) << " "
       << (hours) << ":"
       << (mins) << ":"
       << (secs) << " "
       << (date->tm_zone) << " "
       << (date->tm_year + 1900) << endl;

 return EXIT_SUCCESS;

}





