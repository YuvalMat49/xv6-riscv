#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    exit(-1, "Exactly one argument is required\n");
  }
  int policy = atoi(argv[1]);
  int rc = set_policy(policy);
  if(rc==0){
    char* pl_type = (policy==0)? "xv6 default" : (policy==1)? "priority scheduling" : "CFS with priority decay";
    printf("Successfully changed policy to: %s\n", pl_type);
  }
  else{
    printf("Failed to change policy\n");
  }
  return 0;
}