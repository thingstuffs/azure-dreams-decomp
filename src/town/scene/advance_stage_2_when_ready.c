#include "common.h"

typedef struct {
    u8 pad[8];
    s32 *value;
} ValueHolder;

typedef struct {
    u8 pad[0x34];
    u32 flags;
} State;

extern ValueHolder *D_80701988[3];
extern State *D_80701968[3];

extern s32 func_80700C9C(s32 entry);
extern void shift_index_and_add_offset(s32 entry);
extern void pass_indexed_table(s32 entry);
extern s32 call_indexed_callback_failed_test();

/* When gate 2 and the counter both pass, set stage flag 8 and return the stage handler's result. */
s32 advance_stage_2_when_ready(s32 entry) {

    if ((func_80700C9C(2) != 0) && (*D_80701988[0]->value >= 1)) {
        shift_index_and_add_offset(2);
        D_80701968[0]->flags |= 8;
        return call_indexed_callback_failed_test();
    }
    pass_indexed_table(2);
    return entry;
}
