#include "../inc/admin.h"

//***** global variables ******//

//array of patients 
Patient patients[MAX_PATIENTS];

u8 numPatients = 0;

//ranges of slots avaliable in starting system 
u8 slots[MAX_SLOTS][SLOT_SIZE] = {
    "2pm to 2:30pm",
    "2:30pm to 3pm",
    "3pm to 3:30pm",
    "4pm to 4:30pm",
    "4:30pm to 5pm"
};

u8 slotAvailability[MAX_SLOTS] = {1, 1, 1, 1, 1}; // 1 means available, 0 means reserved

void adminMode(){
	//handle the password
	u32 password;
	u8 attempts = 0;
	u8 scanf_pass;
    u8 scanf_choice;
	printf("\nEnter the admin password: ");
	while(attempts < MAX_PASSWORD_ATTEMPTS){
		scanf_pass = scanf("%d", &password);
		
		// Check if scanf successfully read an integer 
		if (scanf_pass != 1) {
			printf("Invalid input. Please enter a valid password (integer).\n");
			attempts++;
			printf("Attempts left: %d\n", 3 - attempts);
            while (getchar() != '\n');  // Clear input buffer
            if (attempts == 3) {
                printf("Maximum password attempts reached. Exiting admin mode.\n");
                return;
            }
            printf("Enter the admin password again: ");
            continue;  // Skip the rest of the loop iteration
		}else if(password == ADMIN_DEFAULT_PASSWORD){
			printf("Login successful!\n");
			u8 adminChoice;
			while (1) {
                printf("\nAdmin Mode Menu:\n");
                printf("1. Add new patient record\n");
                printf("2. Edit patient record\n");
                printf("3. Reserve a slot with the doctor\n");
                printf("4. Cancel reservation\n");
                printf("5. View Requests\n");
                printf("6. Logout\n");
                printf("Enter your choice: ");
                scanf_choice = scanf("%d", &adminChoice);
                if (scanf_choice != 1) {
                    printf("Invalid input. Please enter a valid choice (integer).\n");
                    while (getchar() != '\n');  // Clear input buffer
                    continue;  // Skip the rest of the loop iteration
                }
                switch (adminChoice) {
                    case 1:
                        addNewPatient();
                        break;
                    case 2:
                        editPatientRecord();
                        break;
                    case 3:
                        reserveSlotWithDoctor();
                        break;
                    case 4:
                        cancelReservation();
                        break;
                    case 5:
                        viewRequests();
                        break;
                    case 6:
                        printf("Logging out of admin mode.\n");
                        return;
                    default:
                        printf("Invalid choice. Please enter a valid option.\n");
                }
            }
		}else{
			attempts++;
            printf("Incorrect password. Attempts left: %d\n", 3 - attempts);
            if (attempts == 3) {
                printf("Maximum password attempts reached. Exiting admin mode.\n");
                return;
            }
            printf("Enter the admin password again: ");
		}
		
	}	
}

int isPatientIDUnique(int id) {
    for (u8 i = 0; i < numPatients; i++) {
        if(patients[i].id == id) {
            return EXIST; // ID already exists
        }
    }
    return NOT_EXIST; // ID is unique
}


void addNewPatient(){
	//to check that the numbers of patients doesn't exceed the limit
	if (numPatients >= MAX_PATIENTS) {
        printf("Maximum number of patients reached.\n");
        return;
    }
	
	//add the patients details 
	Patient newPatient;
    printf("\nEnter patient details:\n");
	printf("Name: ");
	scanf(" %[^\n]s", newPatient.name);
    printf("Age: ");
    scanf("%d", &newPatient.age);
    printf("Gender (M/F): ");
    scanf(" %c", &newPatient.gender);
    printf("ID: ");
    scanf("%d", &newPatient.id);
	if (isPatientIDUnique(newPatient.id) != NOT_EXIST){
        printf("Error: Patient ID already exists. Cannot add patient.\n");
        return;
    }


    // Initially no slot reserved
    newPatient.reservedSlot = -1; 
    //Add patient to array
    patients[numPatients] = newPatient;
    numPatients++;
    printf("Patient record added successfully.\n");

   
}


