#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

const int BUFF_SIZE = 8192;
char buffer[BUFF_SIZE];
vector<string> text(800, " ");

int main(const int argc, const char * argv[]) {
  int argNum = 1;
  int charCount = 0;
  int numLines = 0;
  int requestedLines = 10;
  int fix = 0;

if(*argv[1] == '-') {
    string inLines = argv[1];
    inLines = inLines.erase(0,1);
    int inLinesInt = stoi(inLines);

    requestedLines = inLinesInt;

    argNum++;
  }

  int fd = open(argv[argNum], O_RDONLY);
  int n = read(fd, buffer, BUFF_SIZE);
  text.resize(n);
  for(uint j = 0; j < text.size() && fix < BUFF_SIZE; j++){

    while((buffer[fix]!='\n') && fix < BUFF_SIZE){
      text[j] += buffer[fix];
      fix++;
    }
    fix++;
    numLines++;
  }
  close(fd);

  int startPoint = numLines - requestedLines - 1;
  numLines = 0;


  while(numLines != requestedLines) {
    cout << text[startPoint] << endl;
    startPoint++;
    numLines++;
    }
}
