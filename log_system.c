/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: Julie Hinge
 * Student ID: 13851629
 * Date of submission: 06/10/2022
 * A brief statement on what you could achieve (less than 50 words):
 * I was able to create an array of employee structures where the user could either add 
 * or delete an employee. They could also display the employeelist and save it or view it
 * from a file.
 * A brief statement on what you could NOT achieve (less than 50 words):
 * As far as I know, I was able to complete all the requirements.
 * 
*******************************************************************************/
/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h> /* printf, scanf */
#include <string.h>
/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/
#define MAX_COMPANY_SIZE 5
#define MAX_NAME_SIZE 11
/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
/* Making a nested structure of the employee and the employee birthday */
struct employee{
    char name[MAX_NAME_SIZE];
    double fte;
    unsigned int level;
    struct date{
        unsigned int day;
        unsigned int month;
        unsigned int year;
    }date_t;
};   

/*defining the structure;*/
typedef struct employee employee_t;

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
/*printing the menu of options */
void printMenu(void);
/*scanning the option from the user */
int scanChoice();
/*adding an employee to the employee list */
int add_employee(employee_t *, int);
/* displaying the employee list to the terminal*/
void printEmployees(employee_t *, int);
/* deleting the last employee from the employee list */
int _delete(employee_t *, int );
/* saving the employee list to a file */
int save_emptarr(employee_t *, char *filename, int);
/* reading in the employee list into an array from the file*/
int read_emptarr(char filename[], employee_t *);

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void){
	
	/* num_alloc indicated the current number of employees in the company */
	int num_alloc = 0;
	/* defining the employee array*/
    employee_t emp_array[MAX_COMPANY_SIZE];

	/* printing the user menu and taking input from the user */
    printMenu();
	int c = scanChoice();

    /*while loop that executed a function depending on the users input until the user inputs 6 */

	while (c != 6){
		if(c == 1){
			num_alloc = add_employee(emp_array, num_alloc);
		}
        else if(c==2){
            num_alloc = _delete(emp_array, num_alloc);
        }
		else if(c == 3){
			printEmployees(emp_array, num_alloc);
		}
		else if(c==4){
			save_emptarr(emp_array, "database.txt", num_alloc);
		}
		else if(c==5){
			num_alloc = read_emptarr("database.txt", emp_array);
		}
        else if (c < 1 || c > 6){
			printf("Invalid choice.");
		}
		else if(c==6){
			exit(0);
		}

        printMenu();
		c = scanChoice();
	}
    return 0;
}
/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void printMenu(void){
    printf("\n\n"
     "1. add employee\n"
     "2. delete last employee\n"
     "3. display employee list\n"
     "4. save the employee list to the database\n"
     "5. read the employee list from the database\n"
     "6. exit the program\n");
}

/*******************************************************************************
 * This function takes the input from the user and returns it
 * inputs:
 * - none
 * outputs:
 * - The choice of the user
*******************************************************************************/
int scanChoice(){
    int choice;
    printf("Enter your choice>\n");
	/* saving the user's choice to a variable and returning it from the function */
    scanf("%d", &choice);
    return choice;
}
/*******************************************************************************
 * This function adds an employee struct to the employee array by taking inputs from
 * the user about the employee.
 * inputs:
 * - employee array and the number of employees already in the company
 * outputs:
 * - none
*******************************************************************************/
int add_employee(employee_t *employee, int num){

	/* If the company is at capacity, we return a message informing the user */
	if (MAX_COMPANY_SIZE <= num) {
		printf("List is full");
	}


	else{
		/* getting the name from the user, while escaping special characters */
		printf("Enter name>");	
		scanf(" %[^\t\n]s", employee[num].name);

		/*Getting the day from the user while making sure that it is valid */
		printf("Enter birthday: day>");
		scanf("%u", &employee[num].date_t.day);
		while (employee[num].date_t.day < 1 ||employee[num].date_t.day > 31){
			printf("Invalid day. Enter birthday: day>");
			scanf("%u", &employee[num].date_t.day);
		}

		/*Getting the month from the user while making sure that it is valid */
		printf("Enter birthday: month>");
		scanf("%u", &employee[num].date_t.month);
		while (employee[num].date_t.month < 1 ||employee[num].date_t.month > 12){
			printf("Invalid month. Enter birthday: month>");
			scanf("%u", &employee[num].date_t.month);
		}

		
		/*Getting the year from the user while making sure that it is valid */
		printf("Enter birthday: year>");
		scanf("%u", &employee[num].date_t.year);
		while (employee[num].date_t.year < 1800 ||employee[num].date_t.year > 2018){
			printf("Invalid year. Enter birthday: year>");
			scanf("%u", &employee[num].date_t.year);
		}

		/*Getting the year from the user while making sure that it is valid */
		printf("Enter FTE>");
		scanf("%lf", &employee[num].fte);
		while(employee[num].fte < 0 || employee[num].fte > 1){
			printf("Invalid FTE. Enter FTE>");
			scanf("%lf", &employee[num].fte);
		}

		/*Getting the level from the user while making sure that it is valid */
		printf("Enter level>");
		scanf("%u", &employee[num].level);
		while (employee[num].level < 7 ||employee[num].level > 18){
			printf("Invalid level. Enter level>");
			scanf("%u", &employee[num].level);
		}
	}

    /* incrementing the number of employees in the employee list since an employee has been added */
	num++;
	return num;
}


