#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

const int BUFF_SIZE = 8192;
char buffer[BUFF_SIZE];
vector<string> text(800," ");

int main(const int argc, const char * argv[]) {
  int argNum = 1;
  int charCount = 0;
  int numLines = 0;
  int requestedLines = 10;
  if(*argv[1] == '-') {
    //requestedLines = atoi(argv[1]);                                           
    string inLines = argv[1];
    inLines = inLines.erase(0,1);
    int inLinesInt = stoi(inLines);

    requestedLines = inLinesInt;

    argNum++;
  }



  int fd = open(argv[argNum], O_RDONLY);
  int n = read(fd, buffer, BUFF_SIZE);
  text.resize(n);
  for(uint j = 0; j < text.size(); j++){
    text[j] = buffer[j];
  }

  close(fd);

  while(numLines != requestedLines) {
    cout << text[charCount];
    if(text[charCount].compare("\n") == 0)
      numLines++;
    charCount++;
  }

}
