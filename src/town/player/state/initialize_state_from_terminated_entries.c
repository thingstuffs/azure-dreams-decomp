#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} State;

void expand_bounds_to_inset_rectangle();                 /* extern */
extern s16 D_8006ADD6;
extern s32 player_motion_bounds[4];
extern State player_blocking_rects;

/* Process the terminated entry list and initialize the state for the current mode. */
void initialize_state_from_terminated_entries(s32 *entries) {
    s16 mode;

    player_motion_bounds[0] = 0x1FFFFFFF;
    player_motion_bounds[2] = 0x1FFFFFFF;
    player_motion_bounds[1] = 0;
    player_motion_bounds[3] = 0;
    for (; *entries != 0; entries++) {
        expand_bounds_to_inset_rectangle(player_motion_bounds, *entries);
    }
    mode = D_8006ADD6;
    if (mode == 8) {
        player_blocking_rects.unk0 = 0x03000000;
        (&player_blocking_rects)->unk4 = 0x04000000;
        (&player_blocking_rects)->unkC = 0x02A00000;
        (&player_blocking_rects)->unk8 = 0;
        (&player_blocking_rects)->unk10 = 0x80000000;
        return;
    }
    if (mode == 0xB) {
        player_blocking_rects.unk0 = 0;
        (&player_blocking_rects)->unk4 = 0x04A00000;
        (&player_blocking_rects)->unkC = 0x03B00000;
        (&player_blocking_rects)->unk8 = 0;
        (&player_blocking_rects)->unk10 = 0x80000000;
        return;
    }
    player_blocking_rects.unk0 = 0x80000000;
}
