#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s_record {
    char surname[30];
    char sex;
    int year;
    int Snum;
    char Department[30];
};

void display();
int num_of_student();
struct s_record *create_database(int n);
void ask_student_Info(int n, struct s_record student[]);
void display_s_Info(int n, struct s_record *);
void display_filtered_records(int n, struct s_record *list, char filter_type, char filter_value[]);
void display_records_by_snum(int n, struct s_record *list, int target_snum);
int filter_type_input();
void filter_value_input(char filterArray[]);
int target_Snum_input();
int choiceforUser();


int main(){
    int num, target_snum, choice = 1;
    struct s_record *student_list;
    char filter_type, filter_value[30];

    display();
    while(choice != 0){
        choice = choiceforUser();
        
        if(choice == 1){
            num = num_of_student();
            student_list = create_database(num);
            ask_student_Info(num, student_list);
        }
        else if (choice == 2)
        {
            display_s_Info(num, student_list);    
        }

        else if (choice == 3)
        {
            filter_type = filter_type_input();
            filter_value_input(filter_value);

            // Display filtered records
            display_filtered_records(num, student_list, filter_type, filter_value);
        }
        else if (choice == 4)
        {
            target_snum = target_Snum_input();

            // Display records linked to the specified Snum
            display_records_by_snum(num, student_list, target_snum);
        }
        else if (choice == 0){
            printf("Exiting program...");
            return 0;
        }
        else{
            printf("Invalid Input!");
        }
    }

    return 0;
}

int choiceforUser(){
    int choice;
    printf("\n[1] Add Record\n");
    printf("[2] Display All Records\n");
    printf("[3] Display All Records Filtered By Sex/ Year/ Department\n");
    printf("[4] Display Record(s) Linked To A Given Snum\n");
    printf("[0] Exit\n");
    printf("Choice: ");
    scanf("%d", &choice);

    return choice;
}

void display(){
	printf("\n================================================\n");
	printf("This program is a simple student record.\n");
	printf("================================================\n");
}

int num_of_student(){
    int num;
	printf("\nHow many students do you want to include in the student record?");
	printf("\nEnter number here: ");
	scanf("%d", &num);
	return num;
}

struct s_record *create_database(int n){
    struct s_record *student_list = (struct s_record *)malloc(sizeof(struct s_record) * n);
    return student_list;
}

void ask_student_Info(int n, struct s_record student[]){
    int count = 0;
	while (count < n){
		printf("\nStudent %d Information", count+1);
		
		printf("\nSurname: ");
		scanf(" %[^\n]", student[count].surname);
	
		printf("Sex (M for male, F for female): ");
		scanf(" %c", &student[count].sex);
		
		printf("Year (year part of student number): ");
		scanf("%d", &student[count].year);
		
		printf("Snum (last five digits of the student number): ");
		scanf("%d", &student[count].Snum);

        printf("Department: ");
		scanf(" %[^\n]", student[count].Department);

		count++;
    }
}

void display_s_Info(int n, struct s_record *list){
    int i = 0;
	puts("");
	printf("=============================================================\n");
	printf("Displaying Student Records...\n");
	printf("=============================================================\n");
	puts("");
	printf("No\t | Surname\t | Sex\t | Year\t | Snum\t | Department \n");
	while (i < n)
	{
		printf("%-2d\t | %-13s | %-3c\t | %-d\t | %-5d | %-15s\n", 
            i+1, list[i].surname, list[i].sex, list[i].year, list[i].Snum, list[i].Department);
		i++;
	}
}

int filter_type_input(){
    int filter_type;

    // Get filter type from the user
    printf("\nEnter filter type (S for sex, Y for year, D for department): ");
    scanf(" %c", &filter_type);

    return filter_type;
}

void filter_value_input(char filterArray[]){

    // Get filter value from the user
    printf("Enter filter value: ");
    scanf(" %[^\n]", filterArray);
}

void display_filtered_records(int n, struct s_record *list, char filter_type, char filter_value[]) {
    int i = 0;
    puts("");
    printf("=============================================================\n");
    printf("Displaying Filtered Student Records...\n");
    printf("=============================================================\n");
    puts("");
    printf("No\t | Surname\t | Sex\t | Year\t | Snum\t | Department \n");

    while (i < n) {
        // Check the filter condition based on the chosen filter type
        if ((filter_type == 'S' && list[i].sex == filter_value[0]) ||
            (filter_type == 'Y' && list[i].year == atoi(filter_value)) ||
            (filter_type == 'D' && strcmp(list[i].Department, filter_value) == 0)) {
            // Display the record only if it matches the filter condition
            printf("%-2d\t | %-13s | %-3c\t | %-d\t | %-5d | %-15s\n",
                i + 1, list[i].surname, list[i].sex, list[i].year, list[i].Snum, list[i].Department);
        }
        i++;
    }
}

int target_Snum_input(){
    int target_snum;

    // Get target_snum from the user
    printf("\nEnter Snum to display linked records: ");
    scanf("%d", &target_snum);

    return target_snum;
}

void display_records_by_snum(int n, struct s_record *list, int target_snum) {
    int i;
    int found = 0;

    puts("");
    printf("=============================================================\n");
    printf("Displaying Records Linked to Snum: %d\n", target_snum);
    printf("=============================================================\n");
    puts("");
    printf("No\t | Surname\t | Sex\t | Year\t | Snum\t | Department \n");

    for (i = 0; i < n; i++) {
        if (list[i].Snum == target_snum) {
            printf("%-2d\t | %-13s | %-3c\t | %-d\t | %-5d | %-15s\n",
                   i + 1, list[i].surname, list[i].sex, list[i].year, list[i].Snum, list[i].Department);
            found = 1;
        }
    }

    if (!found) {
        printf("No records found for Snum: %d\n", target_snum);
    }
}





