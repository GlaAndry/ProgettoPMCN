#include <stdio.h>
#include <stdlib.h>
#include "basic.h"

/*
* -----------------------------------------------------
* return the index of the available server idle longest
* -----------------------------------------------------
*/

int find_one(struct state_multiserver multiserver[]) {

    int s;
    int i = 1;

    while (multiserver[i].type_event == 1) {
        i++;                                /* find the index of the first available */
    }                                       /* (idle) server                         */
    s = i;
    while (i < NUM_MAX_SERVER) {            /* now, check the others to find which   */
        i++;                                /* has been idle longest                 */
        if ((multiserver[i].type_event == 0) && (multiserver[i].next_event_time < multiserver[s].next_event_time))
            s = i;
    }
    return s;

}