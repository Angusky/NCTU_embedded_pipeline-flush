#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define NUM 1000000

long diff_in_us(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec * 1000000.0 + diff.tv_nsec / 1000.0);
}

int main()
{
    FILE *fp = fopen("file","w");
    srand(time(NULL));
    for(int i=0; i<NUM; i++) {
        fprintf(fp,"%u\n",rand());
    }
    fclose(fp);
    fp = fopen("file","r");
    unsigned int *ptr = malloc(sizeof(*ptr)*NUM);
    unsigned int sum = 0;
    for(int i=0; i<NUM; i++) {
        fscanf(fp,"%u",&ptr[i]);
    }
    struct timespec start,end;
    clock_gettime(CLOCK_REALTIME,&start);
    for(int i=0; i<NUM; i+=4) {
        sum += ptr[i];
        sum += ptr[i+1];
        sum += ptr[i+2];
        sum += ptr[i+3];
    }
    clock_gettime(CLOCK_REALTIME,&end);
    printf("result: %u ; time spent: %ldus\n",sum,diff_in_us(start,end));
    free(fp);
    free(ptr);
    return 0;
}
