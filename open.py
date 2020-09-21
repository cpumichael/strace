import sys
import os
import random

if __name__ == '__main__':
    pid = os.getpid()
    close_stderr = False
    
    if len(sys.argv) > 1:
        close_stderr = True

    print(f"My pid = {pid}", file=sys.stderr)
    print(f"Closing stderr = {close_stderr}", file=sys.stderr)
    print(f"Type an integer: ", file=sys.stderr); sys.stderr.flush()
    stuff = input() # read from stdin
    try:
        n = int(stuff)
    except ValueError:
        print("Need valid integer", file=sys.stderr)
        sys.exit(1)

    print(f"End of scan", file=sys.stderr)
    
    n_files_open = 0

    for i in range(1, n):
        fname = f'afile{i:05d}'
        n_files_open += 1
        f = open(fname, 'w')
        os.unlink(fname)

        if random.randint(1, 2) == 2:
            f.close()
            n_files_open -= 1
        else:
            print(i, file=f)
            f.flush()

    fname = f'afile{i:05d}'
    if close_stderr:
        sys.stderr.close()
        _ = open(fname, 'w')
        n_files_open += 1

    print(f'There are {n_files_open} files still open', file=sys.stdout); sys.stdout.flush()
    print(f'Pausing, just hit return', file=sys.stdout); sys.stdout.flush()
    input()

    try:
        os.unlink(fname)
    except FileNotFoundError:
        pass

    std_err_ret = sys.stderr.write('Stderr is closed?\n')
    if std_err_ret < 1:
        print(f"Could not print to stderr, error = {std_err_ret}", file=sys.stdout)
    else:
        print(f"Printed {std_err_ret} chars to stderr", file=sys.stdout)


# vim: ai sw=4 ts=4 et showmatch
