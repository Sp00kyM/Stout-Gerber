
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <pwd.h>
#include <grp.h>
using namespace std;
//global variable
bool l=false;
bool a=false;
const char * owd;
//function for printing out the entries created by args
void printing(vector<struct stat>input,vector<string>names){
  string symbols="----------";
  struct passwd* usr;
  struct group* grp;
  struct stat stats;
  if(l==false){
    for(uint i=0;i<names.size();i++){
      cout<<names[i]<<endl;
    }//i
  }//NOT LONG FORM
  if(l){
    for(uint i=0;i<names.size();i++){
      int fd =open(names[i].c_str(),O_RDONLY);
      if(fd==-1){continue;}
      fstat(fd,&stats);
      //handling file type with a series of tests
      if (S_ISREG(stats.st_mode)) {
        symbols[0] ='-';
      }
      if (S_ISDIR(stats.st_mode)) {
        symbols[0] = 'd';
      }
      if (S_ISCHR(stats.st_mode)) {
        symbols[0] = 'c';
      }
      if (S_ISBLK(stats.st_mode)) {
        symbols[0] = 'b';
      }
      if (S_ISFIFO(stats.st_mode)) {
        symbols[0] = 'p';
      }
      if (S_ISLNK(stats.st_mode)) {
        symbols[0] = 'l';
      }
      if (S_ISSOCK(stats.st_mode)) {
        symbols[0] = 's';
      }
      //handling mode bits with a series of test
      //usr bits
      if ( S_IRUSR & stats.st_mode){//1
        symbols[1] ='r';
      }
      if ( S_IWUSR & stats.st_mode){//2
        symbols[2] ='w';
      }
      if ( S_IXUSR & stats.st_mode){//3
        symbols[3] ='x';
      }
      //group bits
      if ( S_IRGRP & stats.st_mode){//4
        symbols[4]='r';
      }
      if ( S_IWGRP & stats.st_mode){//5
        symbols[5]='w';
      }
      if ( S_IXGRP & stats.st_mode){//6
        symbols[6]='x';
      }
      //others bits
      if ( S_IROTH & stats.st_mode){//7
        symbols[7]='r';
      }
      if ( S_IWOTH & stats.st_mode){//8
        symbols[8]='w';
      }
      if ( S_IXOTH & stats.st_mode){//9
        symbols[9]='x';
      }
      //special bits
      if (S_ISUID & stats.st_mode){
        symbols[3]='s';
      }
      if ( S_ISGID & stats.st_mode){
        symbols[6]='s';
      }
      if ( S_ISVTX & stats.st_mode){
        symbols[9]='t';
      }
      usr = getpwuid(stats.st_uid);//username of owner
      grp = getgrgid(stats.st_gid);//groupname of owner
      time_t t = stats.st_ctime;
      struct tm thetime;
      localtime_r(&t,&thetime);
      char timebuff[80];
      strftime(timebuff,sizeof(timebuff),"%b %d %H:%M",&thetime);//formatting
      cout<<" "<<symbols<<" "<<stats.st_nlink<<" "<<usr->pw_name<<" "
          <<grp->gr_name<<" "<<stats.st_size<<" "<<timebuff
          <<" "<<names[i]<<endl;
    }
  }//LONG FORM
}
vector<struct stat> dirreader(const char* input, vector<string> &names){
  vector<string> sorter;
  vector<struct stat> giveBack;
  struct stat entrystats;
  DIR* directory = opendir(input);
  chdir(input);
   struct dirent *dirp;
  int dirlength=0;
  while((dirp = readdir(directory))){//reading dirents and placing them to be sorted
    if(!a&&(dirp->d_name[0]=='.')){
      continue;
    }
    dirlength++;
    (sorter).push_back(dirp->d_name);
  }
  sort(sorter.begin(),sorter.end());//sorting
  for(uint i=0;i<sorter.size();i++){//opening and pushing dirents in the correct order
    int fd=open(sorter[i].c_str(),O_RDONLY);
    fstat(fd,&entrystats);
    giveBack.push_back(entrystats);
    names.push_back(sorter[i]);
  }
  closedir(directory);
  chdir(owd);//moving back to original directory
  return giveBack;
}
struct stat filereader(const char * input){//reading files simply
  struct stat stats;
  int fd = open(input,O_RDONLY);
  fstat(fd,&stats);
  return stats;
}
int main(const int argc, const char * argv[]){
  int opt;
  owd = get_current_dir_name();//storing cwd
  int inputfilecount=0;
  struct stat stats;
  vector<string> sortedargs;
  vector<vector<struct stat> > entries;
  vector<vector<string> > names;
  while((opt = getopt(argc,(char**)argv,"al"))!=-1){
    switch(opt){
    case'a':
      a=true;
      break;
    case'l':
      l=true;
      break;
    }//switch
  }//while opt

  for(int i=1;i<argc;i++){//checking how many files were input
    if(argv[i][0]=='-'){continue;}
    inputfilecount++;
  }

  if(inputfilecount==0){//if no files input
    names.resize(1);
     entries.resize(1);
    entries.push_back(dirreader(".",names[0]));
    printing(entries[0],names[0]);
  }

  //sorting the command line args
  for(int i=0;i<argc;i++){
    if(argv[i][0]=='-'|| i==0){continue;}
    sortedargs.push_back(argv[i]);
  }
  sort(sortedargs.begin(),sortedargs.end());

  //main logic
  if(inputfilecount>0){
    for(uint i=0;i<sortedargs.size();i++){
      int fd = open(sortedargs[i].c_str(),O_RDONLY);
      if(fd == -1){//checking open success
        cout<<"ls: cannot access "<<sortedargs[i]<<": No such file or directory"<<endl;
        continue;
      }

      fstat(fd,&stats);//storing argc[i] data to test
      if(S_ISDIR(stats.st_mode)){//adding dirrectory names
        names.resize(names.size()+1);
        entries.push_back(dirreader(sortedargs[i].c_str(),names[i]));
        continue;
        //the above read through the directory, and stored all it's entries
        //in a 2d vector. the first dimension of the vector corresponds
        //to the command line args, the second, their contents
      }
      entries.resize(entries.size()+1);//accomadating
      names.resize(names.size()+1);
       entries[i].push_back(filereader(sortedargs[i].c_str()));
       //the above did the same with a simple file
       names[i][0]=sortedargs[i].c_str();

    }//for argc

    for(uint i=0;i<names.size();i++){
      int fd =open(sortedargs[i].c_str(), O_RDONLY);
      fstat(fd,&stats);
      //statting the args again bc we used the stat struct again
      if(S_ISDIR(stats.st_mode)){//checking
        cout<<sortedargs[i]<<":"<<endl;
        chdir(sortedargs[i].c_str());//we do this bc we will be opening contents
      }
      printing(entries[i],names[i]);
      chdir(owd);//moving back so this can be done on loop
    }
  }//if more than one file is input
  return EXIT_SUCCESS;
}//main



