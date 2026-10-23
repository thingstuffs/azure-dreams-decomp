#include "common.h"
#include "shared/town_event_state.h"



typedef struct {
    s32 unk0[8];
    s32 value;
} Destination;

extern TownIndexedValueEntry town_indexed_values[];
extern Destination D_800164D0;

/* Copies the indexed entry's value to the shared destination and returns it. */
Destination *copy_indexed_entry_value(s32 index) {
    Destination *destination = &D_800164D0;

    destination->value = town_indexed_values[index].value;
    return destination;
}
