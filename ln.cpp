#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
int main(const int argc, const char * argv[]){
  int argplace =0;
  bool s;
  struct stat dircheck;
  if(argc<3){
    cout<<"ln:Too few arguments input, process terminated"<<endl;
    exit(1);
  }
  if(argc>4){
    cout<<"ln:Too many arguments input, process terminated"<<endl;
    exit(1);
  }
  if(strcmp(argv[1],"-s")==0){
    s = true;
    argplace = 2;
  }
  else{argplace = 1;};
  if(!s){
    int fd = open(argv[argplace],O_RDONLY);
    if(fd==-1){
      cout<<"ln: accessing '"<<argv[argplace]<<"': No such file or directory"<\
<endl;
      exit(1);
    }
    fstat(fd,&dircheck);
      if(S_ISDIR(dircheck.st_mode)){
        cout<<"ln: cannot make a hard link to a directory";
      }
 fd = open(argv[argplace+1],O_RDONLY);
    if(fd!=-1){
      cout<<"ln: creating hard link'"<<argv[argplace+1]<<"': File exists"<<end\
l;
      exit(1);
    }
    link(argv[argplace],argv[argplace+1]);
  }
  if(s){
    int fd = open(argv[argplace+1],O_RDONLY);
    if(fd!=-1){
      cout<<"ln: creating hard link'"<<argv[argplace+1]<<"': File exists"<<end\
l;
      exit(1);
    }
    symlink(argv[argplace],argv[argplace+1]);
  }
 return EXIT_SUCCESS;
}