void editPatientRecord(){
    u32 id;
    printf("\nEnter patient ID to edit: ");
    scanf("%d", &id);
    //found flage for the event of enetering incorrect id
    u8 found = FALSE;
    for (int i = 0; i < numPatients; i++){
        if(patients[i].id == id){
            printf("Enter new details for patient %s:\n", patients[i].name);
            printf("Name: ");
            scanf(" %[^\n]s", patients[i].name);
            printf("Age: ");
            scanf("%d", &patients[i].age);
            printf("Gender (M/F): ");
            scanf(" %c", &patients[i].gender);
            printf("Patient record updated successfully.\n");
            found = TRUE;
            break;
        }
    }

    if(found != TRUE){
        printf("Patient with ID %d not found.\n", id);
    }
}

void reserveSlotWithDoctor(){
    if (numPatients == 0) {
        printf("No patients available to reserve slots.\n");
        return;
    }

    u32 id;
    printf("\nEnter patient ID to reserve slot: ");
    scanf("%d", &id);

    //found flage for the event of enetering incorrect id
    u8 found = FALSE;
    for (u8 i = 0; i < numPatients; i++){
        if(patients[i].id == id){
            //check that has reserved slot or not
            if(patients[i].reservedSlot != -1){
               printf("Patient already has a reserved slot.\n");
               return;
            }

            printf("\nAvailable Slots:\n");
            for (u8 j = 0; j < MAX_SLOTS; j++){
                //check if slot is avaliable or not
                if(slotAvailability[j] == 1){
                    printf("%d. %s\n", j + 1, slots[j]);
                }
            }

            u8 slotChoice;
            printf("Enter slot number to reserve (1-%d): ", MAX_SLOTS);
            scanf("%d", &slotChoice);
            // Convert to zero-based index for accessing 
            slotChoice--; 

            if( (slotChoice >= 0) && (slotChoice < MAX_SLOTS) && (slotAvailability[slotChoice] == 1) ){
                patients[i].reservedSlot = slotChoice;
                //mark the slot as reserved
                slotAvailability[slotChoice] = 0; 
                printf("Slot reserved successfully.\n");
                // Remove the specific request associated with this patient
                u8 requestIndex = MAX_REQUSETS; // Invalid index
                for (u8 i = 0; i < numOfRequests; i++) {
                    if (requests[i].patient.id == patients[i].id) {
                        requestIndex = i;
                        break;
                    }
                }

                if (requestIndex < MAX_REQUSETS) { // Valid index
                    // Shift requests to remove the specific request
                    for (u8 j = requestIndex; j < numOfRequests - 1; j++) {
                        requests[j] = requests[j + 1];
                    }
                    numOfRequests--;
                }
            }else {
                printf("Invalid slot choice.\n");
            }
            found = TRUE;
            break;

        }
    }
    if (found != TRUE) {
        printf("Patient with ID %d not found.\n", id);
    }
    

}

void cancelReservation(){
    u8 id;
    printf("\nEnter patient ID to cancel reservation: ");
    scanf("%d", &id);

    //found flage for the event of enetering incorrect id
    u8 found = FALSE;
    for (u8 i = 0; i < numPatients; i++){
        if(patients[i].id == id){

            if (patients[i].reservedSlot == -1) {
                printf("Patient with ID %d does not have any reservations to cancel.\n", id);
            }else{
                u8 slotIndex =  patients[i].reservedSlot;
                printf("Reservation cancelled for patient %s in slot %s.\n", patients[i].name, slots[slotIndex]);

                //mark slot as avaliable
                slotAvailability[slotIndex] = 1;

                //clear the reservation of the patient
                patients[i].reservedSlot = -1;
            } 
            found = TRUE;
            break;
        }
       
    }
    if (found != TRUE){
        printf("Patient with ID %d not found.\n", id);
    }
    
}

void viewRequests(){
    printf("\nToday's Requests:\n");
    for (int i = 0; i < numOfRequests; i++) {
        if (requests[i].patient.reservedSlot != -1) {
            printf("Request ID %d has a request before: %s\n", patients[i].id, patients[requests[i].patient.reservedSlot]);
        }else{
            printf("\nRequest number %d: \n", i + 1);
            printf("Patient ID: %d\n", requests[i].patient.id);
            printf("Name: %s\n", requests[i].patient.name);
            printf("Age: %d\n", requests[i].patient.age);
            printf("Gender: %c\n", requests[i].patient.gender);    
            printf("Reservation slot : %s\n", requests[i].reservationSlots);
        }
    }

 

}