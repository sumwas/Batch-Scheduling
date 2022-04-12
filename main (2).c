#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //for max function

// declare global variables including a table structure to hold scheduling information
int num_processes;

struct node {
    int id;
    int arrival;
    int total_cpu;
    int total_remaining;
    int done;
    int start_time;
    int already_started;
    int end_time;
    int turnaround_time;
}* table_ptr = NULL;

typedef struct node table_type;

// optional: define a function that finds the maximum of two integers
#define max(a,b) ( a > b ? a : b )

//***************************************************************
void printTable() {
	// declare local variables
	// print table header 	
	printf("ID\tArrival\tTotal\tStart\tEnd\tTurnaround\n");
	printf("--------------------------------------------------\n");
	// for each process from 0 up to but not including num_processes
	for (int i=0; i<num_processes; i++){
		// print the contents (id, arrival time, total_cycles) of each field of the table's index 
		printf("%d\t", table_ptr[i].id);
		printf("%d\t", table_ptr[i].arrival);
		printf("%d\t", table_ptr[i].total_cpu);
		// if process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time) 
		if (table_ptr[i].done == 1){
		    printf("%d\t", table_ptr[i].start_time);
		    printf("%d\t", table_ptr[i].end_time);
		    printf("%d\t", table_ptr[i].turnaround_time);
		}
		printf("\n");
	}//end for loop
	return;
}


//*************************************************************
void option1() {
	// declare local variables 
	int id; 
	int arrival_time;
	int total_cycles;
	
	// prompt for total number of processes 	
	printf("Enter maximum number of processes: ");
    scanf("%d" , &num_processes);
    
	// allocate memory for table to hold process parameters 
	table_ptr = (table_type*)malloc(num_processes * sizeof(table_type));
	
	// for each process index from 0 up to but not including num_processes
	for (int i=0; i < num_processes; i++){
		// prompt for process id, arrival time, and total cycle time 
		printf("Enter process id: ");
		scanf("%d", &id);
		table_ptr[i].id = id;
		printf("Enter arrival cycle for Process %d: " , id);
		scanf("%d", &arrival_time);
		table_ptr[i].arrival = arrival_time;
		printf("Enter total cycles for Process %d: " , id);
		scanf("%d", &total_cycles);
		table_ptr[i].total_cpu = total_cycles;
	}
	// print contents of table 
	printTable();
	return;		
}	

// p0: 1092
// p1: 1093
// p2: 1091      <- just teacher example

//*************************************************************
void option2() {
	// declare (and initilize when appropriate) local variables 
	int num_done = 0;
	int earliest_time;
	int earliest_index;
	int current_cycle = 0;
	
	// for each process, reset "done" field to 0 
	for (int j = 0; j<num_processes; j++){
	    table_ptr[j].done = 0;
	}//for loop
	
	// while there are still processes to schedule 	
	while (num_done < num_processes){
		// initilize the earliest arrival time to INT_MAX (largest integer value) 
		earliest_time = INT_MAX;
		// for each process not yet scheduled 
		for (int i = 0; i < num_processes; i++){
		    if (table_ptr[i].done == 0){ //not done yet
			    // check if process has earlier arrival time than current earliest and update 	
			    if (table_ptr[i].arrival < earliest_time ){
			        earliest_time = table_ptr[i].arrival;
			        earliest_index = i;
			    } // if earlier arrival time
		    } //if not already scheduled
		}// for loop
		// set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time   
		table_ptr[earliest_index].start_time = max(current_cycle,table_ptr[earliest_index].arrival) ;
		table_ptr[earliest_index].end_time = table_ptr[earliest_index].start_time + table_ptr[earliest_index].total_cpu;
		table_ptr[earliest_index].turnaround_time = table_ptr[earliest_index].end_time - table_ptr[earliest_index].arrival ;
		table_ptr[earliest_index].done = 1 ;
		// update current cycle time and increment number of processes scheduled 
		num_done++;
		current_cycle = table_ptr[earliest_index].end_time;
	}//while loop
	
	// print contents of table 
	printTable();
	return;		
}	


