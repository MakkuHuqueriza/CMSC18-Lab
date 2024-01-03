#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to record student records
typedef struct s_record {
    char surname[30];
    char sex;
    int year;
    int Snum;
    char Department[30];
}s_record;

// Function that displays introductory message about the program
void display();

// Function that gets user-input for choice of action
int choiceforUser();

// Function that gets user-input after the choice of action
int innerchoiceforUser();

// Function that gets user-input for number of students to include in the record
int num_of_student();

// Function to create a dynamic array for student records
s_record *create_database(int num);

// Function that collects user-input information for each student
void ask_student_Info(int n, s_record student[]);

// Function to allocate memory for an array from the database file
s_record *allocarray();

// Function that displays student records
void display_s_Info(s_record *);

int main(){

    int num, choice;
    s_record *student_list;

    display(); // Calls display function and displays introductory message
    while(1){
        choice = choiceforUser(); // Calls choiceforUser function and gets user's choice
        switch(choice){
            
            // Exiting program if user-input is 0
            case 0:
                printf("\nExiting program...");
                return 0;
                break;
            
            // Adding a new student record if user-input is 1
            case 1: 

                // Calling num_of_student function to get the number of students    
                num = num_of_student();

                // Calling create_database function to create a dynamic array for student records
                student_list = create_database(num);

                // Calling ask_student_Info function to collect information for each student 
                ask_student_Info(num, student_list); 

                // Free allocated memory from array
                free(student_list); 
                
                // Calling innerchoiceforUser function to ask user if they want to perform more actions
                innerchoiceforUser(); 
                break;

            // Displaying current student records if user-input is 2
            case 2:

                // Calling allocarray function to allocate for an array from the database file
                student_list = allocarray();

                // Calling display_s_Info function to display student records
                display_s_Info(student_list);

                // Free allocated memory from array
                free(student_list); 

                // Calling innerchoiceforUser function to ask user if they want to perform more actions
                innerchoiceforUser();
                break;

            // Printing Message if user-input is an invalid output
            default:
                printf("\n\tInvalid Input!\n");
                break;
        }
    }
}

// Function that displays introductory message about the program
void display(){
	printf("\n=================================================================================================================\n");
	printf("THIS PROGRAM IS A SIMPLE STUDENT RECORDS THAT STORES THE DATA INPUTTED BY THE USER TO A TEXT FILE AS A DATABASE.\n");
    printf("UNANTICIPATED USER ACTIONS OR INPUTS MAY LEAD TO BUGS OR THE TERMINATION OF THE PROGRAM.\n");
	printf("=================================================================================================================\n");
}

// Function that gets user-input for choice of action
int choiceforUser(){
    int choice;
    
    printf("\n\tUSER CHOICES (Select among the options available)\n");
    printf("\t\t[1] Add Record\n");
    printf("\t\t[2] Display All Records\n");
    printf("\t\t[0] Exit\n");
    printf("\tChoice: ");
    scanf("%d", &choice);

    return choice;
}

// Function that gets user-input after the choice of action
int innerchoiceforUser(){
    char innerchoice;
    printf("\n-----------------------------------------------------------------------------------------------------------------\n");
    printf("\nWould you like to perform other actions?\n");
    printf("\tInput [Y] or [y] for YES \n");
    printf("\tAny character for NO \n");
    printf("\tChoice: ");
    scanf(" %c", &innerchoice);

    if(innerchoice == 'Y' || innerchoice == 'y'){
        system("cls");
        display();
    }
    else{
        printf("\nExiting program...");
        exit(0);
    }
}

// Function that gets user-input for number of students to include in the record
int num_of_student(){
    system("cls");
    int num;
	printf("\nHow many students do you want to include in the student record?");
	printf("\nEnter number here: ");
	scanf("%d", &num);
	return num;
}

// Function to create a dynamic array for student records
s_record *create_database(int num)
{
	s_record *student_list = (s_record *)malloc(sizeof(s_record) * num);
	return student_list;
}

// Function that collects user-input information for each student
void ask_student_Info(int n, s_record student[]){

    FILE *firstfile = fopen("display.csv", "a");
    if(firstfile == NULL){
        printf("Error in opening file\n");
        exit(1);
    }

    FILE *secondfile = fopen("database.csv", "a");
    if(secondfile == NULL){
        printf("Error in opening file\n");
        exit(1);
    }

    FILE *bufferfile = fopen("display.csv", "r");
    if(bufferfile == NULL){
        printf("Error in opening file\n");
        exit(1);
    }

    char buffer[10];

    fscanf(bufferfile, "%[^,]", buffer);

    if((strcmp(buffer, "Surname")) != 0){
        fprintf(firstfile, "Surname,Sex,Student Number,Department\n");
    }

    fclose(bufferfile);

    int count = 0;
	while (count < n){
		printf("\nStudent %d Information", count+1);
		
		printf("\nSurname: ");
		scanf(" %[^\n]", student[count].surname);
        fprintf(firstfile, "%s,", student[count].surname);
        fprintf(secondfile, "%s,", student[count].surname);
	
		printf("Sex (M for male, F for female): ");
		scanf(" %c", &student[count].sex);
        fprintf(firstfile, "%c,", student[count].sex);
        fprintf(secondfile, "%c,", student[count].sex);
		
		printf("Year (year part of student number): ");
		scanf("%d", &student[count].year);
        fprintf(firstfile, "%d-", student[count].year);
        fprintf(secondfile, "%d,", student[count].year);
		
		printf("Snum (last five digits of the student number): ");
		scanf("%d", &student[count].Snum);
        fprintf(firstfile, "%d,", student[count].Snum);
        fprintf(secondfile, "%d,", student[count].Snum);

        printf("Department: ");
		scanf(" %[^\n]", student[count].Department);
        fprintf(firstfile, "%s\n", student[count].Department);
        fprintf(secondfile, "%s\n", student[count].Department);

		count++;
    }
    fclose(firstfile);
    fclose(secondfile);

    printf("\nNew record/s is/are added...\n");

}

// Function to allocate memory for an array from the database file
s_record *allocarray(){

    FILE *file = fopen("database.csv", "r");
    if(file == NULL){
        printf("Error in opening file\n");
        exit(1);
    }   

    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL){
        count++;
	}
    
    fclose(file);   

	s_record *student_list = (s_record *)malloc(sizeof(s_record) * count);
    if (student_list == NULL) {
        printf("Error in memory allocation\n");
        exit(1);
    }
	return student_list;
}

// Function that displays student records
void display_s_Info(s_record *list){

    system("cls");

    FILE *file = fopen("database.csv", "r");
    if(file == NULL){
        printf("Error in opening file\n");
        exit(1);
    }

    printf("===============================================================\n");
    printf("Displaying Student Records...\n");
    printf("===============================================================\n");
    printf("---------------------------------------------------------------\n");
    printf("No.\t | Surname\t | Sex\t | Student Number | Department\n");
    printf("---------------------------------------------------------------\n");

    int i = 0;
    while (fscanf(file, "%[^,] ,%c,%d,%d,%s\n", list[i].surname, &list[i].sex, &list[i].year, &list[i].Snum, list[i].Department) != EOF){
        i++;
	}

    fclose(file);

    for(int j = 0; j < i; j++){
        printf("%-2d\t | %-13s | %-3c\t | %-d-%-5d \t  | %-15s\n", j+1, list[j].surname, list[j].sex, list[j].year, list[j].Snum, list[j].Department);
    }
}
