#include "common.h"


typedef struct {
    u8 pad[8];
    s32 *value;
} ValueHolder;

typedef struct {
    u8 pad[0x34];
    u32 flags;
} State;

extern ValueHolder *devkit_stage_value_owner[3];
extern State *devkit_state_slots[3];

extern s32 func_80700C9C(s32 entry);
extern void shift_index_and_add_offset(s32 entry);
extern void pass_indexed_table(s32 entry);
extern s32 func_80701404(void);

/* When the gate and the counter both pass, set the stage flag and return the stage handler's result. */
s32 advance_stage_1_when_ready(s32 entry) {

    if ((func_80700C9C(1) != 0) && (*devkit_stage_value_owner[0]->value >= 3)) {
        shift_index_and_add_offset(1);
        devkit_state_slots[0]->flags |= 4;
        return func_80701404();
    }
    pass_indexed_table(1);
    return entry;
}
