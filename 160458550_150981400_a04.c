#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define INPUTFILE "sample4_in.txt"
#define MAXINPUT 200
#define MAXCLIENTS 5
#define MAXCOL 4


void create_maximum_array();
int run_bankers(int, int, int alloc[MAXCLIENTS][MAXCOL], int max[MAXCLIENTS][MAXCOL], int avail[MAXCOL], int need[MAXCLIENTS][MAXCOL]);
void get_need_array(int, int , int alloc[MAXCLIENTS][MAXCOL], int max[MAXCLIENTS][MAXCOL]);
int max_array[MAXCLIENTS][MAXCOL];
int available[MAXCLIENTS];
int need[MAXCLIENTS][MAXCOL]; 
int allocation[MAXCLIENTS][MAXCOL];

int main(int argc, char *argv[]) 
{ 
    int n = 5;
    
    printf("Number of Customers: %d\n", n); // would like to dynamically get this data but am lazy
    printf("Currently available resources:");
    for(int k = 1; k < argc; k++){
        int int_val = atoi(argv[k]);
        available[k-1] = int_val;
        printf("%d ", available[k-1]); 
    }

    printf("\nMaximum resources from file: \n");
    create_maximum_array();
    
    char word[MAXINPUT];
    char comm[MAXINPUT];
    char rq[MAXINPUT] = "RQ";
    char rl[MAXINPUT] = "RL";
    char star[MAXINPUT] = "*\n";
    char run[MAXINPUT] = "run\n";
    char exit_str[MAXINPUT] = "exit\n";

    printf("Enter Request: ");
    fgets(word, MAXINPUT, stdin);
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
                total_words++;	
            } 
        }	

        /* initialize parser */
        char *token = strtok(comm, " ");
        // loop through the string to extract all other tokens
        char *input_string[MAXINPUT];
        
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
                printf("Allocation array cannot be larger than Max clients\n");
                continue;
            }
            for (int x = 2; x < (length_string); x++){
                allocation[atoi(input_string[1])][x-2] = atoi(input_string[x]);
            }
        }

        

        if (strcmp(input_string[0], rl) == 0) {
            int leave_if;
            for (int b = 2; b < (length_string); b++){
                int release_val;
                release_val = allocation[atoi(input_string[1])][b-2] - atoi(input_string[b]);

                if (release_val < 0){
                    printf("Cannot Release\n");
                    leave_if = 1;
                    break;
                }else{
                    allocation[atoi(input_string[1])][b-2] = release_val;
                }
            }
            if (leave_if ==1 ){
                continue;
            }

            printf("Release Made\n");


        } 

        if (strcmp(input_string[0], star) == 0) {
            printf("Got the star command\n");
            int i, j;
            printf("Available Array: ");
            for (i = 1; i < MAXCLIENTS; i++){
                printf("%d ", available[i]); 
            }

            printf("\nMaximum Array: \n");
            create_maximum_array();

            printf("Allocation Array: \n");
            for (i = 0; i < MAXCLIENTS; i++) { 
                for (j = 0; j < MAXCOL; j++) {
                    printf("%d ", allocation[i][j]);
                }
                printf("\n");
        
            }
            printf("\n");

            printf("Need Array: \n");
            get_need_array(MAXCOL, MAXCLIENTS, allocation, max_array);
            for (i = 0; i < MAXCLIENTS; i++) { 
                for (j = 0; j < MAXCOL; j++) {
                    printf("%d ", need[i][j]);
                }
                printf("\n");
        
            }
            printf("\n");

        } 

        if (strcmp(input_string[0], run) == 0) {
            printf("Got the run command\n");
            get_need_array(MAXCOL, MAXCLIENTS, allocation, max_array);
            int response = run_bankers(MAXCOL, MAXCLIENTS, allocation, max_array, available, need);
            if (response != 0) {
                printf("No safe sequence found\n");
            }

        }

        start += 1;

    } 

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

void get_need_array(int m, int n, int alloc[n][m], int max[n][m]){
    int i, j;
    
    for (i = 0; i < n; i++) { 
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j]; 
        }
        
    }
}

int run_bankers(int m, int n, int allocation[n][m], int max[n][m], int available[m], int need[n][m]){
    int i, j, k; 
    int safe = 1;

    int f[n], ans[n], ind = 0; 
    for (k = 0; k < n; k++) { 
        f[k] = 0; 
    } 

    int y = 0; 
    for (k = 0; k < m; k++) { 
        for (i = 0; i < n; i++) { 
            if (f[i] == 0) { 
  
                int flag = 0; 
                for (j = 0; j < m; j++) { 
                    if (need[i][j] > available[j]){ 
                        flag = 1; 
                        break; 
                    } 
                } 
  
                if (flag == 0) { 
                    ans[ind++] = i; 
                    for (y = 0; y < m; y++) 
                        available[y] += allocation[i][y]; 
                    f[i] = 1; 
                } 
            } 
        } 
    } 

    for (i = 0; i<n; i++){
        if (f[i] == 0){
            safe = 0;
        }
    }

    if (safe == 0) {
        return (-1);
    }
  
    printf("Safe Sequence is: < "); 
    for (i = 0; i < n - 1; i++) 
        printf("%d ", ans[i]); 
    printf("%d>\n", ans[n - 1]); 
  
    return (0); 
}