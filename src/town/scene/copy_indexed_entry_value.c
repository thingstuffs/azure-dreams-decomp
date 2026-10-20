#include "common.h"
#include "shared/town_event_state.h"



typedef struct {
    s32 unk0[8];
    s32 value;
} Destination;

extern TownIndexedValueEntry D_80016470[];
extern Destination D_800164D0;

/* Copies the indexed entry's value to the shared destination and returns it. */
Destination *copy_indexed_entry_value(s32 index) {
    Destination *destination = &D_800164D0;

    destination->value = D_80016470[index].value;
    return destination;
}
