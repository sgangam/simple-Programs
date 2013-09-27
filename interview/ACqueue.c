/*
 *Author: Sriharsha Gangam
  Email: sgangam@purdue.edu
 * */


#include <stdio.h>
typedef struct _List {
    // dummy struct
} List;


typedef enum _AC_type {
    PASSENGER, CARGO 
} AC_type;

typedef enum _AC_size {
    SMALL, LARGE 
} AC_size;

typedef struct _AC{
    unsigned int id; // the aircraft identifier
    AC_type type;
    AC_size size;
} AC;

typedef struct _ACQueue{
    List* smallPassenger; // A list of aircrafts that only store small passenger planes
    List* largePassenger; // A list of aircrafts that only store large passenger planes
    List* smallCargo; // A list of aircrafts that only store small cargo planes
    List* largeCargo; // A list of aircrafts that only store large cargo planes
} ACQueue;

typedef enum _Request { // We handle three types of requests
    SYSTEM_BOOT, ENQUEUE_AIRCRAFT, DEQUEUE_AIRCRAFT
} Request;

// This is called when systems boot message is given. It initializes the four Lists in our aircraft queue.
void init_queues(ACQueue* ac_queue) { 
    ac_queue->smallPassenger = List_Create();
    ac_queue->largePassenger = List_Create();
    ac_queue->smallCargo = List_Create();
    ac_queue->largeCargo = List_Create();
}

//Enqueues the aircraft in appropriate queue. At the end of each list
void enqueue(ACQueue* ac_queue, AC* ac) {
    List* list;
    if (ac->type == SMALL && ac->size == PASSENGER)
        list = ac_queue->smallPassenger;

    else if (ac->type == LARGE && ac->size == PASSENGER)
        list = ac_queue->largePassenger;

    else if (ac->type == SMALL && ac->size == CARGO)
        list = ac_queue->smallCargo;

    else if (ac->type == LARGE && ac->size == CARGO)
        list = ac_queue->largeCargo;

    int last_position = List_Size(list) ;// Get the size of the list.
    List_Insert(list, last_position, (void *) ac);  // Insert at the end of the list.
}

//  Looks at each of the four lists in prority and accesses the first element of the list.
void dequeue(ACQueue* ac_queue, AC* ac) {
    List* list;
    if (List_Size(ac_queue->largePassenger) > 0)
        list = ac_queue->largePassenger; // FIRST preference

    else if (List_Size(ac_queue->smallPassenger) > 0)
        list = ac_queue->smallPassenger;// SECOND preference
        
    else if (List_Size(ac_queue->largeCargo) > 0)
        list = ac_queue->largeCargo;// THIRD preference

    else if (List_Size(ac_queue->smallCargo) > 0)
        list = ac_queue->smallCargo;// LAST preference
    else
        printf("Not enough aircrafts available to dequeue\n");

        
    AC* first_element = (AC*) List_Access(list, 0) ; // Access the first element in the list
    ac->id = first_element->id;
    ac->type = first_element->type;
    ac->size = first_element->size;
    List_Remove(list, 0) ; // Remove the first element in the lsit
}

void aqm_request_process(Request request, ACQueue* ac_queue, AC* ac) {
    if (request == SYSTEM_BOOT) 
        init_queue(ac_queue);
    else if (request == SYSTEM_BOOT)
        enqueue(ac_queue, ac);
    else if (request == SYSTEM_BOOT)
        dequeue(ac_queue, ac);
    else
        printf("Invalid request\n");
        
}

int main(int argc, char *argv[])
{
    ACQueue ac_queue;// The queue of aircrafts
    AC ac1, ac2;// Two aircrafts
    ac1.id = 0; ac1.type = PASSENGER; ac1.size = SMALL;

    AC acDequeue;
    aqm_request_process(SYSTEM_BOOT, &ac_queue, 0);
    aqm_request_process(SYSTEM_BOOT, &ac_queue, &ac1);
    aqm_request_process(SYSTEM_BOOT, &ac_queue, &ac2);

    return 0;
}
