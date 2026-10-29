#include "common.h"
#include "dungeon/monster/beldo_large.h"

typedef struct DungeonState {
    s8 pad00[0x12];
    u16 field12;
    u8 pad14[4];
    u16 field18;
} DungeonState;

extern DungeonState *encounter_object_slots[];
extern DungeonState *encounter_overlay_object[];

/* Increments the selected state counter and clears its timer. */
void advance_encounter_overlay_phase(s32 state_selector) {
    if (state_selector == 0) {
        DungeonState *state_zero;

        state_zero = (DungeonState *)((u8 *)encounter_object_slots[0] + 0x20);
        state_zero->field18 = 0;
        state_zero->field12++;
        return;
    }

    {
        DungeonState *state_nonzero;

        state_nonzero = (DungeonState *)((u8 *)encounter_overlay_object[0] + 0x20);
        state_nonzero->field18 = 0;
        state_nonzero->field12++;
    }
}
