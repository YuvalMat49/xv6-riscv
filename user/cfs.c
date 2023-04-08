#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
print_cfs_stats()
{
    /**
     * TODO: print current process stats
    */
}

int
main(int argc, char *argv[]) {
    int pid1, pid2, pid3;
    pid1 = fork();
    if(pid1==0) {
        set_cfs_priority(LOW);
        pid2 = fork();
        if(pid2==0) {
            set_cfs_priority(NORMAL);
            pid3 = fork();
            if(pid3==0){
                set_cfs_priority(HIGH);
            }
        }
        int i;
        for(i=0; i<1000000; i++) {
            if(i%100000 == 0) {
                sleep(1);
            }
        }
    }
    
    /**
     * TODO: make sure only one process prints the children stats
     * Problems: Mixed printing - Do serial printing
    */
    return 0;
}