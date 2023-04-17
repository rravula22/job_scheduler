#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

/**
 * Struct to store job information
*/
typedef struct {
    int job_id;
    pid_t pid;
    pthread_t thread;
    time_t start_time;
    time_t end_time;
    char* command;
    char status[128];
}jobs;

/**
 * Function to execute job
 * @param arg - job struct
 * @return NULL
*/
void *executeJob(void* command) { // function to execute job
    jobs* tmp_job = (jobs*) command;
    char outfile[20], errfile[20]; // create output and error file names
    sprintf(outfile, "%d.out", tmp_job->job_id); // create output file name
    sprintf(errfile, "%d.err", tmp_job->job_id); // create error file name
    freopen(outfile, "w", stdout); // redirect stdout to output file
    freopen(errfile, "w", stderr); // redirect stderr to error file
    printf("Job %d started\n", tmp_job->job_id); 
    char* values[3]= strtok(tmp_job->command, " ");
    char *cmd = strcat(values[1], values[2]);
    tmp_job->start_time = time(NULL);
    int res = system(cmd);
    tmp_job->end_time = time(NULL);
    if (res == -1) {
        printf("Error executing command\n");
        tmp_job->status = "FAILED";
    }
    else {
        tmp_job->status = "COMPLETED";
        printf("Job %d finished", tmp_job->job_id);
    }
    return NULL;
}

/**
 * Main function
 * @param argc - number of arguments
 * @param argv - array of arguments
 * @return 0
*/
int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <number of jobs> \n", argv[0]);
        exit(1);
    }
    //Reading the input from command line and storing it in a variable P
    int P = atoi(argv[1]);
    // Check for valid number of jobs
    if (P < 1 || P > 8) { // check if number of jobs is between 1 and 8
        printf("Number of jobs must be between 1 and 8 \n");
        exit(1);
    }
    // allocate jobs size
    jobs *job_list  = malloc(sizeof(jobs) * 100);
    int job_count = 0;
    int curr_jobs = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    // Create job struct and schedule jobs
    while (1) {
        // Read command
        char job_cmd[1024];
        printf("Enter command> ");
        fgets(job_cmd, 1024, stdin);
        // Remove the newline character at the end of the command
        job_cmd[strlen(job_cmd) - 1] = '\0';
        // Check for valid commands
        if (strncmp(job_cmd, "quit", 4) == 0) { // quit
            printf("Exiting job scheduler...\n");
            exit(0);
        } else if (strncmp(job_cmd, "showjobs", 8) == 0) { // showjobs
            printf("Jobs and Status:\n");
            for (int i = 0; i < job_count; i++) printf("Job %d: Status - %s\n", job_list[i].job_id, job_list[i].status);
        } else if(strncmp(job_cmd, "submithistory", 13) == 0) {
            printf("Job History:\n");
            for (int i = 0; i < job_count; i++) {
                printf("Job %d: Status - %s start_time: %dt end_time %dt\n", job_list[i].job_id, job_list[i].status, job_list[i].start_time, job_list[i].end_time);
            }
        }
        else {
            if (strncmp(job_cmd, "submit ", 7) == 0) { // submit
                pthread_t thread;
                jobs tmp_new = {job_count, 0, thread, 0, 0, strdup(job_cmd + 7), "WAITING"};
                job_list[job_count++] = tmp_new;
                if (curr_jobs >= P) { // check if max jobs reached and print error
                    printf("Maximum number of jobs (%d) reached\n job added to queue and in waiting state", P);
                } 
                else {
                    curr_jobs++;
                    int res = pthread_create(&tmp_new.thread, NULL, executeJob, &tmp_new);
                    if (res != 0) {
                         printf("Error creating thread for job %d\n", job_count);
                    }
                    else { 
                        printf("Job %d submitted\n", job_count);
                        
                    }
                }
            }
            else {
                printf("Invalid command\n");
            }
        }
    }
    return 0;
}
