#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <cwchar>
using namespace std;
int main(const int argc, const char * argv[]){
  int opencount=0;
  int totbytes=0;
  int totlines=0;
  int totwords=0;
  int totcharacters=0;
  int opt;
  bool c = false;
  bool l = false;
  bool w = false;
  bool m = false;
  struct stat stats;
  while((opt = getopt(argc,(char**)argv,"clmw"))!=-1){
    switch (opt){
    case 'c':
      c = true;
      break;
    case 'l':
      l = true;
      break;
    case 'm':
      m = true;
      break;
    case 'w':
      w = true;
      break;
    }//switch
  }//while opt
  if(!c&&!m&&!l&&!w){c=true;l=true;w=true;}
    for(int i=1;i<argc;i++){
      if(argv[i][0]=='-'){continue;}
      int fd = open(argv[i],O_RDONLY);
      if(fd == -1){
        cout<<"wc: "<<argv[i]<<": No such file or directory"<<endl;
        continue;
      }
      opencount++;
      int bytes=0;
      int lines=0;
      int words=0;
      int characters=0;
      fstat(fd,&stats);
      if(S_ISDIR(stats.st_mode)) {
        cout<<argv[i]<<" is a directory"<<endl;
        cout<<"\t0\t0\t0 "<<argv[i]<<endl;
        exit(0);
        }
      bytes = stats.st_size;//size of file
      totbytes += bytes;
      char * buffer = new char[bytes];//char array the size of the file
      read(fd,&buffer,bytes);
      if(buffer[0]!=' ' && buffer[0]!='\n'){words++;}
      for(int i=0;i<bytes;i++){
        if(buffer[i]=='\n'){
          lines++;
          totlines++;
        }
        if( buffer[i]!=' ' && buffer[i] !='\n' && buffer[i]!='\t'&&
            (buffer[i-1]=='\n' || buffer[i-1]==' ' || buffer[i-1]=='\t')){
          words++;
          totwords++;
        }
      }//for buffer
      delete buffer;
       if(l){cout<<lines<<' ';}
      if(w){cout<<words<<' ';}
      if(c){cout<<bytes<<' ';}
      if(m){cout<<characters<<' ';}
      cout<<argv[i]<<endl;
    }//for argc
    if(opencount>1){
      if(l){cout<<totlines<<' ';}
      if(w){cout<<totwords<<' ';}
      if(c){cout<<totbytes<<' ';}
      if(m){cout<<totcharacters<<' ';}
      cout<<"total"<<endl;
    }
}//main
