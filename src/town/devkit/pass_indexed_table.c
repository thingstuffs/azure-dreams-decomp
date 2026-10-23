#include "common.h"
#include "town/devkit/stage_dispatch.h"


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
extern s32 func_80701404();

/* When the gate and the counter both pass, set the stage flag and return the stage handler's result. */
s32 set_stage_flag_two_if_ready(s32 fallback_result) {

    if ((func_80700C9C(1) != 0) && (*D_80701988[0]->value >= 2)) {
        shift_index_and_add_offset(1);
        D_80701968[0]->flags |= 2;
        return func_80701404();
    }
    pass_indexed_table(1);
    return fallback_result;
}
