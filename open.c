#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char* fname = malloc(1024);
    pid_t pid = getpid();
    srandom((unsigned int)pid);
    int i, n;

    fprintf(stdout, "My pid = %d\n", (int)pid);
    fprintf(stdout, "Type an integer: "); fflush(stdout);
    fscanf(stdin, "%d", &n);
    fprintf(stderr, "End of Scan\n");

    int n_files_open = 0;

    for (i=1; i < n; i++) {
        sprintf(fname, "afile%05d", i);
        FILE *f = fopen(fname, "w");
        n_files_open += 1;
        unlink(fname); /* remove fname from directory listing,
                        * contents will be removed at another time */
        if (random() % 2 == 0) {
            fclose(f);
            n_files_open -= 1;
        } else {
            fprintf(f, "%d\n", i);
            fflush(f);
        }
    }

    close(2); /* close stderr, and see what happens */
    sprintf(fname, "afile%05d", i);
    FILE *f = fopen(fname, "w");
    unlink(fname);
    fclose(f);

    fprintf(stdout, "There are %d files still open\n", n_files_open); fflush(stdout);
    fprintf(stdout, "Pausing just hit return"); fflush(stdout);
    char c;
    fscanf(stdin, "%c", &c);
    fscanf(stdin, "%c", &c);

    int std_err_ret = 0;
    std_err_ret = fprintf(stderr,"Stderr is closed!\n");
    fprintf(stdout, "Could not print to stderr, error = %d\n", std_err_ret);

    return 0;

}

/* vim: cindent sw=4 ts=4 et showmatch
 */