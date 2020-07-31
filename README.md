Project title: A4 CP386, Bankers Algorithm
4th assignment for CP386

Installation:
installed github and ran through VS code, using git bash

Instructions:
1. Import sample4_in.txt to location you are stored the c file in. Leave file name as is.
2. Import makefile4, and rename as MaKeFile
3. call the makefile, and run assignment as: ./Assignment_4, with the 4 inputs for the available array (same as assignment description) example: ./Assignment_4 10 5 7 8
4. When running enter in either RQ followed by 5 values, RL followed by 5 values, \* or run, or exit to leave program
5. If RL or RQ is entered, and the first thread or process value has already been requested, it will overwrite that request. Ie P0 = 1 2 3 4 if RQ 0 8 3 1 3 is entered, P0 will be 8 3 1 3
6. There must be at thease 1 RQ submitted before \* (star command) can be called

Motivation: To learn more about operating systems and simulate the Banker's Safe Algorithm

Screenshots: For screenshots, please visit this link. https://drive.google.com/drive/folders/1_5h8CwkCoBs-6Ib5FM-FnufMFOH1ML0a?usp=sharing

Individual contribution (main responsibilities):
Katie: Run function (safe sequence), RQ function, main
Jake: RL function, \* function, Run function (thread runs)

Group contribibution:
Katie and Jake actively assited eachother for the whole assignment.

Features : Various commands such as: run, RQ, RL and *, displayed thread/customer stats

Test: Please see screenshots above for test cases.

Code Example :
This is the thread function that runs when the user enters the run command.
void *threadRun(void *p)
{
    int i;
    // max array that each process can take
    // allocated array @ [0], needed array[0], availble
    sleep(1);
    int *client = (int *)p;
    printf("-->Customer/Thread id:%d\n", *client);
    printf("\tAllocated Resources:");
    for (i=0; i< MAXCOL; i++){
        printf("%d ", allocation[*client][i]);
    }
    printf("\n");
    printf("\tNeeded:");
    for (i=0; i< MAXCOL; i++){
        printf("%d ", need[*client][i]);
    }
    printf("\n");
    printf("\tAvailable:");
    for (i=0; i< MAXCOL; i++){
        printf("%d ", available[i]);
    }
    printf("\n");
    printf("\tThread has started\n");
    printf("\tThread has finished\n");
    printf("\tThread is realeasing resources\n");
    printf("\tNew Available:");
    for (i=0; i< MAXCOL; i++){
        available[i] =  available[i] + allocation[*client][i];
        printf("%d ", available[i]);
    }
    printf("\n");
    return NULL;
}


Authors:
Katie Milligan 160458550
Jacob Hessian 150981400

Credits: See authors
License: MIT license
