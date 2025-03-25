#include<stdio.h>

#include<unistd.h>

int main(){

  int x=0, y=4;

  int pid=fork();

  if(pid==0){

    x+=y;

    printf("Child process: %d; ",x);

    return 0;

  }

  else if(pid>0){

    x+=y*2;

    printf("Parent process: %d; ",x);

  }

  return 0;

}
