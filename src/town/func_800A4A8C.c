#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800A21EC_0 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
} S_800A21EC_0;   /* arg2 in func_800A21EC */

typedef struct S_800A21EC_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    s32 unk_04;
    s32 unk_08;
} S_800A21EC_1;   /* arg1 in func_800A21EC */

typedef struct S_800A21EC_2 {
    M2C_UNK * unk_00;
    u8 pad_04[0x10];
    void * unk_14;
    u8 pad_18[0x8];
    s16 unk_20;
} S_800A21EC_2;   /* arg0 in func_800A21EC */

typedef struct S_800A21EC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A21EC_3;   /* ((S_800A21EC_2 *)arg0)->unk_14 in func_800A21EC */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004491C();
extern M2C_UNK D_80046398;
extern M2C_UNK D_800A22D0;

/* Initialize object state and placement with a direction-dependent offset. */
s32 func_800A21EC(void *object, S_800A21EC_1 *placement, S_800A21EC_0 *state) {
    state->unk_00 = 0;
    state->unk_04 = 0;
    state->unk_05 = 0;
    func_8004491C(object - 0x20, &D_80046398);
    placement->unk_00.at00.v = (s32) ((S_800A21EC_3 *)(((S_800A21EC_2 *)object)->unk_14))->unk_00;
    placement->unk_04 = (s32) ((S_800A21EC_3 *)(((S_800A21EC_2 *)object)->unk_14))->unk_04;
    placement->unk_08 = (s32) ((S_800A21EC_3 *)(((S_800A21EC_2 *)object)->unk_14))->unk_08;
    ((S_800A21EC_2 *)object)->unk_00 = &D_800A22D0;
    if (((S_800A21EC_2 *)object)->unk_20 == 0) {
        s32 heading;
        heading = 1;
        state->unk_08 = heading;
        heading = (u16) placement->unk_00.at02.v;
        placement->unk_00.at02.v = (u16) (heading + 0x90);
    } else {
        s32 flags = (u16) state->unk_14;
        s32 enabled = 1;
        state->unk_08 = enabled;
        state->unk_14 = (u16) (flags | 1);
        placement->unk_00.at02.v = (u16) (placement->unk_00.at02.v - 0x90);
    }
    state->unk_1A = 0;
}
