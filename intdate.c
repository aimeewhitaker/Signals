////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        intdate.c
// Other Files:      sendsig.c, division.c
// Semester:         CS 354 Fall 2018
//
// Author:           Aimee Whitaker Lecture: 001
// Email:            awhitaker2@wisc.edu
// CS Login:         aimee
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

time_t curtime;  // global variable of current time
int SECONDS = 3;  // number of seconds alarm will be set up for
int count = 0;  // number of times SIGUSR1 is caught

/* This function handles SIGALRM and will print the PID and current time
*/
void sig_handler(){
        time(&curtime);  // hand curtime to time function
        char buf[50];
        if (ctime_r(&curtime, buf) == NULL){  // error checking ctime()
                printf("Error in getting time. Exiting now.");
                exit(0);
        }
        printf("PID: %d | Current Time: %s", getpid(), ctime(&curtime));
        // display time
        alarm(SECONDS);  // realarm
        return;
}


/* This function handles SIGUSR1, and will increase count
*/
void user_handler(){
        ++count;  // incremement counter
        printf("SIGUSR1 caught!\n");
        return;
}


/* This function handles SIGINT, and will print number of times SIGUSR1 was
 * caught, and then exit.
*/
void int_handler(){
        printf("SIGINT received.");
        printf("SIGUSR1 was received %d times. Exiting now.", count);
        // how many times SIGUSR1 was caught
        exit(0);
}


/* This function is the main function. It sends an alarm signal every 3 seconds.
 * It also is responsible for redirecting flow of exection by sending caught
 * signals to user-created handlers.
*/
int main() {
        printf("Pid and time will be printed every 3 seconds.");
        struct sigaction act;  // create sigaction for SIGALRM
        memset (&act, 0, sizeof(act));
        act.sa_handler = &sig_handler;
        if (sigaction(SIGALRM, &act, NULL) < 0){  // error checking
                exit(0);
        }
        struct sigaction user;  // create sigaction for SIGUSR1
        memset (&user, 0, sizeof(user));
        user.sa_handler = &user_handler;
        // assigns handler to go to user-function
        if (sigaction(SIGUSR1, &user, NULL) < 0){  // error checking
                exit(0);
        }
        struct sigaction sigint;  // create sigaction for SIGINT 
        memset (&sigint, 0, sizeof(sigint));
        sigint.sa_handler = &int_handler;  // assigns handler to user-function
        if (sigaction(SIGINT, &sigint, NULL) < 0){  // error checking
                exit(0);
        }
        alarm(SECONDS);  // alarm the program
        while (1){  // infinite while loop
        }
        return 0;
}
