#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
sleep_and_print_cfs_stats()
{
    int i;
    for(i=0; i<1000000; i++) {
        if(i%100000 == 0) {
             sleep(10);
        }
    }
    struct cfs_stats cfs_stats;
    if(get_cfs_stats(getpid(), &cfs_stats) != -1){
        sleep(10);
        printf("PID: %d, CFS: %d, rtime: %d, stime: %d, retime: %d\n", getpid(), cfs_stats.cfs_priority, cfs_stats.rtime, cfs_stats.stime, cfs_stats.retime);
    }
}
   

int
main(int argc, char *argv[]) {
    // set_policy(2);
    for( int i = 0; i < 3; i++){
        if(fork() == 0) {
            set_cfs_priority(i);
            sleep_and_print_cfs_stats();
            exit(0,"");
        }
        else{
            sleep(200);
        }
    }
    wait(0,0);
    wait(0,0);
    wait(0,0);
    exit(0,"");
}