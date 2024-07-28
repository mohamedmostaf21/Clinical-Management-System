#ifndef USER_H
#define USER_H
#include "dataType.h"
//****** prototypes *******/
void userMode();
void viewPatientRecord(u32 patientID);
void viewTodayReservations();
int isRequestIDUnique(int id);
void requestToReserve();

#endif /* USER_H */