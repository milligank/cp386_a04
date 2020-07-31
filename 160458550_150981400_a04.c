/*
Names:
Kathleen Milligan 160458550
Git: milligank
Jacob Hessian 150981400
Git: JakeHessian

Project link:
https://github.com/milligank/cp386_a04
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

#define INPUTFILE "sample4_in.txt"
#define MAXINPUT 200
#define MAXCLIENTS 5
#define MAXCOL 4

void *threadRun(void *p);
void create_maximum_array();
int run_bankers(int, int, int alloc[MAXCLIENTS][MAXCOL], int max[MAXCLIENTS][MAXCOL], int avail[MAXCOL], int need[MAXCLIENTS][MAXCOL]);
void get_need_array(int, int, int alloc[MAXCLIENTS][MAXCOL], int max[MAXCLIENTS][MAXCOL]);
int max_array[MAXCLIENTS][MAXCOL];
int available[MAXCLIENTS];
int need[MAXCLIENTS][MAXCOL];
int allocation[MAXCLIENTS][MAXCOL]; //allocation of clients 2d array
int ans[MAXCLIENTS];
int main(int argc, char *argv[])
{
    int n = 5;
    //print number of customers
    printf("Number of Customers: %d\n", n);
    //print currently available resources
    printf("Currently available resources:");
    for (int k = 1; k < argc; k++)
    {
        int int_val = atoi(argv[k]);
        available[k - 1] = int_val;
        printf("%d ", available[k - 1]);
    }

    printf("\nMaximum resources from file: \n");
    create_maximum_array(); //generate the maxarray 2d

    char word[MAXINPUT];
    char comm[MAXINPUT];
    char rq[MAXINPUT] = "RQ"; //request for resource
    char rl[MAXINPUT] = "RL"; //release resource
    char star[MAXINPUT] = "*\n";
    char run[MAXINPUT] = "run\n";
    char exit_str[MAXINPUT] = "exit\n";

    //ask banker for initial request for while loop to initially run
    printf("Enter Request: ");
    fgets(word, MAXINPUT, stdin);
    strcpy(comm, word);
    int start = 0;
    //main command logic, while not exit command
    while (strcmp(comm, exit_str) != 0)
    {
        if (start > 0)
        {
            printf("Enter Request: ");
            fgets(word, sizeof word, stdin);
            strcpy(comm, word);
        }
        //split input into words
        int total_words = 0;
        for (int w = 0; comm[w] != '\0'; w++)
        {
            if (comm[w] == ' ' || comm[w] == '\n' || comm[w] == '\t')
            {
                total_words++;
            }
        }

        /* initialize parser */
        char *token = strtok(comm, " ");
        // loop through the string to extract all other tokens
        char *input_string[MAXINPUT];

        int i = 0;
        if (total_words > 1)
        {
            while (token != NULL && i <= MAXCLIENTS)
            {
                input_string[i] = token; //printing each token
                token = strtok(NULL, " ");
                i += 1;
            }
        }
        else
        {
            strcpy(input_string[0], comm);
        }
        int length_string = i;
        i = 0;
        //parser end

        //main command parser
        //strcpy(comm,input_string[0]);

        //client asking for resource
        if (strcmp(input_string[0], rq) == 0)
        {
            //check to see if room for another client
            if (atoi(input_string[1]) >= MAXCLIENTS)
            {
                printf("Allocation array cannot be larger than Max clients\n");
                continue;
            }
            for (int x = 2; x < (length_string); x++)
            {
                //allocate client to allocation 2d array
                allocation[atoi(input_string[1])][x - 2] = atoi(input_string[x]);
            }
            printf("Request Successfull\n");
        }
        //release resource
        if (strcmp(input_string[0], rl) == 0)
        {
            printf("Release requested\n");
            int leave_if;
            for (int b = 2; b < (length_string); b++)
            {
                int release_val;
                //release value from allocation 2d array
                release_val = allocation[atoi(input_string[1])][b - 2] - atoi(input_string[b]);

                //error with release val
                if (release_val < 0)
                {
                    printf("Cannot Release\n");
                    leave_if = 1;
                    break;
                }
                else
                {
                    allocation[atoi(input_string[1])][b - 2] = release_val;
                    //printf("Release successful\n");
                }
            }
            if (leave_if == 1)
            {
                continue;
            }

            printf("Release Made\n");
        }
        //star command
        //to output the values of the different data structures
        if (strcmp(input_string[0], star) == 0)
        {
            printf("Got the star command\n");
            int i, j;
            printf("Available Array: ");
            for (i = 1; i < MAXCLIENTS; i++)
            {
                printf("%d ", available[i]);
            }

            printf("\nMaximum Array: \n");
            create_maximum_array();

            printf("Allocation Array: \n");
            for (i = 0; i < MAXCLIENTS; i++)
            {
                for (j = 0; j < MAXCOL; j++)
                {
                    printf("%d ", allocation[i][j]);
                }
                printf("\n");
            }
            printf("\n");

            printf("Need Array: \n");
            get_need_array(MAXCOL, MAXCLIENTS, allocation, max_array);
            for (i = 0; i < MAXCLIENTS; i++)
            {
                for (j = 0; j < MAXCOL; j++)
                {
                    printf("%d ", need[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        }
        //main run command
        //‘Run’ find the safe sequence and run each thread.
        if (strcmp(input_string[0], run) == 0)
        {
            printf("Got the run command\n");
            get_need_array(MAXCOL, MAXCLIENTS, allocation, max_array);
            int response = run_bankers(MAXCOL, MAXCLIENTS, allocation, max_array, available, need);
            if (response != 0)
            {
                printf("No safe sequence found\n");
                return(-1);
            }
            printf("Sequence found. %d\n", response);
            //for thread in threads:RQ
            for (int w = 0; w < MAXCLIENTS; w++)
            {
                int index = ans[w];
                printf("%d\n", index);
                pthread_t tid;
                
                pthread_create(&tid, NULL, threadRun, &index);
                pthread_join(tid, NULL);
            }
        }

        start += 1;
    }

    return (0);

    //chamnge to test b
}

int test()
{
    //show test
    return 1;
}

//thread run
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
//This function will take info from input file
//and put into 2d array max_array
void create_maximum_array()
{
    int count;

    FILE *fp = fopen(INPUTFILE, "r");

    for (int i = 0; i < MAXCLIENTS; i++)
    {
        for (count = 0; count < MAXCOL; count++)
        {
            fscanf(fp, "%d,", &max_array[i][count]);
        }
    }

    for (int i = 0; i < MAXCLIENTS; i++)
    {
        for (count = 0; count < MAXCOL; count++)
        {
            printf("%d ", max_array[i][count]);
        }
        printf("\n");
    }
    fclose(fp);
}

void get_need_array(int m, int n, int alloc[n][m], int max[n][m])
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

int run_bankers(int m, int n, int allocation[n][m], int max[n][m], int available[m], int need[n][m])
{
    int i, j, k;
    int safe = 1;

    int f[n], ind = 0;
    for (k = 0; k < n; k++)
    {
        f[k] = 0;
    }

    int y = 0;
    for (k = 0; k < m; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {

                int flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        available[y] += allocation[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        if (f[i] == 0)
        {
            safe = 0;
        }
    }

    if (safe == 0)
    {
        return (-1);
    }

    printf("Safe Sequence is: < ");
    for (i = 0; i < n - 1; i++)
        printf("%d ", ans[i]);
    printf("%d>\n", ans[n - 1]);

    return (0);
}