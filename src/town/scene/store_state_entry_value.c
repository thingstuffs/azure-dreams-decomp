#include "shared/town_event_state.h"
#include "common.h"
#include "town/scene.h"

typedef unsigned long uptr;

typedef struct {
    u8 pad[0x10];
    void *records;
} TownObject;

s32 store_state_1_entry_value(TownObject *object, s32 index, s32 unused2, s32 unused3) {
    if (town_event_state->selection_mode != 1) {
        return 1;
    }
    {
                        /* MATCH: Save store operands separately so call arguments retain their incoming registers. */
        TownObject *saved_object = object;
        s32 saved_index = index;
        *(s32 *)((saved_index * 0x10) + (uptr)saved_object->records + 8) =
            prepare_stored_value_pair();
        return 0;
    }
}
