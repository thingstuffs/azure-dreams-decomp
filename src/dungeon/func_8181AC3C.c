#include "common.h"
#include "shared/object_flags.h"

typedef struct S_8002443C_0 {
    u16 unk_00;
} S_8002443C_0;   /* state in func_8002443C; pointer addresses record offset 0x2 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    unsigned char pad00[2];
    u16 frames_left;
    unsigned char pad04[20];
    s16 mode;
    s16 period;
    u16 tick;
    unsigned char pad1e[0x3a];
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} MotionState;

typedef struct {
    unsigned char pad00[0x14];
    u16 flags;
} UpdateFlags;

extern s16 D_80025914;
extern void func_800478B8(void *flags);

/* Accumulate motion, process the update mode, and mark expired or flagged state. */
void func_8002443C(MotionState *state, s32 *sum, UpdateFlags *flags) {
    s32 update_count;
    s32 more_updates;
    u16 next_tick;

    state->frames_left = state->frames_left - 1;
    state->x = state->x + state->dx;
    state->y = state->y + state->dy;
    state->z = state->z + state->dz;
    sum[0] = sum[0] + state->x;
    sum[1] = sum[1] + state->y;
    D_80025914 = 1;
    sum[2] = sum[2] + state->z;

    switch (state->mode) {
    case 0:
        func_800478B8(flags);
        break;
    case 1:
        if (state->period > 0) {
            update_count = 0;
            do {
                func_800478B8(flags);
                update_count = update_count + 1;
                more_updates = update_count < state->period;
            } while (more_updates);
        }
        break;
    case 2:
        next_tick = state->tick + 1;
        state->tick = next_tick;
        if ((s16) next_tick >= state->period) {
            func_800478B8(flags);
            state->tick = 0;
        }
        break;
    default:
        break;
    }

    if ((s16) state->frames_left <= 0) {
        ((S_8002443C_0 *)((u8 *)state - 0x2))->unk_00 = ((S_8002443C_0 *)((u8 *)state - 0x2))->unk_00 | 0x8000;
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    }
    if (flags->flags & 0x8000) {
        ((S_8002443C_0 *)((u8 *)state - 0x2))->unk_00 = ((S_8002443C_0 *)((u8 *)state - 0x2))->unk_00 | 0x8000;
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    }
}
