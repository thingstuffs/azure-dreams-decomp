#include "common.h"

#include "common.h"
#include "engine/town.h"

void initialize_paired_state_blocks(void);

/* Dispatch to the town runtime routine. */
void init_town_paired_state(void) {
    initialize_paired_state_blocks();
}
