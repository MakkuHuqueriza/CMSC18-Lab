#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_record {
    char surname[30];
    char sex;
    int year;
    int Snum;
    char Department[30];
}s_record;

void display();
int choiceforUser();
int num_of_student();
s_record *create_database(int num);
void ask_student_Info(int n, s_record student[]);
void display_s_Info(s_record *);
int innerchoiceforUser();

int main(){

    int num, choice;
    s_record *student_list;
    s_record stdlist[1000];

    display();
    while(1){
        choice = choiceforUser();
        switch(choice){

            case 0:
                printf("\nExiting program...");
                return 0;
                break;
            
            case 1: 
                num = num_of_student();
                student_list = create_database(num);
                ask_student_Info(num, student_list);  
                innerchoiceforUser();
                break;

            case 2:
                display_s_Info(stdlist);
                innerchoiceforUser();
                break;

            default:
                printf("\n\tInvalid Input!\n");
                break;
        }
    }
}

void display(){
	printf("\n=================================================================================================================\n");
	printf("THIS PROGRAM IS A SIMPLE STUDENT RECORDS THAT STORES THE DATA INPUTTED BY THE USER TO A TEXT FILE AS A DATABASE.\n");
    printf("UNANTICIPATED USER ACTIONS OR INPUTS MAY LEAD TO BUGS OR THE TERMINATION OF THE PROGRAM.\n");
	printf("=================================================================================================================\n");
}

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

int num_of_student(){
    system("cls");
    int num;
	printf("\nHow many students do you want to include in the student record?");
	printf("\nEnter number here: ");
	scanf("%d", &num);
	return num;
}

s_record *create_database(int num)
{
	s_record *student_list = (s_record *)malloc(sizeof(s_record) * num);
	return student_list;
}

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

void display_s_Info(s_record *list){

    system("cls");

    FILE *file = fopen("database.csv", "r");
    if(file == NULL){
        printf("Error in opening file\n");
        exit(1);
    }

    printf("=============================================================\n");
    printf("Displaying Student Records...\n");
    printf("=============================================================\n");
    printf("-------------------------------------------------------------\n");
    printf("No.\t | Surname\t | Sex\t | Student Number | Department \n");
    printf("-------------------------------------------------------------\n");

    int i = 0;
    while (fscanf(file, "%[^,] ,%c,%d,%d,%s\n", list[i].surname, &list[i].sex, &list[i].year, &list[i].Snum, list[i].Department) != EOF){
        i++;
	}

    fclose(file);

    for(int j = 0; j < i; j++){
        printf("%-2d\t | %-13s | %-3c\t | %-d-%-5d \t  | %-15s\n", j+1, list[j].surname, list[j].sex, list[j].year, list[j].Snum, list[j].Department);
    }
}
