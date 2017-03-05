#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <unistd.h>

const int width  = 85, height = 30;
int states [height][width] = {0};

void draw(){
  for(int i=0;i<width;i++)
    std::cout << "#";
  std::cout << std::endl;
  for(int i=0; i<height; i++){
    for(int x=0; x<width; x++){
      //std::stringstream ss;
      //ss << states[i][x];
      if(states[i][x]==0)
	std::cout << " ";
      else
	std::cout << std::to_string(states[i][x]);
      }
    std::cout << std::endl;
  }
}
void copy_array(int* origin, int* destination){
  for(int i=0;i<sizeof(states)/4;i++){
    *(destination+i)=*(origin+i);
  }
}

int wrap(int x,int max){
	if(x>=max)
	  return x-max;
	else if(x<0)
	  return x+max;
	return x;
}

void move(){
  int new_states[height][width];
  int *p=states[0], *q=new_states[0];
  copy_array(p,q);
  //for each cell on screen
  for(int i=0; i<height; i++){
    for(int x=0; x<width; x++){
      int num_alive = 0;
      //scan neighbours, see who's alive
      for(int a=i-1; a<= i+1; a++){
	int c=wrap(a,height);
	for(int b=x-1; b<=x+1; b++){
	  int d=wrap(b,width);
	  if(states[c][d]==1)
	    num_alive++;
	}
      }
      if(states[i][x]==1)
	num_alive--;
      if(num_alive==3&&states[i][x]==0)
	new_states[i][x]=1;
      else if(states[i][x]==1&&(num_alive<2||num_alive>3))
	new_states[i][x]=0;
      else
	new_states[i][x]=states[i][x];
    }
  }
  copy_array(q,p);
}

void add_glider(int top,int left){
  states[wrap(top,height)][wrap(left+1,width)]=1;
  states[wrap(top+1,height)][wrap(left+2,width)]=1;
  states[wrap(top+2,height)][wrap(left,width)]=1;
  states[wrap(top+2,height)][wrap(left+1,width)]=1;
  states[wrap(top+2,height)][wrap(left+2,width)]=1;
}

int main() {
  //gliders added accross
  //note: draws a pattern at: width  = 50, height = 15;
  int set = 0;
  for(int i=0; i<height; i++){
    for(int x=0; x<width; x++){
      if (set== 50){
	add_glider(i,x);
	set = 0;
      }
      set++;
    }
  }
  /*
  //square
  states[10][22]=1;
  states[11][22]=1;
  states[10][23]=1;
  states[11][23]=1;
  //line
  states[4][23]=1;
  states[4][25]=1;
  states[4][24]=1;
  //edge square
  states[0][22]=1;
  states[height-1][22]=1;
  states[0][23]=1;
  states[height-1][23]=1;
  //edge line
  states[10][width-1]=1;
  states[10][0]=1;
  states[10][1]=1;
  */
  add_glider(height-1,width-2);
  while(true){
    draw();
    usleep(500000);
    move();
  }
  return 0;
}

