#include <stdio.h> 

int** array;
int main(int argc, char *argv[]) 
{ 
    //create_maximum_array();
    //run_bankers()

    // use create maximum array to parse sample in file to create max matrix
    // once program is loaded with max array, take in argument gievn at the start for allocation. store the allocation data. 
    //respond with a paramer as, create cases for 4 inputs from assingment example
    return (0); 

    //chamnge to test b
} 

int test(){
    //show test 
}

//may not need to use, checking with prof
int create_maximum_array(){
    //max[amount of rows][length of rows]
    
    int n = 5;

	array = malloc(n * sizeof(*array)); /* Assuming `n` is the number of rows */
	if(!array) /* If `malloc` failed */
	{
	    fputs(stderr, "Error");
	    exit(-1);
	}

	int count = 1;
	for(int i = 0; i < n; i++)
	{
	    array[i] = malloc(count * sizeof(**array));
	    if(!array[i]) /* If `malloc` failed */
	    {
	        for(int j = 0; j < i; j++) /* free previously allocated memory */
	        {
	            free(array[j]); 
	        }
	        free(array);

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
	      free(array[i]); 
	   }
	   free(array);

	   fputs(stderr, "Error");
	   exit(-1);
	}

	int max = 1;

	for(int i = 0; i < n; i++)
	{
	    for(count = 0; count < max; count++)
	    {
	        fscanf(fp, "%d", &array[i][count]);
	    }
	    max++;
	}

	// Then print the results:

	max = 1;

	for(int i = 0; i < n; i++)
	{
	    for(count = 0; count < max; count++)
	    {
	        printf("array[%d][%d] = %d", i, count, array[i][count]);
	    }
	    max++;
	}

	// And finally, free the allocated memory:

	for(int i = 0; i < n; i++)
	{
	   free(array[i]); 
	}
	free(array);
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