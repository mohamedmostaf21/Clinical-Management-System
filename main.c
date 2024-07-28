#include <stdio.h>
#include <stdlib.h>
#include "../inc/user.h"
#include "../inc/admin.h"
int main(){
	u8 choice;
    u8 scanf_choice;
	while (1) {
        printf("\nWelcome to the Clinic Management System\n");
        printf("1. Admin Mode\n");
        printf("2. User Mode\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf_choice = scanf("%d", &choice);
     
        // Check if scanf successfully read an integer 
		if (scanf_choice != 1) {
			printf("Invalid input. Please enter a valid choice (integer).\n");
            while (getchar() != '\n');  // Clear input buffer
			 // Continue to prompt for user input
            continue;
		}
        switch (choice) {
            case 1:
                adminMode();
                system("cls");
                break;
            case 2:
                userMode();
                system("cls");
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    }

	
	return 0;
}