
#include <iostream>
#include <unistd.h>
using namespace std;
int main(){
  char * owd = get_current_dir_name();
  cout<<owd<<endl;
}