/*******************************************************************************
 * This function prints the information about each employee and formats it in
 * a table form.
 * inputs:
 * - employee array and the number of employees already in the company
 * outputs:
 * - none
*******************************************************************************/

void printEmployees(employee_t *emp_array, int num){
	int i;
	int j;
    /* If the employeelist is not empty, we display the list */
	if (num > 0){
		printf("Name       Birthday   FTE   Level\n");
		printf("---------- ---------- ----- -----\n");
    	for(i = 0; i < num; i++) {

            
            /*Making sure that the program does not display the full employee name if it is over 10 characters*/
			int len = strlen(emp_array[i].name);
			if (len >= 10) printf("%.*s ", 10, emp_array[i].name);
			else printf("%s", emp_array[i].name);
			
            /*Printing spaces between the employee name and the birthday*/
			for(j = 0; j < 11-len; j++){
				printf(" ");
			}
            
           /*printing the employee birthday in the correct format */
			printf("%02u-%02u-%u ", 
			emp_array[i].date_t.day, 
			emp_array[i].date_t.month, 
			emp_array[i].date_t.year);
            
            /*printing the employee fte in the correct format */
            printf("%.03lf ", emp_array[i].fte);
           
            /*printing the employee level in the correct format */
			printf("%02u\n", emp_array[i].level);
    	}
 	 }

    /*If the list is empty, we return a message to the user*/
    else printf("List is empty");

}




/*******************************************************************************
 * This function deletes the last employee in the employee array unless the
 * array is empty. If the array is empty it returns the message "List is empty"
 * inputs:
 * - employee array and the number of employees already in the company
 * outputs:
 * - none
*******************************************************************************/
int _delete(employee_t *emp_array, int num){
	if (num > 0){
		int i;
		for(i = 0; i < num; i++){
			for (i = 0; i <  MAX_COMPANY_SIZE - 1; i++){
                /* Shifting all elements in the array to delete the employee*/
				emp_array[i+1] = emp_array[i];
			}
		}
        /* decrementing the number of employees in the employee list since an employee has been deleted */
		num--;
	}
	else{
		printf("List is empty");
	}
	return num;
}

/*******************************************************************************
 * This function saves the employee array to a file.
 * inputs:
 * - employee array and the name of the file.
 * outputs:
 * - 1 if the file is unable to be created otherwise 0
*******************************************************************************/
int save_emptarr(employee_t *emp_array, char *filename, int num){
    int i;

    /* Make file pointer */
    FILE *file = NULL;

    /* Opening the file in write mode */
    file = fopen(filename, "w");

    /* Makes sure file exists */
    if(file == NULL)
    {
        printf("Unable to create file.\n");
        return 1;
    }

    /* Writes all employees to the file */
    for(i=0;i<num;i++){
        fprintf(file, "%s %u %u %u %lf %u", 
        emp_array[i].name, 
        emp_array[i].date_t.day, 
        emp_array[i].date_t.month, 
        emp_array[i].date_t.year, 
        emp_array[i].fte,
         emp_array[i].level);
    }
    
    /* Closes the file */
    fclose(file);


    return 0;
}





/*******************************************************************************
 * This function reads the employee array from the file and scans it into an
 * array of structs.
 * inputs:
 * - name of the file, employee array and the number of employees already in the company
 * outputs:
 * - none
*******************************************************************************/

int read_emptarr(char filename[], employee_t *emp_array){
	
	int num = 0;
	
    /* Opening the file in read mode */
	FILE *file = fopen(filename, "r");

    /* Making sure the file can be opened */
	if(file == NULL){
		printf("Read error");
		return 0;
    }

    /* scanning every line of the file into employee array until end of file and incrementing i for every employee*/
	while(fscanf(file, "%s %u %u %u %lf %u",
        emp_array[num].name, 
        &emp_array[num].date_t.day,
        &emp_array[num].date_t.month,
        &emp_array[num].date_t.year,
        &emp_array[num].fte, 
        &emp_array[num].level)!=EOF){
		num++;   	
	}

	fclose(file);

    /* Returning the total number of employees */
	return num;
}