//*************************************************************
void option3() {
	// declare (and initilize when appropriate) local variables 
    int num_done = 0;
	int earliest_time;
	int earliest_index;
	int current_cycle = 0;
	int at_least_one;
	
	// for each process, reset "done" field to 0 
	for (int i = 0; i<num_processes; i++){
	    table_ptr[i].done = 0;
	}//for loop
	
	// while there are still processes to schedule 	
	while (num_done < num_processes){
		// initilize the earliest arrival time to INT_MAX (largest integer value) 
		earliest_time = INT_MAX;
		// at_least_one flag to initilize
		at_least_one = 0;
		// for each process not yet scheduled 
		for (int i = 0; i < num_processes; i++){
		    if (table_ptr[i].done == 0){ //not done yet
			    // check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update 
			    if ( (table_ptr[i].total_cpu < earliest_time) && (table_ptr[i].arrival <= current_cycle) ){
			        earliest_time = table_ptr[i].total_cpu;
			        earliest_index = i;
			        at_least_one = 1;
			    } // if earlier arrival time
		    } //if not already scheduled
		}// for loop
		
		// one mroe thing to check
		if(at_least_one == 0){
		    current_cycle++;
	    }
		else {
		    // set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time   
		    table_ptr[earliest_index].start_time = max(current_cycle,table_ptr[earliest_index].arrival) ;
		    table_ptr[earliest_index].end_time = table_ptr[earliest_index].start_time + table_ptr[earliest_index].total_cpu;
		    table_ptr[earliest_index].turnaround_time = table_ptr[earliest_index].end_time - table_ptr[earliest_index].arrival ;
		    table_ptr[earliest_index].done = 1 ;
		    // update current cycle time and increment number of processes scheduled 
		    num_done++;
		    current_cycle = table_ptr[earliest_index].end_time;
		}
	}//while loop
	
	// print contents of table 
	printTable();
	return;		
}	
        	

//*************************************************************
void option4() {
    // declare (and initilize when appropriate) local variables 
    int num_done = 0;
	int earliest_time;
	int earliest_index;
	int current_cycle = 0;
	int at_least_one;
	
	// for each process, reset "done", "total_remaining" and "already_started" fields to 0 
	for (int j = 0; j<num_processes; j++){
	    table_ptr[j].done = 0;
	    table_ptr[j].total_remaining = table_ptr[j].total_cpu;
	    table_ptr[j].already_started = 0;
	}//for loop
	
	// while there are still processes to schedule 	
	while (num_done < num_processes){
		// initilize the lowest total remaining time to INT_MAX (largest integer value) 
		earliest_time = INT_MAX;
		// at_least_one flag to initilize
		at_least_one = 0;
		// for each process not yet scheduled 
		for (int i = 0; i < num_processes; i++){
		    if (table_ptr[i].done == 0){ //not done yet
			    // check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update 
			    if ( (table_ptr[i].total_remaining < earliest_time) && (table_ptr[i].arrival <= current_cycle) ){
			        earliest_time = table_ptr[i].total_remaining;
			        earliest_index = i;
			        at_least_one = 1;
			    } // if shorter remaining time
		    } //if not already scheduled
		}// for loop
		
		// check if process already partially-scheduled 
			// if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time       
			
		// one mroe thing to check
		if(at_least_one == 0){
		    current_cycle++;
	    }
		else {
		    // set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time   
		    if (table_ptr[earliest_index].already_started == 0){
		        table_ptr[earliest_index].already_started = 1;
		        table_ptr[earliest_index].start_time = max(table_ptr[earliest_index].arrival, current_cycle) ;
		        //table_ptr[earliest_index].end_time = table_ptr[earliest_index].start_time
		        //table_ptr[earliest_index].turnaround_time = table_ptr[earliest_index].end_time - table_ptr[earliest_index].arrival_time ;
		    }
		    table_ptr[earliest_index].end_time = current_cycle+1;
		    table_ptr[earliest_index].turnaround_time = table_ptr[earliest_index].end_time - table_ptr[earliest_index].arrival ;
		    table_ptr[earliest_index].total_remaining--;
	        
	        
		// update current cycle time and increment number of processes scheduled 
		    if (table_ptr[earliest_index].total_remaining == 0){
		        table_ptr[earliest_index].done = 1 ;
		        num_done++;
		        // else 
		    }
		    current_cycle++;
		}
	}//while loop
	
	// print contents of table 
	printTable();
	return;		
}	
        	

//*************************************************************
void option5() {
	// free the schedule table if not NULL 
	if (table_ptr != NULL){
	    free(table_ptr);
	}
	return;
}


//*************************************************************
int main() {
	
	/* declare local vars */
    int choice = 0;
    /* while user has not chosen to quit */
    while (choice != 5) {
        /* print menu of options */
        printf("\nBatch scheduling \n----------------\n1) Enter parameters \n2) Schedule processes with FIFO algorithm \n3) Schedule processes with SJF algorithm \n4) Schedule processes with SRT algorithm \n5) Quit and free memory  \n");
        /* prompt for menu selection */
        printf("\nEnter selection: ");
        scanf("%d" , &choice);
        
        /* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */
        if (choice == 1){
            option1();
        }
        else if (choice == 2){
            option2();
        }
        else if (choice == 3){
            option3();
        }
        else if (choice == 4){
            option4();
        }
        else if (choice == 5){
            option5();
        }
        else {
            printf("Invalid Option\n");
        }
        
    } /* while loop */
	 return 1; // indicates success 
} // end of procedure 







