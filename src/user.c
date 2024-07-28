#include "../inc/user.h"
Request requests[MAX_REQUSETS];
u8 numOfRequests = 0;
void userMode(){
    u8 choice;
    u8 scanf_use;
    u8 flage = FALSE;
    u32 patientID;
    while (1) {
        printf("\nUser Mode Menu:\n");
        printf("1. View patient record\n");
        printf("2. View today's reservations\n");
        printf("3. Request to reserve\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf_use = scanf("%d", &choice);


        // Check if scanf successfully read an integer 
		if (scanf_use != 1) {
			printf("Invalid input. Please enter a valid choice (integer).\n");
			while (getchar() != '\n');  // Clear input buffer
         
            continue;  // Skip the rest of the loop iteration
		}
        switch (choice) {
            case 1:
                printf("Enter patient ID: ");
                scanf("%d", &patientID);
           
                viewPatientRecord(patientID);
                break;
            
            case 2:
                viewTodayReservations();
                break;
            case 3:
                requestToReserve();
                break;
            case 4:
               printf("Logging out of user mode.\n");
               flage = TRUE;
               break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
        if(flage == TRUE){
            break;
        }
    }
}

void viewPatientRecord(u32 patientID) {
    int found = 0;
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].id == patientID) {
            printf("Patient ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Gender: %c\n", patients[i].gender);
            if (patients[i].reservedSlot == -1) {
                printf("Reservation: No reservation\n");
            } else {
                printf("Reserved at: %s\n", slots[patients[i].reservedSlot]);
            }
            found = 1;
            break;
        }
    }

    if (found != 1) {
        printf("Patient with ID %d not found.\n", patientID);
    }
}


void viewTodayReservations() {
    u8 found = FALSE;
    printf("\nToday's Reservations:\n");
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].reservedSlot != -1) {
            printf("Patient ID %d has a reservation: %s\n", patients[i].id, slots[patients[i].reservedSlot]);
            found = TRUE;
        }
    }

    if(found != TRUE){
        printf("No reservation today yet\n");
    }
}

int isRequestIDUnique(int id){
    for (u8 i = 0; i < numOfRequests; i++) {
        if(requests[i].patient.id == id) {
            return EXIST; // ID already exists
        }
    }
    return NOT_EXIST; // ID is unique
}
void requestToReserve(){
    //to check that the numbers of patients doesn't exceed the limit
	if (numOfRequests >= MAX_REQUSETS) {
        printf("Maximum number of requests reached.\n");
        return;
    }
	
	//add the patients details 
	Request newRequest;
    printf("\nEnter patient details:\n");
	printf("Name: ");
	scanf(" %[^\n]s", newRequest.patient.name);

    printf("Age: ");
    scanf("%d", &newRequest.patient.age);
   
    printf("Gender (M/F): ");
    scanf(" %c", &newRequest.patient.gender);
  
    printf("ID: ");
    scanf("%d", &newRequest.patient.id);
 
    printf("Reservation Slot: ");
    scanf(" %[^\n]s", newRequest.reservationSlots);

	if (isRequestIDUnique(newRequest.patient.id) != NOT_EXIST){
        printf("Error: Request ID already exists. Cannot add request.\n");
        return;
    }


    // Initially no slot reserved
    newRequest.patient.reservedSlot = -1; 
  
    //Add patient to array
    requests[numOfRequests] = newRequest;
    numOfRequests++;
    printf("Request submited successfully.\n");

}