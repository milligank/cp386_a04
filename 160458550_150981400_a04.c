#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


void create_maximum_array();
int** max_array;
int available[50];
int **allocation;

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
    
    char word[100];
    int l = 5;
    allocation = malloc(l * sizeof(*allocation));

    do {
        printf("Enter Request: ");
        /* read from stdin 
        note the `sizeof char`, if you need to change the size of `word`,
        you won't have to change this line. */
        fgets(word, sizeof word, stdin);

        /* initialize parser */
        char *token = strtok(word, " ");
        // loop through the string to extract all other tokens
        char *input_string[200];
        char rq[15] = "RQ";
        int i = 0;
        while( token != NULL ) {
            input_string[i] = token;//printing each token
            token = strtok(NULL, " ");
            i += 1;
        }
        int length_string = i;
        i = 0;

        char comm[20];
        strcpy(comm,input_string[0]);
        int rq_row = 0;
        if (strcmp(comm, rq) == 0){
            if (rq_row > 4){
                printf("Allocation array cannot be larger than Max");
                continue;
            }
            for (int x = 1; x < length_string; x++){
                allocation[rq_row][x] = atoi(input_string[x]);
                printf("%d \n", allocation[rq_row][x]);
            }
            rq_row += 1;
        }
    } while (strcmp(word,"EXIT") !=0);

    //run_bankers(max_array);
    //int available = argv;

    // use create maximum array to parse sample in file to create max matrix
    // once program is loaded with max array, take in argument gievn at the start for allocation. store the allocation data. 
    //respond with a paramer as, create cases for 4 inputs from assingment example
    return (0); 
} 


void create_maximum_array(){

    int n = 5;

	max_array = malloc(n * sizeof(*max_array)); /* Assuming `n` is the number of rows */
	
	int count = 1;
	for(int i = 0; i < n; i++)
	{
	    max_array[i] = malloc(count * sizeof(**max_array));
	    count++;
	}

	FILE* fp = fopen("sample4_in.txt", "r");

	int max = 4;

	for(int i = 0; i < n; i++)
	{
	    for(count = 0; count < max; count++)
	    {
	        fscanf(fp, "%d,", &max_array[i][count]);
           
	    }
        
	}

	max = 4;

	for(int i = 0; i < n; i++)
	{
	    for(count = 0; count < max; count++)
	    {
	        printf("%d,",max_array[i][count]);
	    }
        printf("\n");
	}

	for(int i = 0; i < n; i++)
	{
	   free(max_array[i]); 
	}
	free(max_array);
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
  
    printf("Following is the SAFE Sequence\n"); 
    for (i = 0; i < n - 1; i++) 
        printf(" P%d ->", ans[i]); 
    printf(" P%d", ans[n - 1]); 
  
    return (0); 
}