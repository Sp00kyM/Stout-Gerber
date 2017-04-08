#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main(int argc, const char** argv, char** envp) {
  char** env;
  for(env = envp; *env != 0; env++)
    {
      char* thisEnv = *env;
      cout << "\n" << thisEnv;

    }
  cout << endl;
  return EXIT_SUCCESS;

}
