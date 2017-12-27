#include <iostream>
int input = 277678;

// 1 9 25 ...


int main() {
  int result = 0;
  int location = input;

  // Find n (where n is the full circle
  int n = 1;
  while(n*n < location) n+=2;
  n-=2;

  int x = 0;
  int y = 0;
  int topleft = n*n+2*(n+1);
  int topright = n*n+(n+1);
  std::cout << topleft << " " << topright << std::endl;
  if(location <= topleft && location > n*n+(n+1)) {
    // top edge
    std::cout << "t" << std::endl;

    x = (n+1)/2 - (topleft - location);
    y = (n+1)/2;
  } else if(location < topleft || location == (n+1)*(n+1)) {
    // right edge
    std::cout << "r" << std::endl;
    x = -(n+1)/2;
    if(location == (n+1)*(n+1)) {
      y = -(n+1)/2;
    } else {
      y = (n+1)/2 - (topright - location);
    }
  } else if (location < topleft + n+1) {
    // left edge
    std::cout << "l" << std::endl;
    x = (n+1)/2;
    y = (n+1)/2 - (location - topleft);
  } else {
    // bottom edge
    std::cout << "b" << std::endl;
    x = (n+1)/2 + ((topleft+n+1) - location);
    y = -(n+1)/2;
  }


  std::cout << n << " " << x << " " << y << " " << abs(x)+abs(y) << std::endl;

  int l = 526;
  int v[526][526];
  memset(&v,0,sizeof(v));
  v[l/2][l/2] = 1;
  location = 2;
  while(true) {
    // Find n (where n is the full circle
    int n = 1;
    while(n*n < location) n+=2;
    n-=2;

    int x = 0;
    int y = 0;
    int topleft = n*n+2*(n+1);
    int topright = n*n+(n+1);

    if(location <= topleft && location > n*n+(n+1)) {
      x = (n+1)/2 - (topleft - location);
      y = (n+1)/2;
    } else if(location < topleft || location == (n+1)*(n+1)) {
      x = -(n+1)/2;
      if(location == (n+1)*(n+1)) {
        y = -(n+1)/2;
      } else {
        y = (n+1)/2 - (topright - location);
      }
    } else if (location < topleft + n+1) {
      // left edge
      x = (n+1)/2;
      y = (n+1)/2 - (location - topleft);
    } else {
      x = (n+1)/2 + ((topleft+n+1) - location);
      y = -(n+1)/2;
    }
    int real_x, real_y;
    real_x = l/2 + x;
    real_y = l/2 + y;
    v[real_x][real_y] =
      v[real_x+1][real_y-1] +
      v[real_x+1][real_y] +
      v[real_x+1][real_y+1] +
      v[real_x-1][real_y] +
      v[real_x-1][real_y+1] +
      v[real_x-1][real_y-1] +
      v[real_x][real_y+1] +
      v[real_x][real_y-1];

    std::cout << real_x << " " << real_y << " " <<v[real_x][real_y] << std::endl;
    location+=1;
    if(v[real_x][real_y] > input) {
      std::cout << v[real_x][real_y] << std::endl;
return 0;
    }

  }


  return 0;
}
