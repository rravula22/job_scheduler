## Job Scheduler
# A simple job scheduler program written in C that allows a user to submit commands as jobs to be executed, up to a maximum of P (1 <= P <= 8) jobs running concurrently. The program provides the ability to check the status of jobs, view job history, and quit the scheduler.

## Requirements
gcc
pthreads library
## Usage
    Compile:  gcc -o final final.c.

    Run: ./final <number of jobs>, where <number of jobs> is an integer between 1 and 8.

## commands at the prompt:

    submit <command> - submits a new job to be executed.
    showjobs - shows the status of all currently running jobs.
    submithistory - shows the history of all submitted jobs.
    quit - exits the program.
## Code Overview
    # Structs
        jobs - Struct to store job information.
    # Functions
        executeJob - Function to execute a job.
         main - Main function that schedules jobs and processes commands.
## References
    C Standard Library: https://en.wikipedia.org/wiki/C_standard_library
    POSIX Threads: https://en.wikipedia.org/wiki/POSIX_Threads
    System Calls: https://en.wikipedia.org/wiki/System_call
    The C Programming Language: https://en.wikipedia.org/wiki/The_C_Programming_Language
    Time Library: https://en.wikipedia.org/wiki/C_date_and_time_functions
    String Library: https://en.wikipedia.org/wiki/C_string_handling
    Dynamic Memory Allocation: https://en.wikipedia.org/wiki/C_dynamic_memory_allocation
    File I/O: https://en.wikipedia.org/wiki/C_file_input/output
    Command-line arguments: https://en.wikipedia.org/wiki/Command-line_interface#Arguments
    sscanf function: https://www.geeksforgeeks.org/sscanf-function-in-c-cpp/
    pthread_create function: https://man7.org/linux/man-pages/man3/pthread_create.3.html
    fgets function: https://www.geeksforgeeks.org/fgets-function-in-c/
    system function: https://man7.org/linux/man-pages/man3/system.3.html
    freopn function: https://man7.org/linux/man-pages/man3/freopen.3.html
    sprintf function: https://www.geeksforgeeks.org/sprintf-in-c/
    strcmp function: https://www.geeksforgeeks.org/strcmp-in-c-cpp/
    strlen function: https://www.geeksforgeeks.org/strlen-function-in-c-with-examples/
    malloc function: https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
    exit function: https://www.geeksforgeeks.org/exit-function-c/
    Waitpid function: https://man7.org/linux/man-pages/man2/waitpid.2.html