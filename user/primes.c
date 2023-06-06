#include "kernel/types.h"
#include "user/user.h"

__attribute__((noreturn))
void
primes(int *p){
    close(p[1]);

    int n;
    int first;
    int len;
    int in = p[0];
    int out;
    int fd[2];

    if((len = read(in,&first,sizeof(int))) <= 0){
        exit(0);
    }

    printf("prime %d\n",first);

    pipe(fd);
    out = fd[1];
    if(fork() == 0){
        primes(fd);
    }else{
        while ((len = read(in,&n,sizeof(int))) > 0){
            if(n % first != 0){
                write(out,&n,sizeof(int));
            }
        }
        close(out);
        wait(0);
        exit(0);
    }

}

int
main(int argc, char *argv[])
{
 int p[2];
 pipe(p);

 if(fork() == 0){
    primes(p);
 }else{
    int i;
    for (i = 2; i <= 35; i++)
    {
       write(p[1],&i,sizeof(i));
    }
     close(p[1]);
     wait(0);
 }
 exit(0);

}
