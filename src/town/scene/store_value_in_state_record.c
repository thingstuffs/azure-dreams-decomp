#include "shared/town_event_state.h"
#include "common.h"
#include "town/scene.h"

typedef unsigned long uptr;

typedef struct {
    u8 pad[0x10];
    void *records;
} TownObject;

/* Update the selected object record when the current state is 1. */
s32 store_value_in_state_1_record(TownObject *object, s32 record_index) {
    if (town_event_state->selection_mode == 1) {
        *(s32 *)((record_index * 0x10) + (uptr)object->records + 8) =
            build_selected_entry_output(0);
        return 0;
    }
    return 1;
}
