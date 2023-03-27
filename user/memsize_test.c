#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


// prints unsigned integer
void
print_uint(int num)
{
    char buffer[16];
    int i = 0;
    if (num == 0) 
    {
        buffer[i++] = '0';
    }
    else 
    {
        while (num != 0) {
            int digit = num % 10;
            buffer[i++] = digit + '0';
            num /= 10;
        }
    }
    while (i > 0) {
        i--;
        write(1, &buffer[i], 1);
    }
    write(1, "\n", 1);
}


int
main(int argc, char *argv[])
{
  int size_before = memsize();
  print_uint(size_before);

  void* p = malloc(20000);

  int size_after_alloc = memsize();
  print_uint(size_after_alloc);
  
  free(p);
  
  int size_after_rel = memsize();
  print_uint(size_after_rel);

  exit(0,"");
}


