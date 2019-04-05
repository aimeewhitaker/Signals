////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        sendsig.c
// Other Files:      division.c
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
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

/* This function will use command line arguments to send signals to other
 * running processes on the server using PID and the kill function.
*/
int main(int argc, char* argv[]){
        if (argc != 3){  // error checking that enough arguments exist
                printf("Incorrect command line arguments. Exiting now.");
                exit(0);
        }
        char *ptr;
        int PID = (int) strtol(argv[2], &ptr, 10); 
        // use strtol to parse the data and convert to in
        if (errno != 0 && PID == 0){  // error checking for strtol
                printf("Invalid argument, exiting now.");
                exit(0);
        }
        char sig_type = argv[1][1];
        if (sig_type == 'i'){ 
                int check = kill(PID, SIGINT);  // send signal to this program
                if (errno != 0 &&  check == -1){
                        printf("Error sending signal. Exiting now.");
                        exit(0);
                }
        } else {
                int check2 = kill(PID, SIGUSR1);
                if (errno != 0 && check2 == -1){
                        printf("Error sending signal. Exiting now.");
                        exit(0);
                }
        }
        return 0;
}
