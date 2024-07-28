#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include "STD_TYPES.h"

#define MAX_SLOTS 5
#define SLOT_SIZE 30
#define MAX_PASSWORD_ATTEMPTS 3
#define ADMIN_DEFAULT_PASSWORD 1234
#define MAX_PATIENTS 50
#define MAX_REQUSETS 50
#define MAX_SLOTS 5
#define SLOT_SIZE 30

#define TRUE 1
#define FALSE 0


//***** non primative datatypes  ******//
typedef struct{
	u8 name[50];
	u8 age;
	u8 gender;
	u32 id;
	s8 reservedSlot; 
}Patient;

typedef struct{
	Patient patient;
	char reservationSlots[50]; 
}Request;

typedef enum{
	NOT_EXIST = -1,
	EXIST
}Existence;


extern u8 slots[MAX_SLOTS][SLOT_SIZE];
extern Patient patients[MAX_PATIENTS];
extern Request requests[MAX_REQUSETS];
extern u8 numPatients;
extern u8 numOfRequests;
extern u8 slotAvailability[MAX_SLOTS];
#endif /* DATA_TYPE_H */