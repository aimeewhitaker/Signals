////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        division.c
// Other Files:      sendsig.c
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

#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int MAX = 100;  // max number of character of user input
int division = 0;  // counter for number of succesfull divisions performed

/* This function will handle the zero-division signal, and display
 * the number of successful divisions performed. It will then exit.
*/
void fpe_handler(){
        printf("Error: a division by 0 operation was attempted.");
        printf("Total number of operations completed successfully: %d", 
                division);
        // display number of divisions
        printf("The program will be terminated");
        exit(0);  // exit program
}

/* This function will handle the ctrl-C keyboard input. It will display the
 * number of successful divisions and quit. 
*/
void int_handler(){
        printf("Total number of operations completed successfully: %d",
                division);
        // display number of divisions
        printf("The program will be teminated");
        exit(0);  // exit program
}


/* This function is the main program that creates sigaction structs and changes
 * the flow of error signals. It will redirect the program towards user-created
 * error handlers. It will also perform division and prompt user for two 
 * numbers.
*/
int main(){
        struct sigaction act;  // create sigaction struct for keyboard input
        memset (&act, 0, sizeof(act)); 
        act.sa_handler = &fpe_handler;
        if (sigaction(SIGFPE, &act, NULL) < 0){
                exit(0);  // exit program if can't redirect signal
        }
        struct sigaction sigint;
        // create sigaction struct for zero division input
        memset (&sigint, 0, sizeof(act)); 
        sigint.sa_handler = &int_handler;
        if (sigaction(SIGINT, &sigint, NULL) < 0){ 
                exit(0);  // exit program if can't redirect signal
        }
        while (1){  // infinite loop
                char buf[MAX];
                printf("Enter first integer: ");
                char* string = fgets(buf, MAX, stdin);
                if (string == NULL){  // error checking for fgets()
                        printf("Error reading input. Exiting now.");
                        exit(0);
                }
                int first = (int) atoi(string);  // convert to integer
                printf("Enter second integer: ");
                char* string2 = fgets(buf, MAX, stdin);
                if (string2 == NULL){  // error checking for fgets()
                        printf("Error reading input. Exiting now.");
                        exit(0);
                }
                int second = (int) atoi(string2);  // convert to integer
                int quotient = (int) first / second;  
                // if second is 0, will be sent to handler
                int mod = (int) first % second;
                division++;  // increment number of successful divisions
                printf("%d / %d is %d with a remainder of %d",
                        first, second, quotient, mod);
        }
        return 0;
}

