#ifndef ADMIN_H
#define ADMIN_H
#include "dataType.h"





//****** prototypes  ******//
void adminMode();
void addNewPatient();
void editPatientRecord();
void reserveSlotWithDoctor();
void cancelReservation();
int isPatientIDUnique(int id);
void viewRequests();



#endif /* ADMIN_H */