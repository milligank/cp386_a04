#include <stdio.h> 
#include <stdlib.h>

int** max_array;

int main(int argc, char *argv[]) 
{ 
    int n = 5;
    
    printf("Number of Customers: %d\n", n); // would like to dynamically get this data but am lazy
    printf("Currently available resources:");
    for(int k = 1; k < argc; k++)
         printf("%s ", argv[k]);
    printf("\nMaximum resources from file: \n");
    create_maximum_array();

    printf("Enter a command: ");
    //scanf("%d", &testInteger); 

    //run_bankers(max_array);
    //int available = argv;

    // use create maximum array to parse sample in file to create max matrix
    // once program is loaded with max array, take in argument gievn at the start for allocation. store the allocation data. 
    //respond with a paramer as, create cases for 4 inputs from assingment example
    return (0); 
} 


int create_maximum_array(){

    int n = 5;

	max_array = malloc(n * sizeof(*max_array)); /* Assuming `n` is the number of rows */
	if(!max_array) /* If `malloc` failed */
	{
	    fputs(stderr, "Error");
	    exit(-1);
	}

	int count = 1;
	for(int i = 0; i < n; i++)
	{
	    max_array[i] = malloc(count * sizeof(**max_array));
	    if(!max_array[i]) /* If `malloc` failed */
	    {
	        for(int j = 0; j < i; j++) /* free previously allocated memory */
	        {
	            free(max_array[j]); 
	        }
	        free(max_array);

	        fputs(stderr, "Error");
	        exit(-1);
	    }
	    count++;
	}

	// Then, read data from the file into the array by using:

	FILE* fp = fopen("sample4_in.txt", "r");
	if(!fp)
	{
	   for(int i = 0; i < n; i++) /* free previously allocated memory */
	   {
	      free(max_array[i]); 
	   }
	   free(max_array);

	   fputs(stderr, "Error");
	   exit(-1);
	}

	int max = 4;

	for(int i = 0; i < n; i++)
	{
	    for(count = 0; count < max; count++)
	    {
	        fscanf(fp, "%d,", &max_array[i][count]);
           
	    }
	    
        
	}

	// Then print the results:

	max = 4;

	for(int i = 0; i < n; i++)
	{
	    for(count = 0; count < max; count++)
	    {
	        printf("%d,",max_array[i][count]);
	    }
        printf("\n");
	}

	// And finally, free the allocated memory:

	for(int i = 0; i < n; i++)
	{
	   free(max_array[i]); 
	}
	free(max_array);
    return 0;
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