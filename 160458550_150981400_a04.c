#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define INPUTFILE "sample4_in.txt"
#define MAXCLIENTS 5
#define MAXCOL 4


void create_maximum_array();
//int run_bankersrun_bankers(MAXCLIENTS, MAXCOL, int alloc[MAXCLIENTS][MAXCOL], int max[MAXCLIENTS][MAXCOL], int avail[MAXCOL]);
int max_array[MAXCLIENTS][MAXCOL];
int available[50];
//int **allocation;
int allocation[MAXCLIENTS][MAXCOL];

int main(int argc, char *argv[]) 
{ 
    int n = 5;
    
    printf("Number of Customers: %d\n", n); // would like to dynamically get this data but am lazy
    printf("Currently available resources:");
    for(int k = 1; k < argc; k++){
        int int_val = atoi(argv[k]);
        available[k] = int_val;
        printf("%d ", available[k]); 
    }

    printf("\nMaximum resources from file: \n");
    create_maximum_array();
    
    char word[200];
    char comm[200];
    char rq[200] = "RQ";
    char rl[200] = "RL";
    char star[200] = "*";
    char run[200] = "run";
    char exit_str[200] = "exit";

    printf("Enter Request: ");
    fgets(word, sizeof word, stdin);
    strcpy(comm,word);
    int start = 0;

    while (strcmp(comm, exit_str) !=0) {
        if (start > 0){
            printf("Enter Request: ");
            fgets(word, sizeof word, stdin);
            strcpy(comm, word);
        }
        int total_words = 0;
        for(int w = 0; comm[w] != '\0'; w++)
        {
            if(comm[w] == ' ' || comm[w] == '\n' || comm[w] == '\t')
            {
                total_words+=1;	
            } 
        }	

        /* initialize parser */
        char *token = strtok(comm, " ");
        // loop through the string to extract all other tokens
        char *input_string[200];
        
        int i = 0;
        if (total_words > 1 ){
            while( token != NULL && i <= MAXCLIENTS) {
                input_string[i] = token;//printing each token
                token = strtok(NULL, " ");
                i += 1;
            }
        }
        else{
            strcpy(input_string[0], comm);
        }
        int length_string = i;
        i = 0;
        
        //strcpy(comm,input_string[0]);
        if (strcmp(input_string[0], rq) == 0){
            if (atoi(input_string[1]) >= MAXCLIENTS){
                printf("Allocation array cannot be larger than Max \n");
                continue;
            }
            for (int x = 2; x < (length_string); x++){
                allocation[atoi(input_string[1])][x] = atoi(input_string[x]);
            }
        }

        if (strcmp(input_string[0], rl) == 0) {
            printf("Got the RL command\n");

        } 

        if (strcmp(input_string[0], star) == 0) {
            printf("Got the star command\n");

        } 

        if (strcmp(input_string[0], run) == 0) {
            printf("Got the run command\n");
            int response = run_bankers(MAXCOL, MAXCLIENTS, allocation, max_array, available);

        }

        start += 1;

    } 

    //run_bankers(max_array);
    //int available = argv;

    // use create maximum array to parse sample in file to create max matrix
    // once program is loaded with max array, take in argument gievn at the start for allocation. store the allocation data. 
    //respond with a paramer as, create cases for 4 inputs from assingment example
    return (0); 
} 


void create_maximum_array(){
    int count;

	FILE* fp = fopen(INPUTFILE, "r");

	for(int i = 0; i < MAXCLIENTS; i++)
	{
	    for(count = 0; count < MAXCOL; count++)
	    {
	        fscanf(fp, "%d,", &max_array[i][count]);
           
	    }
        
	}

	for(int i = 0; i < MAXCLIENTS; i++)
	{
	    for(count = 0; count < MAXCOL; count++)
	    {
	        printf("%d ",max_array[i][count]);
	    }
        printf("\n");
	}
}

int run_bankers(int m, int n, int alloc[n][m], int max[n][m], int avail[m]){
    int i, j, k; 

    int f[n], ans[n], ind = 0; 
    for (k = 0; k < n; k++) { 
        f[k] = 0; 
    } 
    int need[n][m]; 
    for (i = 0; i < n; i++) { 
        for (j = 0; j < m; j++) 
            need[i][j] = max[i][j] - alloc[i][j]; 
    } 
    int y = 0; 
    for (k = 0; k < 5; k++) { 
        for (i = 0; i < n; i++) { 
            if (f[i] == 0) { 
  
                int flag = 0; 
                for (j = 0; j < m; j++) { 
                    if (need[i][j] > avail[j]){ 
                        flag = 1; 
                         break; 
                    } 
                } 
  
                if (flag == 0) { 
                    ans[ind++] = i; 
                    for (y = 0; y < m; y++) 
                        avail[y] += alloc[i][y]; 
                    f[i] = 1; 
                } 
            } 
        } 
    } 
  
    printf("Safe Sequence is: < "); 
    for (i = 0; i < n - 1; i++) 
        printf("%d ", ans[i]); 
    printf("%d>\n", ans[n - 1]); 
  
    return (0); 
}