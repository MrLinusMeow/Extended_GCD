#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct Row{
 int64_t q;
 int64_t r;
 int64_t a;
 int64_t b;
};


int main(int argc, char* argv[]){
 if(argc != 3){
  fprintf(stderr, "Invalid input\nE: exactly two digits as input required.\n");
  return -1;
 }
 struct Row digits[3];
 int64_t index = 3;
 do{

  do{
   signed int x = atoi(argv[1]);
   signed int y = atoi(argv[2]);
   if(!(x && y)){
    fprintf(stderr, "Invalid input\nE: not a digit.\n");
    return -1;
   }
   if(x < y){
    signed int t = x;
    x = y;
    y = t;
   }
   digits[0] = (struct Row) {0, x, 1, 0};
   digits[1] = (struct Row) {0, y, 0, 1};
   digits[2] = (struct Row) {x / y, x % y, 1, 0 - (x / y)};
  }while(0);

  do{
   assert(digits[0].r != 0);
   assert(digits[1].r != 0);
   assert(digits[2].r != 0);
   int64_t quotient = digits[(index-2)%3].r / digits[(index-1)%3].r;
   int64_t remainder = digits[(index-2)%3].r % digits[(index-1)%3].r;
   int64_t a = digits[(index-2)%3].a - (quotient * digits[(index-1)%3].a);
   int64_t b = digits[(index-2)%3].b - (quotient * digits[(index-1)%3].b);
   digits[index%3] = (struct Row){quotient, remainder, a, b};
  }while(digits[(index++)%3].r != 0);

 }while(0);
 fprintf(stdout, "q:\t%ld\n", digits[(index-2)%3].q);
 fprintf(stdout, "r:\t%ld\n", digits[(index-2)%3].r);
 fprintf(stdout, "a:\t%ld\n", digits[(index-2)%3].a);
 fprintf(stdout, "b:\t%ld\n", digits[(index-2)%3].b);
 return 0;
}
