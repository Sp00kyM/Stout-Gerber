#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
using namespace std;
time_t t = time(0);//right now
struct tm * grab = localtime(&t);//structured right now
string months[12] =//month strings
  {"January","February","March","April","May","June","July","August",
   "September","October","November","December"};
int numdays[] = {31,28,31,30,31,30,31,31,30,31,30,31};//numdays in month
string header ="Su Mo Tu We Th Fr Sa";//header of every calender

struct tm  makemonthcal(string month,string year){
    struct tm  placehold = {};//to ease calculation
      placehold.tm_mon = stoi(month)-1;
      placehold.tm_mday = 1;
      placehold.tm_year = stoi(year)-1900;
      mktime(&placehold);
    return placehold;
}
void printmonthcal(struct tm input){
  string slots[42];
  int startSlot = input.tm_wday;//only thing that needs to change in Julian
//need to find what day of the week the first day in julian calendar month starts
  if((input.tm_year+1900==1752 && input.tm_mon<=8)
     ||
     (input.tm_year+1900<1752)){
    int w,d,m,y,s,c;
    bool leap;
    int monthposs[12]={0,3,3,6,1,4,6,2,5,0,3,5};
    int leapmonthposs[12]={6,2,3,6,1,4,6,2,5,0,3,5};
    int cposs[7] = {5,4,3,1,0,6};
    if(input.tm_year%4==0){leap = true;}
     /*w = day of week, d= day, m = month, y= year, s = last two digits, c = cent*/
    d=1;
    s=(input.tm_year+1900)%100;
    y = ((s/4)+s)%7;
    if(leap==true){m=leapmonthposs[input.tm_mon];}
    else  if(leap==false){m=monthposs[input.tm_mon];}
    c = cposs[((input.tm_year+1900)/100)%7];
    w=(d+m+c+y)%7;
    startSlot = w;
      }
  if((input.tm_year+1900==1752 && input.tm_mon==8)){
      for(int i=0;i<startSlot+numdays[input.tm_mon];i++){
        slots[i] = to_string(i-startSlot+1);}//for populating cal
      cout<<"    "<<months[input.tm_mon]<<" "<<input.tm_year+1900<<endl;
      cout<<header<<endl;
      int weekday=0;
      for(int i=0;i<42;i++){
        weekday++;
if(i<startSlot){
          cout<<"   ";
          continue;
        }
        if(i<4){cout<<" ";}
        if(i==4){i=15;}
        cout<<slots[i]<<" ";
        if(weekday ==7){
          cout<<endl;
          weekday = 0;
        }
      }
      cout<<endl;
  }
  else{
  cout<<"    "<<months[input.tm_mon]<<" "<<input.tm_year+1900<<endl;
  cout<<header<<endl;
  for(int i=0;i<startSlot+numdays[input.tm_mon];i++){
   slots[i] = to_string(i-startSlot+1);}//for populating cal
  int weekday = 0;
  for(int i=0;i<42;i++){
    weekday++;
    if(i<startSlot){
      cout<<"   ";
      continue;
    }
    if( i-startSlot+1== grab->tm_mday && grab->tm_year == input.tm_year && grab->\
tm_mon == input.tm_mon){
      cout<<"\033[30;47m";
    }
    if(i<startSlot+9){
      cout<<" ";
    }
    cout<<slots[i];
    cout<<"\033[0m";
    cout<<" ";
if(weekday ==7){
      cout<<endl;
      weekday = 0;
    }
  }
  cout<<endl;
  }
}
int main(int argc, const char * argv[]){
  //variables needed for everything
  string yearput;
  string monthput;
  if(argc == 2){//only year is input
    yearput = argv[1];
    if(stoi(yearput)<1 || stoi(yearput)>9999){cout<<"INVALID YEAR ENTRY, PROGRAM
TERMINATED"<<endl; exit(0);}
    if(stoi(yearput)%4 == 0){numdays[1] = 29;}//checking if there is a leap year
 if(stoi(yearput)%4 == 0){numdays[1] = 29;}//checking if there is a leap year
    for(int i=1;i<=12;i++){
      struct tm output = makemonthcal(to_string(i),argv[1]);
      printmonthcal(output);
    }
  }//two command line arguments
  if(argc ==3){//month and year are input
    monthput = argv[1];
    if(stoi(monthput)<1 || stoi(monthput)>12){cout<<"INVALID MONTH  ENTRY, PROGRA\
M TERMINATED"<<endl; exit(0);}
    yearput = argv[2];
    if(stoi(yearput)<1 || stoi(yearput)>9999){cout<<"INVALID YEAR ENTRY, PROGRAM \
TERMINATED"<<endl;exit(0);}
    if(stoi(yearput)%4 == 0){numdays[1] = 29;}
    struct tm output = makemonthcal(argv[1],argv[2]);
    printmonthcal(output);
  }//3 args
  if(argc == 1){//no command line arguments
   struct tm now = makemonthcal(to_string((grab->tm_mon)+1),to_string((grab->tm_\
year)+1900));
    printmonthcal(now);
  }//if no command line args
}//main
